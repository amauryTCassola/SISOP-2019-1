
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"

int numberOfCreatedThreads = 0;
/*-----------------------------------------------------------------------------------------
Função:	Inicializa as filas de aptos
Ret: ==0, se conseguiu
	 !=0, caso contrário (erro ou fila vazia na inicialização de alguma das filas de apto)
------------------------------------------------------------------------------------------*/
int cinit_queues() {
	//TODO: teste se as 3 criações passaram.
    int queues_creation_status = 0;
/*
    queues_creation_status += CreateFila2(high_priority_queue);
    queues_creation_status += CreateFila2(average_priority_queue); 
    queues_creation_status += CreateFila2(low_priority_queue); 
*/
    return queues_creation_status;
}


/*-----------------------------------------------------------------------------------------
Função:	Implementação do chaveamento de contexto e do despachante (dispatcher)

Parâmetros: 
thread_leaving_cpu (ponteiro para a thread que está perdendo a CPU),
new_state_thread_leaving_cpu (novo estado da thread que está perdendo a CPU: PROCST_APTO, PROCST_BLOQ, PROCST_TERMINO)

Ret: void
------------------------------------------------------------------------------------------*/
void dispatcher(TCB_t *thread_leaving_cpu, int new_state_thread_leaving_cpu){
/*
    TCB_t thread_arriving_CPU = (TCB_t*)malloc(sizeof(TCB_t));    

    thread_leaving_cpu->state = new_state_thread_leaving_cpu;

    // escolhe a thread que vai chegar na CPU antes de tirar a thread que está executando na CPU
    // para evitar postergação indefinida
    thread_arriving_CPU = escalonador();
    thread_arriving_CPU.state = PROCST_EXEC;

    if(new_state_thread_leaving_cpu == PROCST_APTO){
        getcontext(thread_leaving_cpu->context);
        insere_na_fila_de_aptos(thread_leaving_cpu);
    }
    else if(new_state_thread_leaving_cpu == PROCST_TERMINO){
        thread_leaving_cpu = NULL;
    }
    else if(new_state_thread_leaving_cpu == PROCST_BLOQ){
        // FUNÇÃO QUE O AMAURY VAI FAZER QUE PÕE UMA THREAD NO ESTADO BLOQUEADO
    }

    thread_in_execution = thread_arriving_CPU; //atualiza a variável global com a thread vinda do escalonador
    setcontext(&thread_in_execution);*/
}



/******************************************************************************
Parâmetros: thread que será inserida na fila de aptos
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int insere_na_fila_de_aptos(TCB_t *thread){
/*
	int status = 0;

	thread->state = PROCST_APTO;
	
	switch(thread->prio){
		case 0:
			status += AppenFila2(high_priority_queue, thread);
		    break;
		case 1:
			status += AppenFila2(average_priority_queue, thread);
		    break;
		case 2:
			status += AppenFila2(low_priority_queue, thread);
		    break;
		default:
			status = CODIGO_ERRO;
	}
	
	if(status != 0){
        return CODIGO_ERRO;
    } 
	*/
	return CODIGO_SUCESSO;
}


/***********************************************************************************************
Parâmetros:
Retorno: Retorna uma variável do tipo TCB_t que é a thread que o escalonador selecionou
*************************************************************************************************/
/*
TCB_t escalonador() {

    int status;

    TCB_t chosen_thread = (TCB_t*)malloc(sizeof(TCB_t)); // variável que representa a thread que será selecionada pelo escalonador

    status = FirstFila2(high_priority_queue);
    if(status == 0){
        chosen_thread = *GetAtIteratorFila2(high_priority_queue);
        DeleteAtIteratorFila2(high_priority_queue);
    }
    else{
            status = FirstFila2(average_priority_queue);
            if(status == 0){
                chosen_thread = *GetAtIteratorFila2(average_priority_queue);
                DeleteAtIteratorFila2(average_priority_queue);
            }
            else{
                status = FirstFila2(low_priority_queue);
                if(status == 0){
                    chosen_thread = *GetAtIteratorFila2(low_priority_queue);
                    DeleteAtIteratorFila2(low_priority_queue);
                }
                else{
                    chosen_thread = thread_main;
                }
            }

    }

    return chosen_thread;
}*/

int InitializeCThreads()
{
	int initOk;
    //Creates main thread, with TID 0
	TCB_t *mainThread;
	mainThread = (TCB_t*)malloc(sizeof(TCB_t));
    mainThread->tid = 0;
    mainThread->prio = LOW_PRIORITY;
    mainThread->state = PROCST_EXEC;
    getcontext(&mainThread->context);
	
	numberOfCreatedThreads++;
	
	initOk = cinit_queues();
    thread_in_execution = *mainThread;

    return initOk;
}
