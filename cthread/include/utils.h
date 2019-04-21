
#ifndef __CUTILS_
#define __CUTILS_
#define PRIORITY_MAIN 3
#define CODIGO_ERRO -9
#define CODIGO_SUCESSO 0

//Declaração das 3 filas de aptos utilizada pelo escalonador: prioridades alta, média e baixa
PFILA2 high_priority_queue;
PFILA2 average_priority_queue;
PFILA2 low_priority_queue;

//Declaração da variável global que representa a thread que está em execução
TCB_t thread_in_execution;

//Declaração da variável global que representa a thread main
TCB_t thread_main;

/*-----------------------------------------------------------------------------------------
Função:	Inicializa as filas de aptos
Ret: ==0, se conseguiu
	 !=0, caso contrário (erro ou fila vazia na inicialização de alguma das filas de apto)
------------------------------------------------------------------------------------------*/
int cinit_queues();



/******************************************************************************
Parâmetros: thread que será inserida na fila de aptos
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int insere_na_fila_de_aptos(TCB_t *thread);


/***********************************************************************************************
Parâmetros:
Retorno: Retorna uma variável do tipo TCB_t que é a thread que o escalonador selecionou
*************************************************************************************************/
int escalonador();

#endif
