#ifndef PARTICLE
#define PARTICLE

/**
 * @file particle.h
 * @author Louis CHARLES
 * @brief This file defines particle structure and associated functions
 * @date 05 mars 2022
 * 
 */

#include "vector.h"

/**
 * @brief Structure of a particle object
 * 
 */
struct part {
    p_vect pos;     /** vector representing the particle position*/
    p_vect velo;    /** vector representing the particle velocity*/
    double mass;    /** the particle mass*/
    double radius;  /** the particle radius*/
    int nbcol;      /** the number of collision of the particle since simulation start*/    
    int color;      /** the particle color*/

};

/**
 * @brief The type defining a pointer to a part
 * 
 */
typedef struct part *p_part;

/**
 * This function updates a particle position given an amount of time 
 *
 * @param p is the particle
 * @param t is the amount of time
 */

void update_pos(p_part p, double t);


/**
 * This function computes the expected time for a particle to collide a vertical wall
 *
 * @param p is the particle
 * @return time to collision
 */

double time_to_vertical(p_part p);


/**
 * This function computes the expected time for a particle to collide an horizontal wall
 *
 * @param p is the particle
 * @return time to collision
 */

double time_to_horizontal(p_part p);


/**
 * This function updates the velocity of a particle after collision with a vertical wall
 *
 * @param p is the particle
 */

void update_velo_vertical(p_part p);


/**
 * This function updates the velocity of a particle after collision with an horizontal wall
 *
 * @param p is the particle
 */

void update_velo_horizontal(p_part p);


/**
 * This function computes the expected time of the collision between two particles
 *
 * @param p1 is the first particle
 * @param p2 is the second particle
 * @return time to collision
 */

double time_to_collision(p_part p1, p_part p2);


/**
 * This function updates the velocities of the two particles after collision 
 *
 * @param p1 is the first particle
 * @param p2 is the second particle
 */

void update_velo_collision(p_part p1, p_part p2);


/**
 * This function prints a particle
 *
 * @param p is the particle
 */

void print_part(p_part p);

/**
 * This function creates a particle - The memory allocatin is done by function.
 *
 * @param posx is the particle position on the x axe
 * @param posy is the particle position on the y axe
 * @param velox is the particle velocity on the x axe
 * @param veloy is the particle position on the y axe
 * @param mass is the particle mass 
 * @param radius is the particle radius 
 * @param color is the particle color
 * @return the created particle (memory allocated by function)
 */

p_part create_part(double posx, double posy, double velox, double veloy, double mass, double radius, int color);




#endif 