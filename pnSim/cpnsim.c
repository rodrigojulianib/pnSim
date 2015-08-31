#include "cpnsim.h"

int ntokensok(Matrix* m){
    int enabled = 1;
    if(findInMatrix(m, 0)){
        enabled = 0;
    }
    return enabled;
}

void definedTransitionSim(PetriNet *p){

    //Verifica na rede trasicoes habilitadas
    Matrix trHab;
    Matrix vect;
    Matrix aux;
    int i, opt;

    initializeMatrix(&trHab, 1, p->pre.col);

    for(i=0; i<p->pre.col; i++){
        colToVector(&(p->pre), i, &vect);
        equalGreaterMatrix(&(p->m), &vect, &aux);
        trHab.m[0][i] = ntokensok(&aux);
    }
    findInMatrixId(&trHab, TRUE, &vect);

    //Comeca laco: que roda enquanto existir pelo menos uma transicao habilitada
    while(findInMatrix(&trHab, TRUE)){
        //mostra transicoes habilitadas;
        printf("--------------");
        showMatrix(&trHab);
        printf("--------------");

        findInMatrixId(&trHab, TRUE, &vect);
        //escolhe transicao para disparar;
        do{
            printf("Select a transition to fire [0 - %d]:", trHab.col-1);
            scanf("%d", &opt);

        }while(!findInMatrix(&vect, opt));

        //Verifica as novas marcacoes
        subMatrix(&(p->post), &(p->pre), &aux);
        colToVector(&aux, opt, &vect);
        sumMatrix(&(p->m), &vect, &aux);
        p->m = aux;

        //Verifica na rede trasicoes habilitadas
        for(i=0; i<p->pre.col; i++){
            colToVector(&(p->pre), i, &vect);
            equalGreaterMatrix(&(p->m), &vect, &aux);
            trHab.m[0][i] = ntokensok(&aux);
        }

        //Mostra marcacao;
        printf("--------------");
        showMatrix(&(p->m));
        printf("--------------");

        //Termina laco
        p->steps++;
    }
    printf("\nNao exitem mais transicoes habilitadas\n");
    printf("\nSimulacao concluida com %d passos\n", p->steps);
}


void stepByStepSim(PetriNet *p, int steps){
//Verifica na rede trasicoes habilitadas
    //int curStep = 0;
    Matrix trHab;
    Matrix vect;
    Matrix aux;
    int i, opt;
    clock_t t;
    initializeMatrix(&trHab, 1, p->pre.col);
    t = clock();
    for(i=0; i<p->pre.col; i++){
        colToVector(&(p->pre), i, &vect);
        equalGreaterMatrix(&(p->m), &vect, &aux);
        trHab.m[0][i] = ntokensok(&aux);
    }
//Mostra transicoes habilitadas
    //showMatrix(&trHab);
//encontra id's validos para transicao;
    findInMatrixId(&trHab, TRUE, &vect);
    /*printf("\n");
    showMatrix(&vect);*/

//Comeca laco: que roda enquanto existir pelo menos uma transicao habilitada
    while((findInMatrix(&trHab, TRUE))&& ((steps>0) || (steps == CONTINUE))){
        //mostra transicoes habilitadas;
        printf("Step: %d\nTransicoes habilitadas: \n", p->steps);
        showMatrix(&trHab);
        printf("\n");

        //Mostra marcacao;
        printf("Marcacao:\n");
        showMatrix(&(p->m));
        printf("\n");

        srand((unsigned)time(NULL));
        //escolhe transicao para disparar;
        opt = vect.m[0][rand()%vect.col];
        //opt = random_at_most(vect.col);

        printf("Fired transition: %d", opt);

        //Verifica as novas marcacoes
        subMatrix(&(p->post), &(p->pre), &aux);
        colToVector(&aux, opt, &vect);
        sumMatrix(&(p->m), &vect, &aux);
        p->m = aux;

        //Verifica na rede trasicoes habilitadas
        for(i=0; i<p->pre.col; i++){
            colToVector(&(p->pre), i, &vect);
            equalGreaterMatrix(&(p->m), &vect, &aux);
            trHab.m[0][i] = ntokensok(&aux);
        }
        findInMatrixId(&trHab, TRUE, &vect);

        //Mostra marcacao;
        printf("\n\nMarcacao resultante");
        showMatrix(&(p->m));
        printf("\n\n\n");


        p->steps++;

        if(steps>0){
            steps--;
        }
    }
    if(steps == 0){
        printf("Numero de passos solicitados foram efetuados\n");
    }
    if(!findInMatrix(&trHab, TRUE)){
        printf("\nNao exitem mais transicoes habilitadas\n");
    }
    printf("\nSimulacao concluida com %d passos\n", p->steps);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}


