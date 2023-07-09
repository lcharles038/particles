/**
 * @file clash-of-particles-naive.c
 * @author Louis CHARLES
 * @brief This application launches the clash of particles naive simulation
 * @date 5 mars 2022
 * 
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "loader.h"
#include "disc.h"
#include "particle.h"
#include "simulation-naive.h"



/**
 * @brief Launches the simulation
 * 
 * @param argc Number of command line arguments
 * @param argv Command lines arguments array
 * @return int The exit status
 */
int main (int argc, char **argv){
    p_part *cloud;
    int nb_particle = load_particles(argv[1],&cloud);
    //double tau_max = atof (argv[2]);
    double tau_max = 50000;
    //double tau_ref = atof (argv[3]);
    double tau_ref = 2;
    CreateWindow("clash-of-particles-naive", SIZE, SIZE);
    simulate_naive(nb_particle,cloud,tau_max, tau_ref);
    CloseWindow();
    free (cloud);
    return EXIT_SUCCESS;

}
