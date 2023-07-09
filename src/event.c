/**
 * @file event.c
 * @author Louis CHARLES
 * @brief The files implements the event object and associated functions
 * @date 5 Mars 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "event.h"
#include "particle.h"


void print_event(event e) {
    printf("time : %lf, ", e.time);
    printf("Particle A : ");
    print_part(e.p_particle_a);
    printf(", Nombre collisions A: %d", e.nb_col_part_a);
    printf(", Particle B : ");
    print_part(e.p_particle_b);
    printf(", Nombre collisions B: %d\n", e.nb_col_part_b);
}

event* create_event(double time, p_part p_particle_a, p_part p_particle_b){
    event* new_event = malloc(sizeof(event));
    new_event->time = time;
    new_event->p_particle_a = p_particle_a;
    new_event->p_particle_b = p_particle_b;
    if (p_particle_a != NULL) new_event->nb_col_part_a = p_particle_a->nbcol;
    if (p_particle_b != NULL) new_event->nb_col_part_b = p_particle_b->nbcol;
    return new_event;
}

bool check_event(event* p_e){
    // refresh event is always valid
    if (p_e->p_particle_a == NULL && p_e->p_particle_b == NULL) return true;
    if (p_e->p_particle_a != NULL && p_e->p_particle_b == NULL) return (p_e->nb_col_part_a == p_e->p_particle_a->nbcol);
    if (p_e->p_particle_a == NULL && p_e->p_particle_b != NULL) return (p_e->nb_col_part_b == p_e->p_particle_b->nbcol);
    return ((p_e->nb_col_part_a == p_e->p_particle_a->nbcol ) && (p_e->nb_col_part_b == p_e->p_particle_b->nbcol ));
}