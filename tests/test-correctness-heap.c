/**
 * @file test-correctness-heap.c
 * @author Louis CHARLES
 * @brief Program for testing the correctness of heap module
 * @date 6 mars 2022
 * 
 */

#include <stdlib.h>
#include<stdio.h>
#include "heap.h"

int main(void) {

    heap events;
    events.nb_nodes = 0;
    events.root = NULL;

    event* p_event;
    for (int i=50; i>=1; i--){
        p_event = create_event(i, NULL, NULL);
        insert(p_event, &events);
    }
    printf("%d Events have been stored in the min heap.\n", events.nb_nodes);
    
    printf("Getting the heap events in priority order...\n");
    for (int i=0; i< 50; i++) {
        p_event = extract_min(&events);
        print_event(*p_event);
        free(p_event);
    }
    printf("DONE!\n");

    return 0;
}