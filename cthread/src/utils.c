
#include <stdio.h>
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
        // FUNÇÃO QUE O AMAURY VAI FAZER QUE PÕE UMA THREAD NO ESTADO BLOQUEADO
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
                else{
                    chosen_thread = thread_main;
                }
            }
    }

    return chosen_thread;
}
/******************************************************************************
Parâmetros: um tid
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int desbloqueia(int tid){
	FirstFila2(blocked_queue);
	
	
}

/******************************************************************************
Parâmetros: ponteiro para um semáforo, o tid a ser inserido em uma fila de bloqueados deste semáforo e a prioridade da thread representada por este tid
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int semaforo_insere_na_fila_de_bloqueados(csem_t *_sem, int _tid, int _prio){
	int* tid = (int*)malloc(sizeof(int));
	PFILA2 fila_destino;
	
	*tid = _tid;
	
	switch(_prio){
		case PRIORITY_HIGH:
			fila_destino = sem->high_prio_blocked_list;
		    break;
		case PRIORITY_AVERAGE:
			fila_destino = sem->avg_prio_blocked_list;
		    break;
		case PRIORITY_LOW:
			fila_destino = sem->lo_prio_blocked_list;
		    break;
		default:
			return CODIGO_ERRO;
	}
	
	if(AppendFila2(fila_destino, tid) == CODIGO_SUCESSO) return CODIGO_SUCESSO;
	else return CODIGO_ERRO;
}

/******************************************************************************
Parâmetros: ponteiro para um semáforo
Retorno:
	Quando executada corretamente: retorna CODIGO_SUCESSO
	Quando executada erroneamente: retorna CODIGO_ERRO
******************************************************************************/
int semaforo_retira_um_da_fila_de_bloqueados(csem_t *_sem){
	
	PFILA2 fila_origem;
	int tid_a_ser_desbloqueado;
	
	if(FirstFila2(_sem->high_prio_blocked_list) == CODIGO_SUCESSO) fila_origem = _sem->high_prio_blocked_list;
	else if(FirstFila2(_sem->avg_prio_blocked_list) == CODIGO_SUCESSO) fila_origem = _sem->avg_prio_blocked_list;
	else if(FirstFila2(_sem->low_prio_blocked_list) == CODIGO_SUCESSO) fila_origem = _sem->low_prio_blocked_list;
	else return CODIGO_SUCESSO; //pode ser que não exista processo bloqueado neste semáforo
	
	tid_a_ser_desbloqueado = *GetAtIteratorFila2(fila_origem);
	DeleteAtIteratorFila2(fila_origem);
	
	return desbloqueia(tid_a_ser_desbloqueado);
}


