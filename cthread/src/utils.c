
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"


/*-----------------------------------------------------------------------------------------
Função:	Inicializa as filas de aptos
Ret:	==0, se conseguiu
	!=0, caso contrário (erro ou fila vazia na inicialização de alguma das filas de apto)
------------------------------------------------------------------------------------------*/
int cinit_queues() {
    int queues_creation_status = 0;

    queues_creation_status += CreateFila2(high_priority_queue);
    queues_creation_status += CreateFila2(average_priority_queue); 
    queues_creation_status += CreateFila2(low_priority_queue); 

    return queues_creation_status;
}


/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna -9
******************************************************************************/
int dispatcher(TCB_t *thread_leaving_CPU, TCB_t *thread_arriving_CPU){

    int status = 0;

    //salva o contexto da thread que está em execução e que vai perder a CPU
    getcontext(thread_leaving_CPU->context);

    //põe a thread que vai entrar na CPU em execução
    setcontext(thread_arriving_CPU->context);

    //coloca a thread que está saindo da execução na fila de aptos correspondente a sua prioridade
    switch(thread_leaving_CPU->prio){
        case 0:
            status += AppendFila2(high_priority_queue, thread_leaving_CPU);
            break;
        case 1:
            status += AppendFila2(average_priority_queue, thread_leaving_CPU);
            break;
        case 2:
            status += AppendFila2(low_priority_queue, thread_leaving_CPU);
            break;
        case PRIORITY_MAIN:
            break;
        default:
            return -9;
    }

    if(status != 0){
        return -9;
    }

    return 0;    
}


/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna diferente de 0
******************************************************************************/
int escalonador_cyield(){
    int status;
    int status_remocao_fila_aptos;
    int status_final;

    chosen_thread = (TCB_t*)malloc(sizeof(TCB_t)); // variável que representa a thread que será selecionada pelo escalonador
    executing_thread = (TCB_t*)malloc(sizeof(TCB_t));

    status = FirstFila2(high_priority_queue);
    if(status == 0){
        &chosen_thread = *GetAtIteratorFila2(high_priority_queue);
        status_remocao_fila_aptos = DeleteAtIteratorFila2(high_priority_queue);
    }
    else{
            status = FirstFila2(average_priority_queue);
            if(status == 0){
                &chosen_thread = *GetAtIteratorFila2(average_priority_queue);
                status_remocao_fila_aptos = DeleteAtIteratorFila2(average_priority_queue);
            }
            else{
                status = FirstFila2(low_priority_queue);
                if(status == 0){
                    &chosen_thread = *GetAtIteratorFila2(low_priority_queue);
                    status_remocao_fila_aptos = DeleteAtIteratorFila2(low_priority_queue);
                }
                else{
                    chosen_thread = thread_main;
                }
            }

    }

    // lembrando que thread_in_execution é a variável global que representa a thread que está em execução

    executing_thread = thread_in_execution; //guardamos a thread que está ocupando a CPU na variável executing_thread
    thread_in_execution = chosen_thread; //atualizamos a variável global que representa a thread em execução com a thread escolhida pelo escalonador
    free(chosen_thread); // desaloca a memória ocupada pela variável chosen_thread
    status_final = dispatcher(&executing_thread, &thread_in_execution);

    return status_final;
}



/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna -9

Função para o David usar para inserir threads bloqueadas ou recem criadas
na fila de aptos
******************************************************************************/
int insere_na_fila_de_aptos(TCB_t *thread){
    int status = 0;

    //coloca a thread que está saindo da execução na fila de aptos correspondente a sua prioridade
    switch(thread->prio){
        case 0:
            status += AppendFila2(high_priority_queue, thread);
            break;
        case 1:
            status += AppendFila2(average_priority_queue, thread);
            break;
        case 2:
            status += AppendFila2(low_priority_queue, thread);
            break;
        case PRIORITY_MAIN:
            break;
        default:
            return -9;
    }

    if(status != 0){
        return -9;
    }

    return 0;  
}


/***********************************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna diferente de zero

ATENÇÃO:
Função para ser chamada quando a thread em execução foi para o estado bloqueado, e então
esse escalonador vai escolher a nova thread na fila de aptos a ser executada
*************************************************************************************************/
int escalonador_cjoin() {

    int status;
    int status_fila_aptos;
    int status_remocao_fila_aptos;

    chosen_thread = (TCB_t*)malloc(sizeof(TCB_t)); // variável que representa a thread que será selecionada pelo escalonador

    status = FirstFila2(high_priority_queue);
    if(status == 0){
        &chosen_thread = *GetAtIteratorFila2(high_priority_queue);
        status_remocao_fila_aptos = DeleteAtIteratorFila2(high_priority_queue);
    }
    else{
            status = FirstFila2(average_priority_queue);
            if(status == 0){
                &chosen_thread = *GetAtIteratorFila2(average_priority_queue);
                status_remocao_fila_aptos = DeleteAtIteratorFila2(average_priority_queue);
            }
            else{
                status = FirstFila2(low_priority_queue);
                if(status == 0){
                    &chosen_thread = *GetAtIteratorFila2(low_priority_queue);
                    status_remocao_fila_aptos = DeleteAtIteratorFila2(low_priority_queue);
                }
                else{
                    chosen_thread = thread_main;
                }
            }

    }

    // lembrando que thread_in_execution é a variável global que representa a thread que está em execução

    thread_in_execution = chosen_thread; //atualizamos a variável global que representa a thread em execução com a thread escolhida pelo escalonador
    free(chosen_thread); // desaloca a memória ocupada pela variável chosen_thread
    
    // põe a thread escolhida pelo escalonador em execução
    setcontext(&thread_in_execution->context);

    return 0;
}
