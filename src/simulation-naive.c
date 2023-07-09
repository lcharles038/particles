/**
 * @file simulation-naive.c
 * @author Louis CHARLES
 * @brief  Implementation of clash of particle naive algorithm
 * @date 05 Mars 2022
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
#include "simulation-naive.h"


void draw_particle(int nb_particle, p_part* cloud){
    EmptySpace();
    for (int i=0; i<nb_particle; i++)
        DrawDISC(((cloud[i]->pos)->x)*SIZE, ((cloud[i]->pos)->y)*SIZE, (cloud[i]->radius)*SIZE, cloud[i]->color );
    UpdateScreen();
}


void simulate_naive(int nb_particle, p_part *cloud, double tau_max, double tau_ref){
    double ttc;
    event* next_event;
    double time = 0; //current time
    double time_next_redraw = tau_ref;
    next_event = create_event(time_next_redraw,NULL,NULL);
    while (time < tau_max){
        draw_particle(nb_particle, cloud); //we draw after each refreshing event
        while (time<time_next_redraw) {
            //initialisation of next_event
            next_event->p_particle_a=NULL;
            next_event->p_particle_b=NULL;
            next_event->time = time_next_redraw;

            //for each particle
            for (int i = 0; i<nb_particle; i++ ){
                //we look at collisions with vertical wall
                ttc = time_to_vertical(cloud[i]);
                if (time + ttc < next_event->time){
                    next_event->p_particle_a = NULL;
                    next_event->p_particle_b = cloud[i];
                    next_event->time = time + ttc;
                 }
                //we look at collisions with horizontal wall
                ttc = time_to_horizontal(cloud[i]);
                if (time + ttc  < next_event->time){
                    next_event->p_particle_a = cloud[i];
                    next_event->p_particle_b = NULL;
                    next_event->time = time + ttc;
                }
                //we look at collisions between the particle and the others
                for (int j = i+1; j<nb_particle;j++){
                    ttc = time_to_collision(cloud[i],cloud[j]);
                    if (time + ttc  < next_event->time){
                        next_event->p_particle_a = cloud[i];
                        next_event->p_particle_b = cloud[j];
                        next_event->time = time + ttc;
                    }
                }
            }
            //at this step, next_event contains the next event that will happen

            for (int i = 0; i<nb_particle; i++ ){
                update_pos(cloud[i],next_event->time - time ); //we update the position of every particle
            }

            //if next_event is a collision with vertical wall
            if (next_event->p_particle_a == NULL && next_event->p_particle_b != NULL){
                update_velo_vertical(next_event->p_particle_b);
            }

            //if next_event is a collision with horizontal wall
            if (next_event->p_particle_a != NULL && next_event->p_particle_b == NULL){
                update_velo_horizontal(next_event->p_particle_a);
            }

            //if next_event is a collision between two particles
            if (next_event->p_particle_a != NULL && next_event->p_particle_b != NULL){
                update_velo_collision(next_event->p_particle_a, next_event->p_particle_b);
            }
            time = next_event->time; //we update the current time
        }
        time_next_redraw = time + tau_ref; //we update next redrax time
    }

    //disallocations
    for (int i=0; i<nb_particle; i++) {
        free(cloud[i]->velo);
        free(cloud[i]->pos);
        free(cloud[i]);
    }
    free(next_event);
}