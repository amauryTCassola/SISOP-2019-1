// Programa de teste para primitivas de criação e sincronização
//

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

int thr1(){
    printf("OI EU SOU A THREAD 111111111\n");
    cyield();
    printf("OI EU SOU A THREAD 1 DE NOVO\n");
    cyield();
    printf("OI EU SOU A THREAD 1 TERMINANDO\n");
    return 0;
}

int thread3(){
    printf("eu sou thread 3 que so faz uma coisa\n");
    return 0;
}


int thr2(){
    int novo_id;
    printf("thread2\n");
    cyield();
    printf("thread2 again, criando nova thread\n");
    novo_id = ccreate(thread3, NULL, 1);
    cyield();
    printf("thread2 terminando\n");
    return 0;
}

int main(int argc, char **argv) {
	int id0;
	int i = 10;

	printf("thread main criando threads\n");
	id0 = ccreate(thr1, NULL, 2);
    ccreate(thr2, NULL, 0);
    cjoin(id0);
    printf("eu sou a main terminando\n");
	return 0;
}