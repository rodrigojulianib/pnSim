#ifndef CPNSIM_H_INCLUDED
#define CPNSIM_H_INCLUDED

#include "matrix.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define CONTINUE -1
typedef struct{
    Matrix pre, post, m;
    int steps;
} PetriNet;

//Simulate petri net with a defined transition
void definedTransitionSim(PetriNet *p);
//void definedTransitionSim(int col, Matrix pre, Matrix post, Matrix m, Matrix c);

//Simulate petri net with step-by-step simulator
void stepByStepSim(PetriNet *p, int steps);
//void stepByStepSim(int col, Matrix pre, Matrix post, Matrix m, Matrix c, int steps);

void fastFowardSim(PetriNet *p, int steps);

int ntokensok(Matrix* m);
#endif // CPNSIM_H_INCLUDED
