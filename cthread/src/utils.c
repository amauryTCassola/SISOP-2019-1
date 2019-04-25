
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"

/*-----------------------------------------------------------------------------------------
Função:	Inicializa as filas de aptos
Ret: ==0, se conseguiu
	 !=0, caso contrário (erro ou fila vazia na inicialização de alguma das filas de apto)
------------------------------------------------------------------------------------------*/
int cinit_queues() {
    int queues_creation_status = 0;

    queues_creation_status += CreateFila2(high_priority_queue);
    queues_creation_status += CreateFila2(average_priority_queue); 
    queues_creation_status += CreateFila2(low_priority_queue); 

	//TO-DO: criar a thread main, inicializar as vars globais, inicializar a lista de bloqueados
	
    return queues_creation_status;
}


/*-----------------------------------------------------------------------------------------
Função:	Implementação do chaveamento de contexto e do despachante (dispatcher)

Parâmetros: 
thread_leaving_cpu (ponteiro para a thread que está perdendo a CPU),
new_state_thread_leaving_cpu (novo estado da thread que está perdendo a CPU: PROCST_APTO, PROCST_BLOQ, PROCST_TERMINO)

Ret: void
------------------------------------------------------------------------------------------*/
void dispatcher(int new_state_thread_leaving_cpu){

    TCB_t* thread_arriving_CPU = (TCB_t*)malloc(sizeof(TCB_t));	//malloc retorna um ponteiro do tipo (TCB_t*)
	
	
	TCB_t* thread_leaving_cpu = thread_in_execution; //a thread que está saindo do estado de execução SEMPRE será a thread que está atualmente executando
	
	//agora precisamos que o escalonador escolha uma thread para ser executada, retire ela da fila de aptos 
	//e nos retorne uma cópia do conteúdo da thread
	//então vamos colocar esse retorno de escalonador() no ESPAÇO DE MEMÓRIA que alocamos, apontado por thread_arriving_CPU
    *thread_arriving_CPU = escalonador(); //ESPAÇO DE MEMÓRIA apontado por thread_arriving_CPU RECEBE conteúdo retornado por escalonador()
	thread_arriving_CPU->state = PROCST_EXEC; //modificamos o estado da thread_arriving_CPU para EXECUTANDO
	
	thread_leaving_cpu->state = new_state_thread_leaving_cpu; //modificamos o estado da thread_leaving_cpu para o estado passado como parâmetro

	thread_in_execution = thread_arriving_CPU; //atualiza a variável global com a thread vinda do escalonador
	
    if(new_state_thread_leaving_cpu == PROCST_APTO){
        insere_na_fila_de_aptos(thread_leaving_cpu);
		//inserimos a thread que está saindo na fila de aptos
		
		swapcontext(thread_leaving_cpu->context, thread_arriving_CPU->context);
		//salvamos na thread que está saindo o contexto atual e trocamos para o contexto da thread que está entrando
		//isto precisou ser feito pois quando a thread que está saindo voltar a executar, ela vai partir do contexto que foi salvo por último
		//que é o contexto de agora, então precisamos garantir que daqui ela volte para sua execuçao normal
		//na versão original, depois desse getcontext() tinha um setcontext() (após o if), então quando essa thread voltasse a executar,
		//ela chamaria setcontext() e não executaria corretamente
    }
    else if(new_state_thread_leaving_cpu == PROCST_TERMINO){
        //thread_leaving_cpu = NULL;
		free(thread_leaving_cpu); //queremos liberar o espaço ocupado por esta thread
		setcontext(thread_arriving_CPU->context);
    }
    else if(new_state_thread_leaving_cpu == PROCST_BLOQ){
		bloqueia(thread_leaving_cpu);
		//inserimos a thread que está saindo na fila de aptos
		swapcontext(thread_leaving_cpu->context, thread_arriving_CPU->context);
    }
}

