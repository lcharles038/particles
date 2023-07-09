/**
 * @file loader.c
 * @author Louis CHARLES
 * @brief This file implements the load particles from file module
 * @date 05 Mars 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "loader.h"

int load_particles(const char* filename, p_part** particles) {
    
    FILE *p_file = NULL;

    p_file = fopen(filename, "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", filename);
        exit(EXIT_FAILURE);
    }

    int nb_particles = 0;
    int fscanf_result = 0;

    double posx=0, posy=0, vx=0, vy=0, mass=0, radius = 0;
    int color = 0;

    // skip first line that is a line of headers
    fscanf(p_file, "%*[^\n]\n");

    // read the number of particles in the file
    fscanf_result = fscanf(p_file, "%d", &nb_particles);
    if (fscanf_result != 1) {
        fprintf(stderr, "Line number 1 is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    (*particles) = malloc(nb_particles * sizeof(p_part));

    // read now one particule per line, 
    for (int i=0; i<nb_particles; i++){
        fscanf_result = fscanf(p_file, "%lf,%lf,%lf,%lf,%lf,%lf,%d", &posx, &posy, &vx, &vy, &mass, &radius, &color);
        if (fscanf_result == EOF) {
            fprintf(stderr, "Prematured End of File at line %d\n", i+2);
            exit(EXIT_FAILURE);
        }
        if (fscanf_result != 7) {
            fprintf(stderr, "Line number %d is not syntactically correct!\n", i+2);
            exit(EXIT_FAILURE);
        }
        (*particles)[i] = create_part(posx, posy, vx, vy, mass, radius, color);
    }


    fclose(p_file);
    p_file = NULL;

    return nb_particles;
}
