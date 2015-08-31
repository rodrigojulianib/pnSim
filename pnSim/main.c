#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "cpnsim.h"



int main()
{
    PetriNet p;
    Matrix pre;
    Matrix post;
    //Matrix c;
    Matrix m;
    int op;
    //int col;

    /* Inicializa Matrizes */
    //Load matrix from file
    loadMatrix(&pre, "preMatrix.txt");

    printf("\nPre matrix:\n");
    showMatrix(&pre);
    printf("\n\n");

    loadMatrix(&post, "posMatrix.txt");
    printf("\nPost matrix:\n");
    showMatrix(&post);
    printf("\n\n");

    //subMatrix(&post, &pre, &c);

    loadMatrix(&m, "mMatrix.txt");

    printf("\nMarcation matrix:\n");
    showMatrix(&m);
    printf("\n\n");

    /* Inicializa Matrizes */


    /* Inicializa uma PetriNet */
        p.m = m;
        p.post = post;
        p.pre = pre;
        p.steps = 0;
    /* Inicializa uma PetriNet */


    /* Escolhe tipo de simulacao */


//    col = pre.col;

    printf("###################################\n");
    printf("                MENU               \n");
    printf("###################################\n");

    printf("1. User define transition to fire   >0    \n");
    printf("2. Step-by-step simulation          >     \n");
    printf("3. Fast Forward simulation          >>    \n");
    printf("4. Exit\n");


    do{
        printf("\nSelect a option:");
        scanf("%d", &op);
        switch (op){
            case 1:
                definedTransitionSim(&p);
                //definedTransitionSim(col, pre, post, m, c);
                break;
            case 2:
                //stepByStepSim(col, pre, post, m, c, steps);
                stepByStepSim(&p, -1);
                break;
            case 3:
                //fastFowrdSim();
                fastFowardSim(&p, -1);
                break;
            case 4:
                printf("Bye!");
                break;
            default:
                printf("Invalid option!");
                break;
            }
    }while(op<1 || op>4);
    system("pause");
    return 0;
}
    /* Escolhe tipo de simulacao */
