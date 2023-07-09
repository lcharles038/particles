
/**
 * @file test-complexity-1mop-heap.c
 * @author Louis CHARLES
 * @brief Program for testing the complexity of heap fonctions
 * @date 6 mars 2022
 * 
 */

#include <stdlib.h>
#include<stdio.h>
#include "heap.h"
#include <time.h>


//static int NB_VALUE = 200;

int main(void) {
    FILE *p_file = fopen("scripts/data_complexity_1mop_heap.csv", "w");
    if (p_file == NULL) {
        fprintf(stderr, "Cannot write to file fact.txt!\n");
        exit(EXIT_FAILURE);
    }

    for (int n=20;n<12000000;n=n*2){
        printf ("Treating n=%d\n", n);
        heap events;
        events.nb_nodes = 0;
        events.root = NULL;
        event* current_event;

        event** p_event = malloc(n*sizeof(p_event));
        
        for (int i=0; i<n; i++){
            p_event[i] = malloc(sizeof(struct event));
            p_event[i]->p_particle_a = NULL;
            p_event[i]->p_particle_b = NULL;
            p_event[i]->nb_col_part_a = 0;
            p_event[i]->nb_col_part_b = 0;
            p_event[i]->time = i;
        }


        for (int i=n-1; i>=0; i--){
            insert(p_event[i], &events);
        }

        clock_t start = clock();
        for (int i=0; i<1000000; i++) {
            current_event = extract_min(&events);
            insert(current_event, &events);
        }
        clock_t end = clock();
        double elapsed_time = (double) (end - start) / CLOCKS_PER_SEC;

        for (int i=1; i< n; i++) {
            extract_min(&events);
        }

        for (int i=0; i< n; i++){
            free(p_event[i]);
        }
        free (p_event);
        
        //printf("Time to extract = %lf\n", elapsed_time_extract);
        fprintf(p_file, "%d,%lf\n", n, elapsed_time);
    }
    fclose(p_file);
    p_file = NULL;
    printf("DONE!\n");

    return 0;
}
	
	
	
