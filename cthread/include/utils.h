
#ifndef __CUTILS_

#define __CUTILS_


//Declaração das 3 filas de aptos utilizada pelo escalonador: prioridades alta, média e baixa
PFILA2 high_priority_queue;
PFILA2 average_priority_queue;
PFILA2 low_priority_queue;

//Declaração da thread que está em execução
TCB_t thread_in_execution;

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
int dispatcher_cpu_fila_de_aptos(TCB_t thread_leaving_CPU, TCB_t thread_arriving_CPU);

/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna -9
******************************************************************************/
int escalonador();


#endif
