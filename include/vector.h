#ifndef VECTOR
#define VECTOR

/**
 * @file vector.h
 * @brief This file defines vector structure and associated functions
 *
 * @author Louis Charles
 * @date 20 Feb 2022
 */ 

/**
 * @brief Structure definition for vector object
 * 
 */

struct vect {
    double x;   /** first coordinate of vector*/
    double y;   /** second coordinate of vector*/

};

/**
 * @brief Struct definition for pointer to vector
 * 
 */
typedef struct vect *p_vect;


/**
 * This function returns the sum of two vectors
 *
 * @param v1 is first vector
 * @param v2 second vector
 * @return the sum of vectors - Memory allocated by function.
 */
p_vect sumvect(p_vect v1, p_vect v2);

/**
 * This function returns the scalar product of two vectors
 *
 * @param v1 is first vector
 * @param v2 second vector
 * @return the scalar product of vectors
 */
double prodscal(p_vect v1, p_vect v2);



/**
 * This function returns the product between a scalar and a vector
 *
 * @param v is the vector
 * @param lambda is the scalar
 * @return the product of vector v and real lambda - memory allocated by function.
 */
p_vect prod_vect_scal(p_vect v, double lambda);




/**
 * This function prints a vector
 *
 * @param v is the vector to print
 */
void print_vect(p_vect v);


#endif