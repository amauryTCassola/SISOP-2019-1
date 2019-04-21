
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/utils.h"


int ccreate (void* (*start)(void*), void *arg, int prio) {
	
	TCB_t *newThread;

    if(numberOfCreatedThreads == INITIALTID) 
    {
      int initializedCorrectly = 1;//TODO InitializeCThreads();
      if(initializedCorrectly != 0)
      {
          return ERRO_INIT;
      }
    }
	if(prio<0 || prio>2){
		return ERRO_PARAM;
	}

    //Initializes the new thread's TCB
    newThread = (TCB_t*)malloc(sizeof(TCB_t));
    newThread->prio = prio;
    newThread->state = PROCST_APTO;
    newThread->tid = numberOfCreatedThreads;
    
    //Initializes the new thread's context
    getcontext(&newThread->context);
    //newThread->context.uc_link = &endExecSchedulerContext;
    newThread->context.uc_stack.ss_sp = (char *) malloc(STACK_SIZE);
    newThread->context.uc_stack.ss_size = STACK_SIZE;
    makecontext(&newThread->context, (void(*)(void))start, 1, arg);

    //Refresh number of threads created
	numberOfCreatedThreads++;
	return numberOfCreatedThreads;
}

int csetprio(int tid, int prio) {
	return -1;
}

int cyield(void) {
	return -1;
}

int cjoin(int tid) {
	return -1;
}

int csem_init(csem_t *sem, int count) {
	return -1;
}

int cwait(csem_t *sem) {
	return -1;
}

int csignal(csem_t *sem) {
	return -1;
}

int cidentify (char *name, int size) {
        char[] components = "Amaury Teixeira Cassola 287704\nBruno Ramos Toresan 291332\nDavid Mees Knijnik 264489";
	strncpy(name, components, size);
	return 0;
}


