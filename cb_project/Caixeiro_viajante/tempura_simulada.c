#include"tempura_simulada.h"

/*
    Vizinho é considerado como aquele estado em que duas cidades que são
    vizinhas de caminho (como exemplo número 3 e 4 no caminho) trocam de
    posições, por causa disso, há n_cities - 2 estados vizinhos (15 ci-
    dades geram 13 estados vizinhos)
*/

struct tempera_simulada *initiate_tempera(struct seed *seed,uint32_t tal_constant){
    struct tempera_simulada *ts = NULL;
    if(seed==NULL||seed->cities==NULL||seed->n_cities==0){
        printf("ERRO: seed NULL\n\tEm initiate_tempera:seed\n");
        system("pause");
        return ts;
    }

    ts = (struct tempera_simulada*)malloc(sizeof(struct tempera_simulada));
    if(ts == NULL){
        printf("ERRO: sem espaço para alocação\n\tEm initiate_tempera:ts\n");
        system("pause");
        return ts;
    }

    ts->seed = seed;
    ts->iterations = 0;
    ts->tal = tal_constant;

    uint16_t aux = ts->seed->n_cities - 1;
    uint16_t i;
    uint16_t *aux_vector;
    aux_vector = (uint16_t*)malloc(aux*(sizeof(uint16_t)));
    for(i=0;i<aux;i++){
        aux_vector[i] = i+1;
    }

    ts->state = (struct state*)malloc(sizeof(struct state));
    ts->state->path_start = create_blank_path(ts->seed->n_cities);

    ts->state->path_start->city = &ts->seed->cities[0];

    uint16_t aux2;
    struct path *aux_path = ts->state->path_start->next;
    for(i = 0;i<(ts->seed->n_cities-1);i++){
        aux2 = rand()%aux;
        aux--;
        aux_path->city = &ts->seed->cities[aux_vector[aux2]];
        //printf("i=%d aux_vec=%d aux2=%d\n",i,aux_vector[aux2],aux2);
        //printf("%d\n",aux_path->city->number);
        for(uint16_t j = aux2;j<aux;j++){
            aux_vector[j] = aux_vector[j+1];
        }

        aux_path = aux_path->next;

    }

    ts->state->evaluation = total_distance(ts->state->path_start);
    printf("%f\n",ts->state->evaluation);

    free(aux_vector);
    aux_vector = NULL;

    return ts;
}

float probability(struct tempera_simulada *ts){
    return exp(-(float)(ts->iterations/ts->tal));
}

#define PROB_PRECISION 1000
uint8_t change_to_worse(struct tempera_simulada *ts){
    float n = (float)((float)(rand()%PROB_PRECISION))/((float)PROB_PRECISION);
    float p = exp(-(float)(ts->iterations/ts->tal));
    //printf("a = %f n = %f p = %f\n",a,n,p);
    if(p<=n){
        return 0;
    }
    return 1;
}

struct state *tempera_process(struct seed *seed,uint32_t tal_constant,uint32_t max_iterations){
    struct tempera_simulada *ts;
    ts = initiate_tempera(seed,tal_constant);

    //estados vizinhos que não foram visitados
    uint16_t n_neighboor_states = ts->seed->n_cities - 2;
    uint16_t *neighboor_states;
    neighboor_states = (uint16_t*)malloc(n_neighboor_states*sizeof(uint16_t*));

    uint16_t i;

    do{
        //if(n_neighboor_states==ts->)
        n_neighboor_states = ts->seed->n_cities - 2;
        for(i=0;i<n_neighboor_states;i++){
            neighboor_states[i]=i+1;
        }

        for(i=0;i<(ts->seed->n_cities-2);i++){
            uint16_t aux = rand()%n_neighboor_states;
            n_neighboor_states--;

            struct path *aux_path;
            struct city *aux_city;

            aux_path = ts->state->path_start->next;
            for(uint16_t j=1;j<neighboor_states[aux];j++){
                aux_path = aux_path->next;
            }
            aux_city = aux_path->city;
            aux_path->city = aux_path->next->city;
            aux_path->next->city = aux_city;

            float new_state_evaluation = total_distance(ts->state->path_start);
            //printf("%d : %f : %f\n",ts->iterations,ts->state->evaluation,new_state_evaluation);
            ts->iterations++;
            if(new_state_evaluation<ts->state->evaluation){
                //printf("menor\n");
                ts->state->evaluation = new_state_evaluation;
                break;
            }else{
                uint8_t c = change_to_worse(ts);
                //printf("c = %d\n",c);
                if(c==1){
                    //printf("maior\n");
                    ts->state->evaluation = new_state_evaluation;
                    break;
                }else{
                    for(uint16_t j=aux;j<n_neighboor_states;j++){
                        neighboor_states[j] = neighboor_states[j+1];
                    }
                    aux_city = aux_path->city;
                    aux_path->city = aux_path->next->city;
                    aux_path->next->city = aux_city;
                }
            }
        }
        if(i==(ts->seed->n_cities-2)&&probability(ts)==(float)0){
            break;
        }
        //ts->iterations++;
    }while(ts->iterations<max_iterations);

    return ts->state;
}
