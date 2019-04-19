
#ifndef __CUTILS_

#define __CUTILS_

#define PRIORITY_MAIN 3


//Declaração das 3 filas de aptos utilizada pelo escalonador: prioridades alta, média e baixa
PFILA2 high_priority_queue;
PFILA2 average_priority_queue;
PFILA2 low_priority_queue;

//Declaração da thread que está em execução
TCB_t thread_in_execution;
TCB_t thread_main;

/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0 (zero)
	Caso contrário, retorna um valor diferente de 0 (zero).
******************************************************************************/
int cinit_queues();


/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna -9
******************************************************************************/
int dispatcher(TCB_t *thread_leaving_CPU, TCB_t *thread_arriving_CPU);



/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna diferente de zero
******************************************************************************/
int escalonador_cyield();


/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna -9

ATENÇÃO:
Função para o David usar para inserir threads bloqueadas ou recem criadas
na fila de aptos
******************************************************************************/
int insere_na_fila_de_aptos(TCB_t *thread);


/***********************************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna diferente de zero

ATENÇÃO:
Função para ser chamada quando a thread em execução foi para o estado bloqueado, e então
esse escalonador vai escolher a nova thread na fila de aptos a ser executada
*************************************************************************************************/
int escalonador_cjoin();

#endif
