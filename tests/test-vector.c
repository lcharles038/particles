/**
 * @file test-vector.c
 * @author Louis CHARLES
 * @brief Test program for vector  module
 * @date 05 Mars 2022
 *  
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "vector.h"

static double EPS= 1E-16;

void test_vector_addition() {
    printf("  | tests for addition... ");
    p_vect v1 = malloc(sizeof(struct vect));
    p_vect v2 = malloc(sizeof(struct vect));
    v1->x = 12.09;
    v2->x = 3.01;
    v1->y = 8.6;
    v2->y = -3.5;
    p_vect sum = sumvect(v1,v2);
    assert (fabs(sum->x - 15.1) < EPS);
    assert (fabs(sum->y - 5.1) < EPS);
    free(v1);
    free(v2);
    free(sum);
    printf(" Vector addition : PASSED\n");
}

void test_vector_multiplication() {
    printf("  | tests for multiplication... ");
    p_vect v1 = malloc(sizeof(struct vect));;
    p_vect v2 = malloc(sizeof(struct vect));;
    v1->x = 1.5;
    v2->x = 10.0;
    v1->y = 8;
    v2->y = -2.5;
    double prod=prodscal(v1,v2);
    assert (fabs(prod + 5.0) < EPS);
    free(v1);
    free(v2);
    printf("Vector product : PASSED\n");
}

void test_vector_scalar_multiplication(){
    printf("  | tests for scalar multiplication... ");
    p_vect v1 = malloc(sizeof(struct vect));
    v1->x = 1.5;
    v1->y = 10.0;
    double lambda = 2.5;
    p_vect res = prod_vect_scal(v1,lambda);
    assert (fabs(res->x - 3.75) < EPS);
    assert (fabs(res->y - 25.0) < EPS);
    free(v1);
    free(res);
    printf("Vector and scalar product  : PASSED\n");


}

void test_print_vector(){
    printf("  | tests for print... ");
    p_vect v1 = malloc(sizeof(struct vect));
    v1->x = 1.5;
    v1->y = 10.0;
    print_vect(v1);
    printf(" : PASSED\n");
    free(v1);
}

int main(void) {
    printf("* Starting vector tests...\n");
    test_vector_addition();
    test_vector_multiplication();
    test_vector_scalar_multiplication();
    test_print_vector();
    printf("  +-> OK!\n");
    return 0;
}