/******************************************************************************
Parâmetros: thread que será inserida na fila de aptos
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int insere_na_fila_de_aptos(TCB_t *thread){

	int status = 0;
	PFILA2 fila_aptos_destino;
	
	thread->state = PROCST_APTO;
	
	switch(thread->prio){
		case PRIORITY_HIGH:
			fila_aptos_destino = high_priority_queue;
		    break;
		case PRIORITY_AVERAGE:
			fila_aptos_destino = average_priority_queue;
		    break;
		case PRIORITY_LOW:
			fila_aptos_destino = low_priority_queue;
		    break;
		default:
			return CODIGO_ERRO;
	}
	
	status = AppendFila2(fila_aptos_destino, thread);
	if(status == CODIGO_SUCESSO) return CODIGO_SUCESSO;
	else return CODIGO_ERRO;
}


/***********************************************************************************************
Parâmetros:
Retorno: Retorna uma variável do tipo TCB_t que é a thread que o escalonador selecionou para executar em seguida
*************************************************************************************************/
TCB_t escalonador() {

    int status;
    TCB_t chosen_thread; // variável que representa a thread que será selecionada pelo escalonador
	//chosen_thread é uma variável do tipo TCB_t (não precisamos alocar espaço pra ela, 
	//do mesmo jeito que não precisamos alocar espaço para uma variável int, por exemplo)
	
    status = FirstFila2(high_priority_queue);
    if(status == CODIGO_SUCESSO){
        chosen_thread = *GetAtIteratorFila2(high_priority_queue);
		//chosen_thread recebe o valor que está apontado pelo ponteiro retornado pela função GetAtIteratorFila2(), 
		//ou seja, se GetAtIteratorFila2() retorna o ponteiro p1, chosen_thread = *p1;
        
		DeleteAtIteratorFila2(high_priority_queue);
		//aqui ele vai liberar o espaço ocupado pelo item apontado pelo iterator da fila high_priority_queue
		//ou seja, se o iterator aponta para um ponteiro p1, essa função vai chamar free(p1)
    }
    else{
            status = FirstFila2(average_priority_queue);
            if(status == CODIGO_SUCESSO){
                chosen_thread = *GetAtIteratorFila2(average_priority_queue);
                DeleteAtIteratorFila2(average_priority_queue);
            }
            else{
                status = FirstFila2(low_priority_queue);
                if(status == CODIGO_SUCESSO){
                    chosen_thread = *GetAtIteratorFila2(low_priority_queue);
                    DeleteAtIteratorFila2(low_priority_queue);
                }
            }
    }

    return chosen_thread;
}

/******************************************************************************
Parâmetros: thread que será inserida na fila de bloqueados
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int bloqueia(TCB_t *thread){
	
	int status = 0;
	
	status = AppendFila2(blocked_queue, thread);
	
	if(status == CODIGO_SUCESSO) return CODIGO_SUCESSO;
	else return CODIGO_ERRO;
}

/******************************************************************************
Parâmetros: um tid
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int desbloqueia(int _tid){
	TCB_t* thread_a_ser_desbloqueada = (TCB_t*)malloc(sizeof(TCB_t));
	int retorno_next_fila = CODIGO_SUCESSO;
	
	FirstFila2(blocked_queue);
	
	while(retorno_next_fila == CODIGO_SUCESSO){
		if(((TCB_t*)GetAtIteratorFila2(blocked_queue))->tid == _tid) break;
		retorno_next_fila = NextFila2(blocked_queue);
	}
	
	if(retorno_next_fila == CODIGO_SUCESSO){
		*thread_a_ser_desbloqueada = *((TCB_t*)GetAtIteratorFila2(blocked_queue));
		DeleteAtIteratorFila2(blocked_queue);
		return insere_na_fila_de_aptos(thread_a_ser_desbloqueada);
	}
	else return CODIGO_ERRO;
	
}

/******************************************************************************
Parâmetros: ponteiro para um semáforo, o tid a ser inserido em uma fila de bloqueados deste semáforo e a prioridade da thread representada por este tid
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int semaforo_insere_na_fila_de_bloqueados(csem_t *_sem, int _tid, int _prio){
	t_item_fila_bloqueados_sem* item_fila = (t_item_fila_bloqueados_sem*)malloc(sizeof(t_item_fila_bloqueados_sem));
	
	item_fila->tid = _tid;
	item_fila->prio = _prio;
	
	if(AppendFila2(_sem->fila, item_fila) == CODIGO_SUCESSO) return CODIGO_SUCESSO;
	else return CODIGO_ERRO;
}

/******************************************************************************
Parâmetros: ponteiro para um semáforo
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int semaforo_retira_um_da_fila_de_bloqueados(csem_t *_sem){
	
	PFILA2 fila_origem = _sem->fila;
	t_item_fila_bloqueados_sem item;
	
	if(FirstFila2(fila_origem) == CODIGO_SUCESSO){
		item.prio = ((t_item_fila_bloqueados_sem*)GetAtIteratorFila2(fila_origem))->prio;//prioridade do primeiro item da fila
		item.tid = ((t_item_fila_bloqueados_sem*)GetAtIteratorFila2(fila_origem))->tid;//tid do primeiro item da fila
		
		while(NextFila2(fila_origem) != NXTFILA_ENDQUEUE){										//o primeiro loop encontra a maior prioridade presente na fila
			if(((t_item_fila_bloqueados_sem*)GetAtIteratorFila2(fila_origem))->prio < item.prio){
				item.prio = ((t_item_fila_bloqueados_sem*)GetAtIteratorFila2(fila_origem))->prio;
			}
		}
		
		FirstFila2(fila_origem);
		while(NextFila2(fila_origem) != NXTFILA_ENDQUEUE){										//o segundo loop seleciona o primeiro tid que tenha a maior prioridade presente
			if(((t_item_fila_bloqueados_sem*)GetAtIteratorFila2(fila_origem))->prio == item.prio){//(ou seja, garante que o iterator da fila está apontando para ele)
				item.tid = ((t_item_fila_bloqueados_sem*)GetAtIteratorFila2(fila_origem))->tid;
				break;
			}
		}
	}
	else return CODIGO_SUCESSO;//para o caso em que a fila está vazia
	
	DeleteAtIteratorFila2(fila_origem);
	
	return desbloqueia(item.tid);
}


