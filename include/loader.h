#ifndef LOADER
#define LOADER

/**
 * @file loader.h
 * @brief Loads a initial situation file
 *
 * This module loads an initial situation file.\n
 * The initial situation file contains a set of particules that are defined with their properties.\n
 * The file must have the format below :\n
 *
 * Simple test with two particles
 *2
 *0.0,0.5,0.0004,0.0,0.5,0.01,4
 *0.5,0.5,0.0,0.0,0.5,0.01,3
 *
 * The first line describes the fields and will be ignored\n
 * 
 * The second line contains the number of particles in the file (int)\n 
 * 
 * The next lines describe the particles, one particle per line.\n 
 *
 * @author Louis CHARLES
 * @date 21 février 2022
 */ 

#include "particle.h"

/**
 * @brief Loads a file of particles initial state
 * 
 * @param filename The name of the file containing particles initial states
 * @param particles A pointer to an array of particles that will contain the particles after loading. Memory is allocated by the function
 * @return int The number of particles stored in the array particles
 */
int load_particles(const char* filename, p_part** particles) ;

#endif
