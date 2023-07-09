/**
 * @file vector.c
 * @author Louis CHARLES
 * @brief  Implementation of vector object and associated functions
 * @date 05 Mars 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

void print_vect(p_vect v){
    if (v == NULL) {
        printf ("NULL");
    }
    else {
        printf("(%lf , %lf)", v->x, v->y);
    }
}

p_vect sumvect(p_vect v1, p_vect v2){
    p_vect sum = malloc(sizeof(struct vect));
    sum->x = v1->x + v2->x;
    sum->y = v1->y + v2->y;
    return sum;
}

double prodscal(p_vect v1, p_vect v2){
    double res;
    double a = v1->x * v2->x;
    double b = v1->y * v2->y;
    res = a + b;
    return res;
}


p_vect prod_vect_scal(p_vect v, double lambda){
    p_vect res = malloc (sizeof(struct vect));
    res->x = lambda * (v->x);
    res->y = lambda * (v->y);
    return res;
}

