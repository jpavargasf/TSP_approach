#ifndef AG_H
#define AG_H

#include"caixeiro_viajante.h"

// cromossomo = state
struct ag{
    struct seed *seed;
    struct state **population;
    //struct state **parents;
    uint16_t n_population;
    uint16_t n_parents;
    float p_mutation;

};

struct state *ag_process(struct seed *seed,uint16_t n_population,uint16_t n_parents,uint32_t max_iterations,float p_mutation);

struct ag *initialize_ag(struct seed *seed,uint16_t n_population,uint16_t n_parents,float p_mutation);

void crossover(struct state *s1, struct state *s2, struct state *result,struct seed *seed);

void mutate(uint16_t n_cities,struct state *state);

void select_parents(struct ag *ag);

#endif // AG_H
