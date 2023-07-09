/**
 * @file test-loader.c
 * @author Louis CHARLES
 * @brief Test program for particle loader module
 * @date 05 Mars 2022
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include "loader.h"

int main(int argc, char** argv) {

    int option;
    char *filename = NULL;

    while((option = getopt(argc, argv, "f:")) != -1) 
    { 
        switch(option) 
        { 
            case 'f': 
                filename = optarg; 
                break; 
            case '?': 
                if (optopt == 'f')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                   "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                exit (EXIT_FAILURE);
        } 
    } 

    if (filename != NULL)
        printf ("Loader will load file %s\n", filename);
    else {
        fprintf (stderr, "-f option is mandatory\n");
        exit(EXIT_FAILURE);
    }

    p_part* particles;
    int nb_particles;

    nb_particles = load_particles(filename, &particles);
    printf("%d particles loaded.\n", nb_particles);
    
    for (int i=0; i<nb_particles;i++) {
        print_part(particles[i]);
        free(particles[i]->pos);
        free(particles[i]->velo);
        free(particles[i]);
    }
    
    return EXIT_SUCCESS;
}

    
