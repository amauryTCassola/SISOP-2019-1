
#ifndef __CUTILS_
#define __CUTILS_
#define PRIORITY_MAIN 3
#define PRIORITY_LOW 2
#define PRIORITY_AVERAGE 1
#define PRIORITY_HIGH 0
#define CODIGO_ERRO -9
#define CODIGO_SUCESSO 0

//Declaração das 3 filas de aptos utilizada pelo escalonador: prioridades alta, média e baixa
PFILA2 high_priority_queue;
PFILA2 average_priority_queue;
PFILA2 low_priority_queue;

//declaração da "fila" de bloqueados (na verdade nós não tratamos ela com FIFO)
PFILA2 blocked_queue;

//Declaração da variável global que representa a thread que está em execução
TCB_t thread_in_execution;

//Declaração da variável global que representa a thread main
TCB_t thread_main;


//typedef da variável de semáforo
typedef struct	csem_s {
	int count;							//quantas instâncias do recurso protegido por este semáforo ainda estão disponíveis
	PFILA2 low_prio_blocked_list;			//lista de tids das threads de baixa proridade bloqueadas esperando pela liberação deste semáforo
	PFILA2 avg_prio_blocked_list;			//lista de tids das threads de média proridade bloqueadas esperando pela liberação deste semáforo
	PFILA2 high_prio_blocked_list;			//lista de tids das threads de alta proridade bloqueadas esperando pela liberação deste semáforo
} csem_t;

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
void dispatcher(int new_state_thread_leaving_cpu);

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

/******************************************************************************
Parâmetros: thread que será inserida na fila de bloqueados
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int bloqueia(TCB_t *thread);

/******************************************************************************
Parâmetros: o tid de uma thread que deve ser retirada da fila de bloqueadas e colocada na fila de aptos
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int desbloqueia(int _tid);


/******************************************************************************
Parâmetros: ponteiro para um semáforo, o tid a ser inserido em uma fila de bloqueados deste semáforo e a prioridade da thread representada por este tid
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int semaforo_insere_na_fila_de_bloqueados(csem_t *_sem, int _tid, int _prio);


/******************************************************************************
Parâmetros: ponteiro para um semáforo
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int semaforo_retira_um_da_fila_de_bloqueados(csem_t *_sem);
#endif
