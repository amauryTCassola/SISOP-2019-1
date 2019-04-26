
#ifndef __CUTILS_
#define __CUTILS_
#define PRIORITY_MAIN 3
#define CODIGO_ERRO -9
#define CODIGO_SUCESSO 0

#define STACK_SIZE 4096
#define INITIALTID 1

#define HIGH_PRIORITY 0
#define MEDIUM_PRIORITY 1
#define LOW_PRIORITY 2

#define ERRO -1
#define ERRO_INIT -2
#define ERRO_PARAM -3
#define ERRO_FILAS -4

#define ERRO_NAO_EXISTE -3
#define ERRO_JA_RELEASER -4
#define SUCEDIDO 1
#define FALHOU 0

#define END_CONTEXT 0

typedef struct s_BLOCK_RELEASER{
  int tidBlock;
  int tidReleaser;
} BLOCK_RELEASER;

//Declaração das 3 filas de aptos utilizada pelo escalonador: prioridades alta, média e baixa
PFILA2 high_priority_queue;
PFILA2 average_priority_queue;
PFILA2 low_priority_queue;

//declaração da "fila" de bloqueados (na verdade nós não tratamos ela com FIFO)
PFILA2 blocked_queue;

PFILA2 releaserTids;

extern int numberOfCreatedThreads;

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

/*-----------------------------------------------------------------------------------------
Função:	Implementação do chaveamento de contexto e do despachante (dispatcher)

Parâmetros: 
thread_leaving_cpu (ponteiro para a thread que está perdendo a CPU),
new_state_thread_leaving_cpu (novo estado da thread que está perdendo a CPU: PROCST_APTO, PROCST_BLOQ, PROCST_TERMINO)

Ret: void
------------------------------------------------------------------------------------------*/
void dispatcher(TCB_t *thread_leaving_cpu, int new_state_thread_leaving_cpu);

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
TCB_t escalonador();

int InitializeCThreads();

void* endExecScheduler();

void* cjoin_release(void *block_releaser_in);

int threadExists(int tid);

int isThreadReleaser(int tid);
	
void setThreadAsReleaser(int releaserTid);

void removeThreadAsReleaser(int releaserTid);

TCB_t* getThread(int tid);

#endif
