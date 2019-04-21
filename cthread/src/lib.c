
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"


int ccreate (void* (*start)(void*), void *arg, int prio) {
	return CODIGO_ERRO;
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
	dispatcher(PROCST_APTO);
	return CODIGO_SUCESSO;
}

int cjoin(int tid) {
	return CODIGO_ERRO;
}

int csem_init(csem_t *sem, int count) {
	sem = (csem_t*)malloc(sizeof(csem_t));
	sem->count = count;
	if(	CreateFila2(sem->low_prio_blocked_list) == CODIGO_SUCESSO &&
		CreateFila2(sem->avg_prio_blocked_list) == CODIGO_SUCESSO &&
		CreateFila2(sem->high_prio_blocked_list) == CODIGO_SUCESSO	)
		return CODIGO_SUCESSO;
	else
		return CODIGO_ERRO;
}

int cwait(csem_t *sem) {
	if(sem->count <= 0){
		semaforo_insere_na_fila_de_bloqueados(sem, thread_in_execution.tid, thread_in_execution.prio)
		dispatcher(PROCST_BLOQ);
	}
	sem->count--;
	return CODIGO_SUCESSO;
}

int csignal(csem_t *sem) {
	sem->count++;
	return semaforo_retira_um_da_fila_de_bloqueados(sem);;
}

int cidentify (char *name, int size) {
    char[] components = "Amaury Teixeira Cassola 287704\nBruno Ramos Toresan 291332\nDavid Mees Knijnik 264489";
	strncpy(name, components, size);
	return CODIGO_SUCESSO;
}
