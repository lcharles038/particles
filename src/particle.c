/**
 * @file particle.c
 * @author Louis CHARLES
 * @brief This file implements the particle object and associated functions
 * @date 05 Mars 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"


static double EPS = 1E-16;

void print_part(p_part p){
    if (p == NULL) {
        printf("NULL");
    }
    else {
        printf("position : ");
        print_vect(p->pos);
        printf(" , velocity : ");
        print_vect(p->velo);
        printf(" , mass : %lf , radius : %lf , color : %d , nb collision : %d\n", p->mass, p->radius, p->color, p->nbcol);
    }
}

void update_pos(p_part p, double t){
    (p->pos)->x = (p->pos)->x + (p->velo)->x * t;
    (p->pos)->y = (p->pos)->y + (p->velo)->y * t;
}

double time_to_vertical(p_part p){
    double vx = (p->velo)->x;
    double posx = (p->pos)->x;
    double res;
    if (vx>0){
        res = (1.0 - posx - p->radius)/(vx);
    }
    if (vx<0){
        res = (- posx + p->radius)/(vx);
    }
    if (fabs(vx)<EPS){
        res = INFINITY;
    }
    return res;
}

double time_to_horizontal(p_part p){
    double vy = (p->velo)->y;
    double posy = (p->pos)->y;
    double res;
    if (vy>0){
        res = (1.0 - posy - p->radius)/(vy);
    }
    if (vy<0){
        res = (- posy + p->radius)/(vy);
    }
    if (fabs(vy)<EPS){
        res = INFINITY;
    }
    return res;
}

void update_velo_vertical(p_part p){
    (p->velo)->x = - (p->velo)->x;
    (p->nbcol)++;
}


void update_velo_horizontal(p_part p){
    (p->velo)->y = - (p->velo)->y;
    (p->nbcol)++;
}

double time_to_collision(p_part p1, p_part p2){
    p_vect mpos1 = prod_vect_scal(p1->pos, -1);
    p_vect mvelo1 = prod_vect_scal(p1->velo, -1);
    p_vect deltap = sumvect(p2->pos,mpos1);
    p_vect deltav = sumvect(p2->velo, mvelo1);
    double deltat;
    double delta = (prodscal(deltap,deltav)*prodscal(deltap,deltav)
                    -prodscal(deltav,deltav)*(prodscal(deltap,deltap)
                    -(p1->radius+p2->radius)*(p1->radius+p2->radius)));
      
    if (delta>0) {
        deltat = -(prodscal(deltap,deltav)+pow(delta,0.5))/(prodscal(deltav,deltav));
        if (deltat < 0){
            deltat=INFINITY;
        }
    }
    else deltat=INFINITY;
    free(mpos1);
    free(mvelo1);
    free(deltap);
    free(deltav);
    return deltat;
}


void update_velo_collision(p_part p1, p_part p2){
    double r1 = p1->radius;
    double r2 = p2->radius;
    double m1 = p1->mass;
    double m2 = p2->mass;
    p_vect mpos1 = prod_vect_scal(p1->pos, -1);
    p_vect mvelo1 = prod_vect_scal(p1->velo, -1);
    p_vect deltap = sumvect(p2->pos, mpos1);
    p_vect deltav = sumvect(p2->velo, mvelo1);
    p_vect deltav1 = prod_vect_scal(deltap, 2*m2*prodscal(deltap,deltav)/((m1+m2)*(r1+r2)*(r1+r2)));
    p_vect deltav2 = prod_vect_scal(deltap, -2*m1*prodscal(deltap,deltav)/((m1+m2)*(r1+r2)*(r1+r2)));      
    p_vect vp1 = sumvect(p1->velo, deltav1);
    p_vect vp2 = sumvect(p2->velo, deltav2);
    free(mpos1);
    free(mvelo1);
    free(deltap);
    free(deltav);
    free(deltav1);
    free(deltav2);
    free(p1->velo);
    free(p2->velo);
    p1->velo = vp1;
    p2->velo = vp2;
    (p1->nbcol)++;
    (p2->nbcol)++;
}


p_part create_part(double posx, double posy, double velox, double veloy, double mass, double radius, int color){
    p_vect position = malloc(sizeof (struct vect));
    p_vect velocity = malloc(sizeof(struct vect));
    p_part new_part = malloc(sizeof (struct part));
    position->x = posx;
    position->y = posy;
    velocity->x = velox;
    velocity->y = veloy;
    new_part->pos = position;
    new_part->velo = velocity;
    new_part->mass = mass;
    new_part->radius = radius;
    new_part->nbcol = 0;
    new_part->color = color;
    return new_part;

}