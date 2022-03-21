#include<stdlib.h>
#include<stdio.h>

#include"caixeiro_viajante.h"
#include"tempura_simulada.h"

int main(){
    srand(time(NULL));
    //struct seed *seed = create_seed("seed_01.txt",15);
    struct seed *seed = open_seed("seed_01.txt");
    print_seed(seed);

    //struct tempera_simulada *ts = initiate_tempera(seed,1000);
    //print_path(ts->state->path_start);

    struct state *s = tempera_process(seed,50000,10000000);
    printf("%f\n",s->evaluation);
    print_path(s->path_start);

    free(seed->cities);
    free(seed);

    free(s);
}
