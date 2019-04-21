
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"


int ccreate (void* (*start)(void*), void *arg, int prio) {
	
	TCB_t *newThread;
	int newTid;

    if(numberOfCreatedThreads == INITIALTID) 
    {
      int initializedCorrectly = cinit_queues();
      if(initializedCorrectly != 0)
      {
          return ERRO_INIT;
      }
    }
	if(prio<0 || prio>2){
		return ERRO_PARAM;
	}
	newTid = numberOfCreatedThreads;
    //Initializes the new thread's TCB
    newThread = (TCB_t*)malloc(sizeof(TCB_t));
    newThread->prio = prio;
    newThread->state = PROCST_APTO;
    newThread->tid = newTid;
    
    //Initializes the new thread's context
    getcontext(&newThread->context);
    //newThread->context.uc_link = &endExecSchedulerContext;
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
	return CODIGO_ERRO;
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
