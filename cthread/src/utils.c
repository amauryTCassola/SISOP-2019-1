
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"

//Declaração das 3 filas de aptos utilizada pelo escalonador: prioridades alta, média e baixa
PFILA2 high_priority_queue;
PFILA2 average_priority_queue;
PFILA2 low_priority_queue;


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
