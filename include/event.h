#ifndef EVENT
#define EVENT

/**
 * @file event.h
 * @author Louis CHARLES
 * @brief This file implements the event object
 * @date 05 Mars 2022
 * 
 */

#include <stdbool.h>
#include "vector.h"
#include "particle.h"

/**
 * @brief Event structure definition
 * 
 */
struct event {
    double time;            /** Time of event*/
    p_part p_particle_a;    /** First particle implied in event if any*/
    p_part p_particle_b;    /** Second particle implied in event if any*/
    int nb_col_part_a;      /** Number of collision for particle_a since start of simulation*/
    int nb_col_part_b;      /** Number of collision for particle_b since start of simulation*/

};

/**
 * @brief Event structure definition
 * 
 */
typedef struct event event;


/**
 * This function creates an event 
 *
 * @param time is the time of the event
 * @param p_particle_a is the particle a
 * @param p_particle_b is the particle b
 */

event* create_event(double time, p_part p_particle_a, p_part p_particle_b);


/**
 * @brief Chechs if event is valid
 * 
 * An event is valid if the nb of collisions in the event
 * equals the number of collisions for each particle when checked
 * 
 * @param p_e : a poiter to the event to check
 * @return true if event is valid
 * @return false if event is invalid
 */
bool check_event(event* p_e);

/**
 * @brief Prints an event for debugging purpose
 * 
 * @param e the event to print
 */
void print_event(event e);


#endif