
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"


int ccreate (void* (*start)(void*), void *arg, int prio) {
	return -1;
}

/*-------------------------------------------------------------------------------------------------
Função:	Alterando a prioridade das threads
Ret:	==  0, se conseguiu
	    == -9, caso contrário 
Lógica: Uma thread pode alterar a sua própria prioridade. Testa se o tid passado como parâmetro 
é igual ao tid da thread em execução. Caso verdadeiro, atualiza a prioridade com o valor passado 
como parâmetro. Caso contrário, retorna -9 como erro
---------------------------------------------------------------------------------------------------*/
int csetprio(int tid, int prio) {
    if(tid == thread_in_execution->tid) {
        thread_in_execution->prio = prio;
        return 0;
    }
    else{
	    return -9;
    }

}

int cyield(void) {
	return -1;
}

int cjoin(int tid) {
	return -1;
}

int csem_init(csem_t *sem, int count) {
	return -1;
}

int cwait(csem_t *sem) {
	return -1;
}

int csignal(csem_t *sem) {
	return -1;
}

int cidentify (char *name, int size) {
    char[] components = "Amaury Teixeira Cassola 287704\nBruno Ramos Toresan 291332\nDavid Mees Knijnik 264489";
	strncpy(name, components, size);
	return 0;
}
