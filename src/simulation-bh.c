/**
 * @file simulation-bh.c
 * @author Louis CHARLES
 * @brief  Implementation of clash of particle bh algorithm
 * @date 10 Mars 2022
 * 
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "particle.h"
#include "event.h"
#include "disc.h"
#include "simulation-bh.h"


void draw_particle_bh(int nb_particle, p_part* cloud){
    EmptySpace();
    for (int i=0; i<nb_particle; i++)
        DrawDISC(((cloud[i]->pos)->x)*SIZE, ((cloud[i]->pos)->y)*SIZE, (cloud[i]->radius)*SIZE, cloud[i]->color );
    UpdateScreen();
}

void add_events(heap* p_heap, p_part p_particle, double time_event, int nb_particle, p_part *cloud){
    double next_collision_time; //represents the relative time between current time and the time of the next collision we study
    event* next_event; // will be the event to add in the heap

    //we add the event dealing with vertical walls
    next_collision_time = time_to_vertical(p_particle);
    if (next_collision_time != INFINITY){
        next_event = create_event(time_event + next_collision_time, NULL, p_particle);
        insert(next_event,p_heap);
    }

    //we add the event dealing with horizontal walls
    next_collision_time = time_to_horizontal(p_particle);
    if (next_collision_time != INFINITY){
        next_event = create_event(time_event + next_collision_time, p_particle, NULL);
        insert(next_event,p_heap);
    }

    //we add all the possible collisions between the particle and all the others
    for (int j = 0; j<nb_particle;j++){
        if (p_particle != cloud[j]) {   //particles should be different
            next_collision_time = time_to_collision(p_particle,cloud[j]);
            if(next_collision_time != INFINITY) {  //we only add events that can happen
                next_event = create_event(time_event + next_collision_time, p_particle, cloud[j]);
                insert(next_event,p_heap);
            }
        }
        
    }
}

void simulate_bh(int nb_particle, p_part *cloud, double tau_max, double tau_ref){
    heap* p_heap = malloc(sizeof(heap));  //create our heap of events
    p_heap->nb_nodes = 0;
    p_heap->root = NULL;
    double time = 0;   //initializes the current time
    event* p_e = NULL;  //will represent the current event
    event* next_event = NULL;  //will represent events to insert in the heap
    
    //we first add all the events each particle are involved in
    for (int i = 0; i<nb_particle; i++ ){
        add_events(p_heap, cloud[i], 0, nb_particle, cloud);
    }

    next_event = create_event(0, NULL, NULL);  //first refreshing event
    insert(next_event,p_heap);
    while(p_heap->nb_nodes != 0 && time < tau_max){
        p_e = extract_min(p_heap);  //we catch the first event to happen
        //we check if this event is correct
        if (check_event(p_e)){
            //we update the positions of every particle at the time of the event p_e
            for (int i = 0; i<nb_particle; i++ ){
                update_pos(cloud[i],p_e->time - time );
            }
            //if p_e is a refreshing event
            if (p_e->p_particle_a == NULL && p_e->p_particle_b == NULL){
                draw_particle_bh(nb_particle, cloud);
                next_event = create_event(p_e->time + tau_ref,NULL,NULL); //we add the next refreshing event in the heap
                insert(next_event,p_heap);
            }
            
            //if the event is a collision with a vertical wall
            if (p_e->p_particle_a == NULL && p_e->p_particle_b != NULL){
                update_velo_vertical(p_e->p_particle_b);
                add_events(p_heap, p_e->p_particle_b, p_e->time, nb_particle, cloud);
            }

            //if the event is a collision with an horizontal wall
            if (p_e->p_particle_a != NULL && p_e->p_particle_b == NULL){
                update_velo_horizontal(p_e->p_particle_a);
                add_events(p_heap, p_e->p_particle_a, p_e->time, nb_particle, cloud);
            }
            
            //if the event is a collision between two particles
            if (p_e->p_particle_a != NULL && p_e->p_particle_b != NULL){
                update_velo_collision(p_e->p_particle_a, p_e->p_particle_b);
                add_events(p_heap, p_e->p_particle_b, p_e->time, nb_particle, cloud);
                add_events(p_heap, p_e->p_particle_a, p_e->time, nb_particle, cloud);
            }
            time = p_e->time; //we update the current time
        }
        free(p_e);
    }
    //disallocations
    while(p_heap->nb_nodes>0) {
        free(extract_min(p_heap));
    }

    for (int i=0; i<nb_particle; i++) {
        free(cloud[i]->velo);
        free(cloud[i]->pos);
        free(cloud[i]);
    }
    free(p_heap);

}





