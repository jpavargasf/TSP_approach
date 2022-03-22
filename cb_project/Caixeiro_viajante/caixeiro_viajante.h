#ifndef CAIXEIRO_VIAJANTE_H
#define CAIXEIRO_VIAJANTE_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include<math.h>

struct city{
    uint16_t number;
    uint8_t x,y;//posição
};


struct seed{
    uint16_t n_cities;
    struct city *cities;
};

struct path{
    struct path *previous;
    struct path *next;
    struct city *city;
};

struct state{
    float evaluation;
    struct path *path_start;
};

struct seed *create_seed(char *file_name,uint16_t n_cities);

struct seed *create_aleatory_seed(uint16_t n_cities);

struct seed *open_seed(char *file_name);

uint8_t print_seed(struct seed *seed);

float distance(struct city *c1,struct city *c2);

float total_distance(struct path *path_start);

void print_path(struct path *path_start);

void push_path(struct path *path_start,struct city *city);

struct path *start_path(struct city *city);

struct path *create_blank_path(uint16_t path_size);

struct state *aleatory_state(struct seed *seed);
#endif // CAIXEIRO_VIAJANTE_H
