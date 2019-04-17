
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"


int ccreate (void* (*start)(void*), void *arg, int prio) {
	return -1;
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