void fastFowardSim(PetriNet *p, int steps){
    //Verifica na rede trasicoes habilitadas
    //int curStep = 0;
    Matrix trHab;
    Matrix vect;
    Matrix aux;
    int i, opt;
    clock_t t;
    initializeMatrix(&trHab, 1, p->pre.col);
    t = clock();
    for(i=0; i<p->pre.col; i++){
        colToVector(&(p->pre), i, &vect);
        equalGreaterMatrix(&(p->m), &vect, &aux);
        trHab.m[0][i] = ntokensok(&aux);
    }
//Mostra transicoes habilitadas
    //showMatrix(&trHab);
//encontra id's validos para transicao;
    findInMatrixId(&trHab, TRUE, &vect);
    /*printf("\n");
    showMatrix(&vect);*/

//Comeca laco: que roda enquanto existir pelo menos uma transicao habilitada
    while((findInMatrix(&trHab, TRUE))&& ((steps>0) || (steps == CONTINUE))){
        //mostra transicoes habilitadas;
       /* printf("Step: %d\nTransicoes habilitadas: \n", p->steps);
        showMatrix(&trHab);
        printf("\n");
        */
        //Mostra marcacao;
  /*      printf("Marcacao:\n");
        showMatrix(&(p->m));
        printf("\n");
*/
        srand((unsigned)time(NULL));
        //escolhe transicao para disparar;
        opt = vect.m[0][rand()%vect.col];
        //opt = random_at_most(vect.col);

       // printf("Fired transition: %d", opt);

        //Verifica as novas marcacoes
        subMatrix(&(p->post), &(p->pre), &aux);
        colToVector(&aux, opt, &vect);
        sumMatrix(&(p->m), &vect, &aux);
        p->m = aux;

        //Verifica na rede trasicoes habilitadas
        for(i=0; i<p->pre.col; i++){
            colToVector(&(p->pre), i, &vect);
            equalGreaterMatrix(&(p->m), &vect, &aux);
            trHab.m[0][i] = ntokensok(&aux);
        }
        findInMatrixId(&trHab, TRUE, &vect);



        p->steps++;

        if(steps>0){
            steps--;
        }
    }
    if(steps == 0){
        printf("Numero de passos solicitados foram efetuados\n");
    }
    if(!findInMatrix(&trHab, TRUE)){
        printf("\nNao exitem mais transicoes habilitadas\n");
    }
    printf("\nSimulacao concluida com %d passos\n", p->steps);

    //Mostra marcacao;
    printf("\n\nMarcacao resultante");
    showMatrix(&(p->m));
    printf("\n\n");

    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

}
/*void stepByStepSim(int col, Matrix pre, Matrix post, Matrix m, Matrix c, int steps){
    int i;
    Matrix trHab;
    Matrix aux;
    Matrix nm;
    Matrix preLine;
    Matrix idTrHab;
    int e;
    int opt;
    int curStep = 0;

    initializeMatrix(&trHab, 1, col);


    clock_t t;
    t = clock();
    for(i=0; i<col; i++){
        colToVector(&pre, i, &preLine);
        equalGreaterMatrix(&m, &preLine, &aux);
        trHab.m[0][i] = ntokensok(&aux);
    }

    printf("Transicoes habilitadas para Marcacao inicial:");
    showMatrix(&trHab);

    findInMatrixId(&trHab, 1, &idTrHab);
    printf("\n");
    //getchar();
    showMatrix(&idTrHab);
    printf("\n");
    while(findInMatrix(&trHab, 1) && curStep<steps){
        curStep++;
        e = round(((idTrHab.col-1) * rand()));

        opt = idTrHab.m[0][e];

        aux.row = m.row;
        aux.col = m.col;
        aux.m[0] = c.m[opt];
        sumMatrix(&m, &aux, &nm);
        m = nm;

        for(i=0; i<col; i++){
            colToVector(&pre, i, &preLine);
            equalGreaterMatrix(&m, &preLine, &aux);
            trHab.m[0][i] = ntokensok(&aux);
        }

        printf("Marcacao atual:\n");
        showMatrix(&m);
        printf("\npasso: %d\n", curStep);
        findInMatrixId(&trHab, 1, &idTrHab);

    }
    printf("\nNão existem mais transições habilitadas");
    printf("Simulação concluida em %d passos\n", curStep);

    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}*/

