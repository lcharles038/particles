/**
 * @file simulation-naive.h
 * @brief Naive implementation of clash of particles
 * @author Louis CHARLES
 * @date 5 mars 2022
 *
 * Library that implements the clash of particles naive algorithm
 *
 */

#ifndef SIMULATION_NAIVE
#define SIMULATION_NAIVE

/**
 * @def SIZE
 * defines the size of the GUI window
 */
#define SIZE 900



#include "vector.h"
#include "particle.h"
#include <stdbool.h>


/**
 * @brief Function that draws the particles
 *
 * @param nb_particles The number of particles in p_part* array
 * @param cloud A pointer to an array of p_part containing particles to draw
 */
void draw_particle(int nb_particle, p_part *cloud);


/**
 * @brief Function implementing the clash of particles naive algorithm
 * 
 * @param nb_particle The number of particles
 * @param cloud A pointer to the particules array
 * @param tau_max Max time of simulation
 * @param tau_ref Refresh rate of simulation
 */
void simulate_naive(int nb_particle, p_part *cloud, double tau_max, double tau_ref);


#endif