
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"


int ccreate (void* (*start)(void*), void *arg, int prio) {
	
	TCB_t *newThread;

	ucontext_t *endExecContext = (ucontext_t *) malloc(sizeof(ucontext_t));
	int newTid;

    if(numberOfCreatedThreads == 0) 
    {
      int initializedCorrectly = InitializeCThreads();
      if(initializedCorrectly != 0)
      {
          return ERRO_INIT;
      }
    }
	if(prio<0 || prio>2){
		return ERRO_PARAM;
	}
	newTid = numberOfCreatedThreads;
	
	//Initializes the end context of the thread
	endExecContext->uc_stack.ss_sp = (char*) malloc(STACK_SIZE * sizeof(char));
	endExecContext->uc_stack.ss_size = STACK_SIZE;
	endExecContext->uc_link = NULL;
	makecontext(endExecContext, (void (*) (void)) endExecScheduler, 0);

    //Initializes the new thread's TCB
    newThread = (TCB_t*)malloc(sizeof(TCB_t));
    newThread->prio = prio;
    newThread->state = PROCST_APTO;
    newThread->tid = newTid;
    
    //Initializes the new thread's context
    getcontext(&newThread->context);
    newThread->context.uc_link = endExecContext;
    newThread->context.uc_stack.ss_sp = (char *) malloc(STACK_SIZE);
    newThread->context.uc_stack.ss_size = STACK_SIZE;
    makecontext(&newThread->context, (void(*)(void))start, 1, arg);
	
	if(insere_na_fila_de_aptos(newThread)==CODIGO_ERRO){
		return ERRO_FILAS;
	}

    //Refresh number of threads created
	numberOfCreatedThreads++;
	return newTid;
}

/*-------------------------------------------------------------------------------------------------
Função:	Alterando a prioridade das threads
Ret:	CODIGO_SUCESSO, se conseguiu
	    CODIGO_ERRO, caso contrário 
Lógica: Atualiza a prioridade da variável global thread_in_execution com o valor passado como 
parametro
---------------------------------------------------------------------------------------------------*/
int csetprio(int tid, int prio) {
		if(prio == 0 || prio == 1 || prio == 2 || prio == PRIORITY_MAIN) {
			thread_in_execution.prio = prio;
			return CODIGO_SUCESSO;
		}
		else {
			return CODIGO_ERRO;
		}
        
}


/*-------------------------------------------------------------------------------------------------
Função:	Cedência voluntária da CPU
Ret:	CODIGO_SUCESSO, se conseguiu
	    CODIGO_ERRO, caso contrário 
---------------------------------------------------------------------------------------------------*/
int cyield(void) {
	dispatcher(&thread_in_execution, PROCST_APTO);
	return CODIGO_SUCESSO;
}

int cjoin(int tid) {
	BLOCK_RELEASER *blockReleaser;
	TCB_t* tcbReleaser;
	int releaserTid=tid;
	if(numberOfCreatedThreads == 0) 
	{
		int initializedCorrectly = InitializeCThreads();
		if(initializedCorrectly != 0)
		{
			return ERRO_INIT;
		}
	}
	if(threadExists(releaserTid)==FALHOU)
	{
		return ERRO_NAO_EXISTE;
	}
	if(isThreadReleaser(releaserTid)==SUCEDIDO)
	{
		return ERRO_JA_RELEASER;
	}
	
	tcbReleaser= getThread(releaserTid);
	
	setThreadAsReleaser(releaserTid);
	
	blockReleaser = (BLOCK_RELEASER *) calloc(1, sizeof(BLOCK_RELEASER));
	if (blockReleaser == NULL) {
		return ERRO;
	}
	blockReleaser->tidBlock = thread_in_execution.tid;
	blockReleaser->tidReleaser = releaserTid;
	
	makecontext(tcbReleaser->context.uc_link, (void (*) (void)) cjoin_release, 1, \
    (void *)blockReleaser);
	
	bloquear();
	return SUCEDIDO;
}

int csem_init(csem_t *sem, int count) {
	return CODIGO_ERRO;
}

int cwait(csem_t *sem) {
	return CODIGO_ERRO;
}

int csignal(csem_t *sem) {
	return CODIGO_ERRO;
}

int cidentify (char *name, int size) {
    //char[] components = "Amaury Teixeira Cassola 287704\nBruno Ramos Toresan 291332\nDavid Mees Knijnik 264489";
	//strncpy(name, components, size);
	return CODIGO_SUCESSO;
}
