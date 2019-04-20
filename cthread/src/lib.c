
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
Lógica: Uma thread pode alterar a sua própria prioridade. Testa se o tid passado como parâmetro 
é igual ao tid da thread em execução. Caso verdadeiro, atualiza a prioridade com o valor passado 
como parâmetro. Caso contrário, retorna CODIGO_ERRO como erro
---------------------------------------------------------------------------------------------------*/
int csetprio(int tid, int prio) {
    if(tid == thread_in_execution->tid) {
        thread_in_execution->prio = prio;
        return CODIGO_SUCESSO;
    }
    else{
	    return CODIGO_ERRO;
    }

}


/*-------------------------------------------------------------------------------------------------
Função:	Cedência voluntária da CPU
Ret:	CODIGO_SUCESSO, se conseguiu
	    CODIGO_ERRO, caso contrário 
---------------------------------------------------------------------------------------------------*/
int cyield(void) {
	return escalonador_cyield();
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
    char[] components = "Amaury Teixeira Cassola 287704\nBruno Ramos Toresan 291332\nDavid Mees Knijnik 264489";
	strncpy(name, components, size);
	return CODIGO_SUCESSO;
}
