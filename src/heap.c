/**
 * @file heap.c
 * @author Louis CHARLES
 * @brief Min heap implementation based on binary trees
 * @date 6 mars 2022
 * 
 */

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"



p_node get_father (int n, heap events) {
    assert (n>0);
    p_node p_father_node = events.root;
    int depth = (int) log2(n);
    for (int i = depth-1; i>0; i--) {
        if ((n>>i & 1) == 0) {
            p_father_node = p_father_node->left_child;
        }
        else {
            p_father_node = p_father_node->right_child;
        }
    }
    return p_father_node;
}

p_node get_min_child(p_node node) {
    if (node->left_child == NULL && node->right_child == NULL) return NULL;
    if (node->right_child == NULL) return node->left_child;
    if (node->left_child->event->time <= node->right_child->event->time) return node->left_child;
    return node->right_child;
}

int insert (event* new_event, heap* events) {

    // Create the node and put it at the first available  place in the tree
    int node_index = (events->nb_nodes)+1;
    p_node new_node = malloc(sizeof(struct node));
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->event = new_event;

    p_node father_node = get_father(node_index, *events);

    if (father_node == NULL) {  // we are creating the root node
        events->root = new_node;
        events->root->parent = NULL;
    }
    else {
        new_node->parent = father_node;
        if (node_index % 2 == 0) {
            new_node->parent->left_child = new_node;
        }
        else {
            new_node->parent->right_child = new_node;
        }
    }

    // now we have to find the right place for our node
    event* p_temp_event = NULL;
    p_node current_node = new_node;
    while (current_node->parent != NULL && (current_node->event->time < current_node->parent->event->time)) {
        p_temp_event = current_node->parent->event;
        current_node->parent->event = current_node->event;
        current_node->event = p_temp_event;
        current_node = current_node->parent;
    }

    events->nb_nodes++;
    //printf("Insert : Nodes : %d\n", events->nb_nodes);
    return events->nb_nodes;
}

event* extract_min (heap* events) {
    event* result = events->root->event;
    
    if (events->nb_nodes == 1) {
        free(events->root);
        events->root = NULL;
    }
    else { 
        // find the last leaf of the tree and put it at the root
        p_node last_leaf_father = get_father(events->nb_nodes, *events);
        if (last_leaf_father->right_child != NULL) {
                events->root->event = last_leaf_father->right_child->event;
                free(last_leaf_father->right_child);
                last_leaf_father->right_child = NULL;
        }
        else {
            events->root->event = last_leaf_father->left_child->event;
            free(last_leaf_father->left_child);
            last_leaf_father->left_child = NULL;
        }

        // now we have to find the right place for our root node
        p_node current_node = events->root;
        p_node min_child = get_min_child(current_node);
        event* p_temp_event;
        while (min_child != NULL && (current_node->event->time > min_child->event->time)) {
            p_temp_event = current_node->event;
            current_node->event = min_child->event;
            min_child->event = p_temp_event;
            current_node = min_child;
            min_child = get_min_child(current_node);
        }
    }
    events->nb_nodes--;
    //printf("Extract : Nodes : %d\n", events->nb_nodes);
    return result;
}
