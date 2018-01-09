#ifndef DISTANCE
#define DISTANCE
#include "curve.h"

double euclidean(double* p,double* q,int dim);

int arprog(int a);

double dfd(Curve* p,Curve* q);

double dtw(Curve* p,Curve* q);

#endif
