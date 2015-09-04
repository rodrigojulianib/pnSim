#ifndef CPNSIM_H_INCLUDED
#define CPNSIM_H_INCLUDED

#include "matrix.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define CONTINUE -1

#define SELF -1
#define PARALEL 0
#define CONCUR 1
#define SINC 1
#define SEQUEN 1

typedef struct{
    Matrix pre, post, m;
    int steps;
} PetriNet;


void definedTransitionSim(PetriNet *p);

void stepByStepSim(PetriNet *p, int steps);

void fastFowardSim(PetriNet *p, int steps);

int ntokensok(Matrix* m);

void conflicts(PetriNet *p, Matrix *mconflit);

void concurrence(PetriNet *p, Matrix *mconflit);

void sinc(PetriNet *p, Matrix *mconflit);

void sequence(PetriNet *p, Matrix *mconflit);
#endif // CPNSIM_H_INCLUDED
