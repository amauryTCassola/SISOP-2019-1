
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

    return queues_creation_status
}


/******************************************************************************
Parâmetros:
Retorno:
	Quando executada corretamente: retorna 0
	Caso contrário, retorna -9
******************************************************************************/
int dispatcher_para_fila_de_aptos(TCB_t* thread_leaving_CPU, TCB_t* thread_arriving_CPU){

    status = 0;

    //salva o contexto da thread que está em execução e que vai perder a CPU
    getcontext(&thread_leaving_CPU->context);

    //põe a thread que vai entrar na CPU em execução
    setcontext(&thread_arriving_CPU->context);

    //coloca a thread que está saindo da execução na fila de aptos correspondente a sua prioridade
    switch(&thread_leaving_CPU->prio){
        case 0:
            status += AppendFila2(high_priority_queue, *thread_leaving_CPU);
            break
        case 1:
            status += AppendFila2(average_priority_queue, *thread_leaving_CPU);
            break
        case 2:
            status += AppendFila2(low_priority_queue, *thread_leaving_CPU);
            break
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
	Caso contrário, retorna -9
******************************************************************************/
int escalonador(){
    
}
