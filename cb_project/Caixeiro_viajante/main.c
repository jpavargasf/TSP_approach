#include<stdlib.h>
#include<stdio.h>

#include"caixeiro_viajante.h"
#include"tempura_simulada.h"
#include"ag.h"

//#define _CRT_SECURE_NO_WARNINGS

int main(){
    srand(time(NULL));
    //struct seed *seed = create_seed("seed_01.txt",15);


    struct seed *seed = open_seed("seed_01.txt");

    /*
    while(1){
        struct state *s = aleatory_state(seed);
        printf("\n");
        print_path(s->path_start);
        printf("\n");
        struct path *p = s->path_start->next;
        struct path *p2;
        do{
            p2 = p->next;
            free(p);
            p = p2;
        }while(p!=s->path_start);
        free(p);
        free(s);
    }
    */
 /*   print_seed(seed);

    //struct tempera_simulada *ts = initiate_tempera(seed,1000);
    //print_path(ts->state->path_start);

    struct state *s = tempera_process(seed,50000,10000000);
    printf("%f\n",s->evaluation);
    print_path(s->path_start);
*/
 /*
    mutate(seed->n_cities,s);
    s->evaluation = total_distance(s->path_start);
    printf("%f\n",s->evaluation);
    print_path(s->path_start);
*/
/*
    struct state *s2 = tempera_process(seed,50000,10000000);
    printf("%f\n",s2->evaluation);
    print_path(s2->path_start);

    struct state *s3 = tempera_process(seed,1,10);
    //printf("%f\n",s3->evaluation);
    //print_path(s3->path_start);

    crossover(s,s2,s3,seed);
    printf("%f\n",s3->evaluation);
    print_path(s3->path_start);
*/

    struct state *s4 = ag_process(seed,40,10,100,0.01);
    printf("%f\n",s4->evaluation);
    print_path(s4->path_start);

    free(seed->cities);
    free(seed);

//    free(s);
    //system("pause");
    return 0;
}
