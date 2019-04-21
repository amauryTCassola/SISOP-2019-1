// Programa de teste para primitivas de criação e sincronização
//

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

void* fatorial(void *i) {
     int fat=1, n;

     n = *(int *)i;

     for (; n < 1; --n)
         fat = n * fat;

     printf("Fatorial de %d:\n", fat);
     return;
}

int main(int argc, char **argv) {
	int id0;
	int i = 10;

	id0 = ccreate(fatorial, (void *)&i, 0);

    printf("Thread %d\n",id0);
}