
#ifndef __CUTILS_
#define __CUTILS_
#define PRIORITY_MAIN 3
#define CODIGO_ERRO -1
#define CODIGO_SUCESSO 0

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
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Caso contrário, retorna CODIGO_ERRO.
******************************************************************************/
int cinit_queues();


/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Caso contrário, retorna CODIGO_ERRO
******************************************************************************/
int dispatcher(TCB_t *thread_leaving_CPU, TCB_t *thread_arriving_CPU);



/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Caso contrário, retorna CODIGO_ERRO
******************************************************************************/
int escalonador_cyield();


/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Caso contrário, retorna CODIGO_ERRO

ATENÇÃO:
Função para o David usar para inserir threads bloqueadas ou recem criadas
na fila de aptos
******************************************************************************/
int insere_na_fila_de_aptos(TCB_t *thread);


/***********************************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Caso contrário, retorna CODIGO_ERRO

ATENÇÃO:
Função para ser chamada quando a thread em execução foi para o estado bloqueado, e então
esse escalonador vai escolher a nova thread na fila de aptos a ser executada
*************************************************************************************************/
int escalonador_cjoin();

#endif
