/**
 * @file test-event.c
 * @author Louis CHARLES
 * @brief Test program for event module
 * @date 05 Mars 2022
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "event.h"

int main(int argc, char** argv) {

    p_part p1 = create_part(0.25, 0.25, 0.5, 0, 0.5, 0.01, 1);
    p_part p2 = create_part(0.25, 0.25, -0.5, 0, 0.5, 0.01, 2);
    event* collision = malloc(sizeof(event));

    printf("Testing event module...\n");
    
    // Test event with p1 and horizontal wall
    printf("  | testing event p1 and horizontal wall collision->.. \n");
    collision = create_event(0.01, p1, NULL);
    assert(check_event(collision));
    collision->nb_col_part_a = 1;
    assert(!check_event(collision));
    p1->nbcol = 1;
    assert(check_event(collision));
    printf("  +->PASSED\n");

    // Test event with p2 and vertical wall
    printf("  | testing event p2 and vertical wall collision->.. \n");
    collision = create_event(0.01, NULL, p2);
    assert(check_event(collision));
    collision->nb_col_part_b = 1;
    assert(!check_event(collision));
    p2->nbcol = 1;
    assert(check_event(collision));
    printf("  +->PASSED\n");

    // Test event with collision between p1 and p2
    printf("  | testing event p1 and p2 collision->.. \n");
    collision = create_event(0.01, p1, p2);
    assert(check_event(collision));
    // P1 collided before
    collision->nb_col_part_a = 2;
    assert(!check_event(collision));
    p1->nbcol = 2;
    assert(check_event(collision));
    //p2 collided before
    collision->nb_col_part_b = 2;
    assert(!check_event(collision));
    p2->nbcol = 2;
    assert(check_event(collision));
    printf("  +->PASSED\n");

    free(p1);
    free(p2);

    printf("+->PASSED!\n");

    return EXIT_SUCCESS;
}

    
