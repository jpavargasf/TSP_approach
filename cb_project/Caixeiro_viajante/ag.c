#include"ag.h"

struct state *ag_process(struct seed *seed,uint16_t n_population,uint16_t n_parents,uint16_t max_iterations,float p_mutation);

struct ag *initialize_ag(struct seed *seed,uint16_t n_population,uint16_t n_parents);


/*
    reprodução ocorre da seguinte forma:
    início e final de um caminho são fornecidos por um estado
    meio do caminho fornecido pelo outro estado
*/
void crossover(struct state *s1, struct state *s2, struct state *result,struct seed *seed){
    struct state *aux[2];
    //struct state *aux2;
    uint8_t a = rand()%2;
    aux[a] = s1;
    aux[1-a]=s2;
    //aux[2] = aux[0];

    struct path *aux_path[2];
    aux_path[0] = aux[0]->path_start->next;
    aux_path[1] = aux[1]->path_start->next;

    struct path *path_aux;
    path_aux = result->path_start->next;

    uint16_t n[3];
    n[0] = (uint16_t)(seed->n_cities-1)/3;
    n[1] = n[0];
    n[2] = n[0];
    printf("\noi\n");
    uint32_t auxx = n[0]+n[1]+n[2];

    while((auxx)<(seed->n_cities-1)){
        a = rand()%3;
        n[a]++;
        auxx = n[0]+n[1]+n[2];
    }
    printf("\noi\n");

    //fazer um wihle dierente od ppath_start aqqui
    //dai inicia com 1, ai pa 2 e se 2 vai pa 1

    //
    uint16_t *n_repeated_cities_vector;
    n_repeated_cities_vector = (uint16_t*)malloc((seed->n_cities-1)*sizeof(uint16_t));

    uint16_t k = 0;

    while(k<(seed->n_cities-1)){
        n_repeated_cities_vector[k] = 0;
        k++;
    }


    uint16_t n_repeated_cities = 0;

    uint8_t i = 0;
    k = 0;
    uint16_t j;
    do{
        j = 0;
        while(j<n[i]){
            path_aux->city = aux_path[k]->city;
            printf("j = %d i = %d k = %d cn = %d\n",j,i,k,aux_path[k]->city->number);
            //system("pause");
            n_repeated_cities_vector[path_aux->city->number-1]++;
            if(n_repeated_cities_vector[path_aux->city->number-1]>1){
                n_repeated_cities++;
            }
            aux_path[0] = aux_path[0]->next;
            aux_path[1] = aux_path[1]->next;
            path_aux = path_aux->next;
            j++;
        }

        i++;
        k++;
        if(k==2){
            k=0;
        }
    }while(path_aux!=result->path_start);

    print_path(path_aux);
    system("pause");
    //j = 0;


    //path_aux = path_aux->next;
    path_aux = path_aux->next;
    k = 0;
    do{
        //path_aux = path_aux->next;
        float lowest_evaluation;
        //float actual_evaluation;
        uint16_t index_le;
        if(n_repeated_cities_vector[path_aux->city->number-1]>1){
            k=0;
            n_repeated_cities_vector[path_aux->city->number-1]--;
            for(uint16_t ii=0;ii<n_repeated_cities;ii++){
                while(n_repeated_cities_vector[k++]!=0);
                path_aux->city = &seed->cities[k];
                result->evaluation = total_distance(path_aux);
                if(ii==0){
                    lowest_evaluation = result->evaluation;
                    index_le = k;
                }else if(lowest_evaluation>result->evaluation){
                    lowest_evaluation = result->evaluation;
                    index_le = k;
                }
            }

            printf(" cidade a ser inserida = %d no lugar da = %d\n",index_le,path_aux->city->number);



            path_aux->city = &seed->cities[index_le];//k+1 porque k desconsidera cidade 0


            n_repeated_cities_vector[index_le-1]++;
            n_repeated_cities--;
        }
        //n_repeated_cities--;
        path_aux = path_aux->next;
    }while(path_aux!=result->path_start);

    result->evaluation = total_distance(result->path_start);
}

void mutate(uint16_t n_cities,struct state *state){
    uint16_t random_city = rand()%(n_cities-2);

    struct path *path_mutate = state->path_start->next;
    struct city *city_aux;

    for(uint16_t i=0;i<random_city;i++){
        path_mutate=path_mutate->next;
    }
    city_aux = path_mutate->city;
    path_mutate->city = path_mutate->next->city;
    path_mutate->next->city = city_aux;
}

void select_parents(struct ag *ag){

}

