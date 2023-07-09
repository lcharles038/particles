/**
 * @file test-particle.c
 * @author Louis CHARLES
 * @brief Test program for particle module
 * @date 05 Mars 2022
 *  
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "particle.h"
#include "loader.h"

/**
 * @brief represents a line of test case validated results (source in test/cmp/test-particle.cmp)
 * 
 */
struct result {
    char object_a[3];
    char object_b[3];
    double time_to_collision;
    struct vect velo_a;
    struct vect velo_b;
};

// global variables
static struct result* results = NULL;
static int nb_results = 0;
static double EPS = 1E-4;

// Loads the test cases results in an array of struct result, from file filename
int load_results (char* filename) {
    FILE *p_file = NULL;
    p_file = fopen(filename, "r");
    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", filename);
        exit(EXIT_FAILURE);
    }

    int nb_results = 0;
    int fscanf_result = 0;

    // skip first line that is a line of headers
    fscanf(p_file, "%*[^\n]\n");

    // read the number of results in the file
    fscanf_result = fscanf(p_file, "%d\n", &nb_results);
    if (fscanf_result != 1) {
        fprintf(stderr, "%s : Line number 1 is not syntactically correct!\n", filename);
        exit(EXIT_FAILURE);
    }
    results = malloc(nb_results * sizeof(struct result));

    // read now one result per mine
    for (int i=0; i<nb_results; i++){
        fscanf_result = fscanf(p_file, "%[^,], %[^,], %lf, (%lf , %lf), (%lf , %lf)\n", results[i].object_a, results[i].object_b, &(results[i].time_to_collision),
                                &(results[i].velo_a.x), &(results[i].velo_a.y), &(results[i].velo_b.x), &(results[i].velo_b.y));
        if (fscanf_result == EOF) {
            fprintf(stderr, "Prematured End of File at line %d\n", i+2);
            exit(EXIT_FAILURE);
        }
        if (fscanf_result < 5) {
            fprintf(stderr, "%s : line number %d is not syntactically correct!\n", filename, i+2);
            exit(EXIT_FAILURE);
        }
    }
    fclose(p_file);
    p_file = NULL;
    return nb_results;
}

struct result *get_result(char* object_a, char* object_b) {
    for(int i=0; i<nb_results;i++){
        if (strcmp(results[i].object_a, object_a)==0 && strcmp(results[i].object_b, object_b) == 0){
            return &results[i];
        }
    }
    return NULL;
}

// main takes 2 arguments
// first : filename containing the test cases
// second : file name containing the test cases validated results
int main(int argc, char **argv){

    p_part* particles;
    p_part* orig_particles;
    int nb_particles;
    char *filename = argv[1];
    char *results_file = argv[2];
    struct result *cur_result;
    char obj_a[3];
    char obj_b[3];
    
    printf("* Starting particles tests...\n");

    nb_results = load_results(results_file);
    assert (nb_results == 20);
    printf ("  +->%d results loaded -> PASSED\n", nb_results);

    // vertical wall collisions
    nb_particles = load_particles(filename, &orig_particles);
    load_particles(filename, &particles);
    printf("  |Jeu de test des chocs sur les murs verticaux...\n");
    for (int i=0; i<nb_particles;i++) {
        double tv = time_to_vertical(particles[i]);
        if (tv != INFINITY) {
            update_pos(particles[i], tv);
            update_velo_vertical(particles[i]);
        }
        sprintf(obj_a,"p%d", i+1);
        sprintf(obj_b,"v");
        cur_result = get_result(obj_a, obj_b);
        assert (cur_result != NULL);
        assert ((fabs(tv - cur_result->time_to_collision)<EPS) || ((tv == INFINITY) && (cur_result->time_to_collision == INFINITY)));
        assert (fabs(particles[i]->velo->x - cur_result->velo_a.x)<EPS);
        assert (fabs(particles[i]->velo->y - cur_result->velo_a.y)<EPS);
        printf ("    +-> Particule p%d : PASSED\n", i+1);
        free(particles[i]->pos);
        free(particles[i]->velo);
        free(particles[i]);
    }
    printf("  +-> PASSED!\n");


    // horizontal wall collisions
    nb_particles = load_particles(filename, &particles);
    printf("  |Jeu de test des chocs sur les murs horizontaux...\n");
    for (int i=0; i<nb_particles;i++) {
        double th = time_to_horizontal(particles[i]);
        if (th != INFINITY) {
            update_pos(particles[i], th);
            update_velo_horizontal(particles[i]);
        }
        sprintf(obj_a,"p%d", i+1);
        sprintf(obj_b,"h");
        cur_result = get_result(obj_a, obj_b);
        assert (cur_result != NULL);
        assert ((fabs(th - cur_result->time_to_collision)<EPS) || ((th == INFINITY) && (cur_result->time_to_collision == INFINITY)));
        assert (fabs(particles[i]->velo->x - cur_result->velo_a.x)<EPS);
        assert (fabs(particles[i]->velo->y - cur_result->velo_a.y)<EPS);
        printf ("    +-> Particule p%d : PASSED\n", i+1);
        free(particles[i]->pos);
        free(particles[i]->velo);
        free(particles[i]);
    }
    printf("  +-> PASSED!\n");

    nb_particles = load_particles(filename, &particles);
    printf("  |Jeu de test des chocs entre particules...\n");
    double tc;
    for (int i=0; i<nb_particles;i++) {
        for (int j=i+1; j<nb_particles;j++){
            tc =  time_to_collision(particles[i],particles[j]);
            if (tc != INFINITY) {
                update_pos(particles[i], tc);
                update_pos(particles[j], tc);
                update_velo_collision(particles[i], particles[j]);
                sprintf(obj_a,"p%d", i+1);
                sprintf(obj_b,"p%d", j+1);
                cur_result = get_result(obj_a, obj_b);
                assert (cur_result != NULL);
                assert (fabs(tc - cur_result->time_to_collision)<EPS);
                assert (fabs(particles[i]->velo->x - cur_result->velo_a.x)<EPS);
                assert (fabs(particles[i]->velo->y - cur_result->velo_a.y)<EPS);
                assert (fabs(particles[j]->velo->x - cur_result->velo_b.x)<EPS);
                assert (fabs(particles[j]->velo->y - cur_result->velo_b.y)<EPS);
                printf ("    +-> Particule p%d et p%d: PASSED\n", i+1, j+1);
                *(particles[i]->pos) = *(orig_particles[i]->pos);
                *(particles[i]->velo) = *(orig_particles[i]->velo);
                *(particles[j]->pos) = *(orig_particles[j]->pos);
                *(particles[j]->velo) =*(orig_particles[j]->velo);
            }
        }
        free(particles[i]->pos);
        free(particles[i]->velo);
        free(particles[i]);
    }
    
    printf("  +-> PASSED!\n");
    printf("+-> PASSED!\n");

    free (results);
    return 0;
   
}


