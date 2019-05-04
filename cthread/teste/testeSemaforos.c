// Programa de teste para primitivas de criação e sincronização
//

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

csem_t semaforoX;
csem_t semaforoY;

float x = 0, y = 0;

int thr1(){
    printf("thr1 tentando acessar o Y\n\n");
    cwait(&semaforoY);
    printf("THR1 ACESSANDO O Y ===========================\n\n");
    cyield();
    y++;
    printf("THR1 LIBERANDO O Y =============================\n\n");
    csignal(&semaforoY);
    printf("thr1 terminando\n\n");
    return 0;
}

int thr3(int* _a){
    printf("thr 3 tentando acessar o X\n\n");
    cwait(&semaforoX);
    printf("THR3 ACESSANDO O X ============================\n\n");
    cyield();
    x++;
    x = (*_a)*x;
    cyield();
    printf("thr3, x vale %f\n\n", x);
    printf("THR3 LIBERANDO O X ============================\n\n");
    csignal(&semaforoX);
    printf("thr3 terminando\n\n");
    return 0;
}


int thr2(){
    printf("THR2 TENTANDO ACESSAR O Y\n\n");
    cwait(&semaforoY);
    printf("THR2 ACESSANDO O Y ============================\n\n");
    y++;
    cyield();
    printf("THR2 TENTANDO ACESSAR O X\n\n");
    cwait(&semaforoX);
    printf("THR2 ACESSANDO O X -------------------------\n\n");
    x = x*y;
    printf("thr2, x vale %f\n\n", x);
    printf("THR2 LIBERANDO O X -------------------------\n\n");
    csignal(&semaforoX);
    cyield();
    printf("THR2 LIBERANDO O Y ===============================\n\n");
    csignal(&semaforoY);
    printf("thr2 terminando\n\n");
    return 0;

}

int main(int argc, char **argv) {
	int a = 3;
    printf("thread main inicializando semaforos\n\n");

    csem_init(&semaforoX, 1);
    csem_init(&semaforoY, 1);
    

	ccreate(thr1, NULL, 0);
    ccreate(thr2, NULL, 0);
    ccreate(thr3, &a, 0);
    
    printf("thread main cyield\n\n");
    cyield();

    printf("eu sou a main terminando\n\n");
	return 0;
}