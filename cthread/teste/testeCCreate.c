// Programa de teste para primitivas de criação e sincronização
//

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

int main(int argc, char **argv) {
	int id0, id1;
	int i = 10;

	id0 = ccreate(fatorial, (void *)&i, 0);

    printf("Threads fatorial e Fibonnaci criadas...\n");
}