/************************
 ** Author: Luiz Leite **
 *************************/

#include "matrix.h"


void initializeMatrix(Matrix* m, unsigned int row, unsigned int col){
    if((row>ZERO)&&(col>ZERO)){
        m->row = row;//set number of rows
        m->col = col;//set number of cols

        m->m = malloc((sizeof(*(m->m))) * row);// allocate memory block with size of an content of m * number of rows
        if(m->m){//if number of rows is more than 0 the condition will be true and all array will be allocated
            int i = 0;
            for(i = 0; i< row; i++){
                m->m[i] = malloc((sizeof (**(m->m))) * col);
            }
        }
    }
    else{
        printf("Invalid dimension!");
    }
}

void setMatrix(Matrix *m){
    int i, j;
    for(i=0; i<m->row; i++){
        for(j=0; j<m->col; j++){
            printf("[%d][%d] = ", i, j);
            scanf("%d", &(m->m[i][j]));
        }
    }
}



void loadMatrix(Matrix *m, char* path){
    int i, j;
    FILE *file;
    char ch;
    int row = 0;
    int col = 1;
    int k = 0;
    int stop = 1;

    file=fopen(path, "r");
    if(file == NULL){
        printf("erro");
        exit(EXIT_FAILURE);
    }
//Set number of rows and size

    do{
        ch = fgetc(file);
        if(ch == '\n')
            row++;
    } while (ch != EOF);

    /*if(ch != '\n' && row!= 0)*/
    row++;

    //debug
    //printf("\nrows: %d\n", row);

//Set number of row



//Set number of col

    fseek(file, 0, SEEK_SET);

    while(stop){
        ch = fgetc(file);
        if(ch == ' ')
            col++;
        if ((ch == '\n') || (ch == EOF))
            stop = 0;
    }
    //debug
    //printf("\ncols: %d\n", col);
//Set number of col

//Initialize matrix

    initializeMatrix(m, row, col);

//Initialize matrix


//Set values of matrix
    char aux [5];
    fseek(file, 0, SEEK_SET);
    for(i = 0; i<row; i++){
        for(j = 0; j<col; j++){

            k = 0;
            ch = fgetc(file);
            while(ch>='0' && ch<='9'){
                aux[k] = ch;
                k++;
                ch = fgetc(file);
            }
            aux[k] = '\0';

            m->m[i][j] = atoi(aux);
        }

    }

//Set values of matrix

    fclose(file);
}



void showMatrix(Matrix *m){
    int i, j;
    for(i=0; i<m->row; i++){
        printf("| ");
        for(j=0; j<m->col; j++){
            printf("%d ", m->m[i][j]);
        }
        printf("|\n");
    }
}


void sumMatrix(Matrix* a, Matrix* b, Matrix* c){
    if((a->row==b->row)&&(a->col==b->col)){
        //freeMatrix(c);//Clean matrix result
        initializeMatrix(c, a->row, a->col); //Initialize matrix result with size of matrix a
        int i, j;
        for(i=0; i<c->row; i++){
            for(j=0; j<c->col; j++){
                c->m[i][j] = a->m[i][j] + b->m[i][j];
            }
        }
    }
    else{
        printf("Invalid dimension");
    }
}


void subMatrix(Matrix* a, Matrix* b, Matrix* c){
    if((a->row==b->row)&&(a->col==b->col)){
        //freeMatrix(c);//Clean matrix result
        initializeMatrix(c, a->row, a->col); //Initialize matrix result with size of matrix a
        int i, j;
        for(i=0; i<c->row; i++){
            for(j=0; j<c->col; j++){
                c->m[i][j] = a->m[i][j] - b->m[i][j];
            }
        }
    }
    else{
        printf("Invalid dimension");
    }
}

void findInMatrixId(Matrix *a, int value, Matrix *b){
    if((findInMatrix(a, value))){
        int i, j, k = 0;
        for(i = 0; i< a->row; i++){
            for(j=0; j<a->col; j++){
                if(a->m[i][j]==value)
                    k++;
            }
        }
        initializeMatrix(b, 1, k);
        k=0;
        for(i = 0; i< a->row; i++){
            for(j=0; j<a->col; j++){
                if(a->m[i][j]==value){
                    b->m[0][k] = j;
                    //printf("%d ", b->m[0][k]);
                    k++;

                }
            }
        }
    }
}

int findInMatrix(Matrix* a, int val){
    int i,j;
    for(i=0; i<a->row; i++){
        for(j=0; j<a->col; j++){
            if(a->m[i][j]==val)
                return 1;
        }
    }
    return 0;
}

void equalGreaterMatrix(Matrix* a, Matrix* b, Matrix* result){
    int i;
    //Matrix result;

    initializeMatrix(result, 1, a->col);
    //printf("ok");
    for(i = 0; i<a->col; i++){
        if(a->m[0][i]>=b->m[0][i]){
            result->m[0][i] = 1;
        }
        else{
            result->m[0][i] = 0;
        }
    }

}


void colToVector(Matrix* a, int col, Matrix* vecta){
    int i;
    initializeMatrix(vecta, 1, a->row);


    for(i =0; i<vecta->col;i++){
        vecta->m[0][i] = a->m[i][col];

    }
}

void normMatrix(Matrix *m){
    int i, j;
    for(i=0; i<m->row; i++){
        for(j=0; j<m->col; j++){
            if(m->m[i][j] > 0)
                m->m[i][j] /= m->m[i][j];
            else if(m->m[i][j]<0)
                m->m[i][j] /= -m->m[i][j];
        }
    }
}

//free
/*for (i = 0; i < cols; i++)
  free(ap[i]);
free(ap);
*/
