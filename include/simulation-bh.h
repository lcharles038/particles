/**
 * @file simulation-bh.h
 * @brief Binary heap implementation of clash of particles
 * @author Louis CHARLES
 * @date 10 mars 2022
 *
 * Library that implements the clash of particles bh algorithm
 *
 */

#ifndef SIMULATION_BH
#define SIMULATION_BH

/**
 * @def SIZE
 * defines the size of the GUI window
 */
#define SIZE 900



#include "vector.h"
#include "particle.h"
#include "heap.h"
#include <stdbool.h>

/**
 * @brief Function that draws the particles
 *
 * @param nb_particles The number of particles in p_part* array
 * @param cloud A pointer to an array of p_part containing particles to draw
 */
void draw_particle_bh(int nb_particle, p_part *cloud);


/**
 * @brief Function that adds all the events dealing with one particule in the heap 
 *
 * @param p_heap is a pointer to the heap containing the events
 * @param p_particle is a pointer to the particle we want to add the next possible events
 * @param time_event is the time of the event in which the particle was just involved
 * @param nb_particles The number of particles in p_part* array
 * @param cloud A pointer to an array of p_part containing particles to draw
 */
void add_events(heap* p_heap, p_part p_particle, double time_event, int nb_particle, p_part *cloud);

/**
 * @brief Function implementing the clash of particles bh algorithm
 * 
 * @param nb_particle The number of particles
 * @param cloud A pointer to the particules array
 * @param tau_max Max time of simulation
 * @param tau_ref Refresh rate of simulation
 */
void simulate_bh(int nb_particle, p_part *cloud, double tau_max, double tau_ref);


#endif

