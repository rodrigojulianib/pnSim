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


/*E definido conflito sempre que exitir uma transicao concorrente a outra onde
elas depedem de um mesmo lugar para serem disparadas. Se um lugar entra em duas
transicoes ou mais, existe um conflito*/
void conflicts(PetriNet *p, Matrix *mconflit){
    Matrix aux;
    Matrix vectorAux;
    int i, j;

    initializeMatrix(&aux, p->pre.row, p->pre.col);
    for(i = 0; i<aux.row; i++){
        for(j=0; j<aux.col; j++){
            aux.m[i][j] = p->pre.m[i][j];
        }
    }
    showMatrix(&aux);

    normMatrix(&aux);

    initializeMatrix(mconflit, aux.col, aux.col);

    for(i=0; i<mconflit->row; i++){
        for(j=0; j<mconflit->col; j++){
            if(i == j)
                mconflit->m[i][j] = SELF;
            else
                mconflit->m[i][j] = compareTransConfli(&aux, i, j);
        }

    }
    showMatrix(mconflit);

}

int compareTransConfli(Matrix *m, int a, int b){
    int i;
    for(i=0; i<m->row; i++){
        if(m->m[i][a]==1 && m->m[i][a]==m->m[i][b]){
            return CONFLIC;
        }
    }
    return PARALEL;
}
