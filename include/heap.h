#ifndef HEAP
#define HEAP

/**
 * @file heap.h
 * @author Louis CHARLES
 * @brief Min Heap implementation based on binary tree
 * @date 6 mars 2022
 * 
 */

#include "event.h"

/**
 * @brief Node structure definition
 * 
 */
struct node {
    event* event;       /** the node value is an event*/
    struct node* left_child;   /** left child node*/
    struct node* right_child;  /** right child node*/
    struct node* parent;       /** parent node*/
};

/**
 * @brief p_node is a pointer to a node
 * 
 */
typedef struct node* p_node;

/**
 * @brief Heap structure definition
 * 
 */
struct heap {
    int nb_nodes;       /** number of nodes in the heap */
    p_node root;        /** pointer to the root node */
};

/**
 * @brief Heap structure definition
 * 
 */
typedef struct heap heap;

/**
 * @brief Get the father of the n th node
 * 
 * @param n The node number
 * @param events The events heap
 * @return p_node The n nodes'parent
 */
p_node get_father (int n, heap events) ;

/**
 * @brief Get the min child object that has the min time
 * 
 * @param event the node parent event
 * @return p_node the node whose event has the min time
 */
p_node get_min_child(p_node node);

/**
 * @brief Return the event with the smallest time_to_collision
 * 
 * @param events the events heap
 * @return event* the event with the min time_to_collision
 */
event* extract_min (heap* events);

/**
 * @brief Inserts a new event in the evants heap
 * 
 * @param new_event The event to insert
 * @param events    Events heap
 * @return int      The number of events in the heap
 */
int insert (event* new_event, heap* events);



#endif