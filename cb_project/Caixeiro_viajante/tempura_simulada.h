#ifndef TEMPURA_SIMULADA_H
#define TEMPURA_SIMULADA_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>

#include"caixeiro_viajante.h"

struct tempera_simulada{
    struct seed *seed;
    struct state *state;
    struct state *vizinhos;
    uint32_t iterations;
    uint32_t tal;// 5 tal == <1%
};

struct tempera_simulada *initiate_tempera(struct seed *seed,uint32_t tal_constant);

float probability(struct tempera_simulada *ts);

uint8_t change_to_worse(struct tempera_simulada *ts);

struct state *tempera_process(struct seed *seed,uint32_t tal_constant,uint32_t max_iterations);

#endif // TEMPURA_SIMULADA_H
