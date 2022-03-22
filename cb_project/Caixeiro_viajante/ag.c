#include"ag.h"

#define P_PRECISION 1000

struct state *ag_process(struct seed *seed,uint16_t n_population,uint16_t n_parents,uint32_t max_iterations,float p_mutation){
    struct ag *ag;
    //printf("\noi\n");
    ag = initialize_ag(seed,n_population,n_parents,p_mutation);
    //printf("\noi\n");

    uint32_t n_iterations = 0;
    uint16_t i;
    uint16_t n_reproductions;
    n_reproductions = ag->n_population - ag->n_parents;

    do{
               // printf("\noi\n");

        select_parents(ag);
    //printf("\noi\n");


        i = 0;
        //os parentes não estão no início da população
        //solução errada
        while(i<n_reproductions){
            uint16_t p1;
            uint16_t p2;
            do{
                p1 = rand()%ag->n_parents;
                p2 = rand()%ag->n_parents;
            }while(p1==p2);
            /*
            printf("\n%f\n",ag->parents[p1]->evaluation);
            print_path(ag->parents[p1]->path_start);
            printf("\n%f\n",ag->parents[p2]->evaluation);
            print_path(ag->parents[p2]->path_start);
            crossover(ag->parents[p1],ag->parents[p2],ag->population[i+n_parents],ag->seed);
            */
            printf("p1 = %d p2 = %d\n",p1,p2);

            printf("\n%f\n",ag->population[p1]->evaluation);
            print_path(ag->population[p1]->path_start);
            printf("\n%f\n",ag->population[p2]->evaluation);
            print_path(ag->population[p2]->path_start);


            crossover(ag->population[p1],ag->population[p2],ag->population[i+n_parents],ag->seed);

            //printf("\noi\n");

            float p_mut = (float)((rand()%P_PRECISION)/((float)(P_PRECISION-1)));
            if(p_mut<=p_mutation){
                mutate(ag->seed->n_cities,ag->population[i+n_parents]);
            }

            ag->population[i+n_parents]->evaluation = total_distance(ag->population[i+n_parents]->path_start);
            i++;
        }


        n_iterations++;
    }while(n_iterations<max_iterations);
    select_parents(ag);
    return ag->population[0];
}

struct ag *initialize_ag(struct seed *seed,uint16_t n_population,uint16_t n_parents,float p_mutation){

    struct ag *ag;
    ag = (struct ag*)malloc(sizeof(struct ag));

    ag->seed = seed;
    ag->n_parents = n_parents;
    ag->n_population = n_population;
    ag->p_mutation = p_mutation;

    //ag->parents = (struct state**)malloc(ag->n_parents*sizeof(struct state*));

    ag->population = (struct state**)malloc(ag->n_population*sizeof(struct state*));


    uint16_t i;
    for(i=0;i<ag->n_population;i++){
        ag->population[i] = aleatory_state(ag->seed);
    }
    return ag;
}


/*
    reprodução ocorre da seguinte forma:
    início e final de um caminho são fornecidos por um estado
    meio do caminho fornecido pelo outro estado
*/

//melhor pegar n cidades da seed de um e m de outro
/*
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
    printf("\ncrossover n[0]=%d aprox = %f\n",n[0],(float)(seed->n_cities-1)/3);
    uint32_t auxx = n[0]+n[1]+n[2];

    while((auxx)<(seed->n_cities-1)){
        a = rand()%3;
        n[a]++;
        auxx = n[0]+n[1]+n[2];
    }
    //printf("\noi\n");

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
            //printf("j = %d i = %d k = %d cn = %d\n",j,i,k,aux_path[k]->city->number);
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

    //print_path(path_aux);
    //system("pause");
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

            //printf(" cidade a ser inserida = %d no lugar da = %d\n",index_le,path_aux->city->number);



            path_aux->city = &seed->cities[index_le];//k+1 porque k desconsidera cidade 0


            n_repeated_cities_vector[index_le-1]++;
            n_repeated_cities--;
        }
        //n_repeated_cities--;
        path_aux = path_aux->next;
    }while(path_aux!=result->path_start);

    //result->evaluation = total_distance(result->path_start);
}

void mutate(uint16_t n_cities,struct state *state){
    uint16_t n_neighboor_states = n_cities - 2;
    uint16_t *neighboor_states;
    neighboor_states = (uint16_t*)malloc(n_neighboor_states*sizeof(uint16_t*));

    uint8_t successful = 0;

    uint16_t i;

    for(i=0;i<n_neighboor_states;i++){
        neighboor_states[i]=i+1;
    }

    for(i=0;i<(n_cities-2);i++){
        uint16_t aux = rand()%n_neighboor_states;
        n_neighboor_states--;

        struct path *aux_path;
        struct city *aux_city;

        aux_path = state->path_start->next;
        for(uint16_t j=1;j<neighboor_states[aux];j++){
            aux_path = aux_path->next;
        }
        aux_city = aux_path->city;
        aux_path->city = aux_path->next->city;
        aux_path->next->city = aux_city;

        float new_state_evaluation = total_distance(state->path_start);
        //printf("%d : %f : %f\n",ts->iterations,ts->state->evaluation,new_state_evaluation);
        //ts->iterations++;
        if(new_state_evaluation<state->evaluation){
            //printf("menor\n");
            state->evaluation = new_state_evaluation;
            successful = 1;
            break;
        }else{
            aux_city = aux_path->city;
            aux_path->city = aux_path->next->city;
            aux_path->next->city = aux_city;
        }
    }
    free(neighboor_states);
    neighboor_states = NULL;

    if(successful==0){
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

}

//velor ag->parents é inútil, pq eu deixo os parentes nas primeiras
//posições da população
/*
void select_parents(struct ag *ag){
    uint16_t i,j,k;
    struct state *state_aux;
    //uint8_t p_selected;

    //ag->parents[0] = ag->population[0];

    for(i=0;i<ag->n_population;i++){

        printf("\n\n%d \tparents  na população\n",i);
        for(k = 0;k<ag->n_parents;k++){
            printf("%d : %f\n",k,ag->population[k]->evaluation);
        }
        //ag->population[i]
        //do while
        j = 0;
        while(j<i&&j<ag->n_parents){

        //}
        //for(j=0;(j<i&&j<ag->n_parents);j++){
                    //printf("\noi\n");

            if(ag->population[i]->evaluation<ag->population[j]->evaluation){
                //state_aux = ag->population[j];
                //printf("i = %d j = %dpop:%f par:%f\n",i,j,ag->population[i]->evaluation,ag->population[j]->evaluation);
                /*
                struct state *aux;
                for(k=j;k<i;k++){
                    aux = ag->parents[k+1];
                    ag->parents[k+1] = ag->parents[k];
                }
                *//*
                k = ag->n_parents-1;
                state_aux = ag->population[k];
                for(;k>j;k--){
                    ag->population[k] = ag->population[k-1];
                }
                //ag->parents[j] = ag->population[i];

                ag->population[j] = ag->population[i];
                ag->population[i] = state_aux;


                break;
            }
            j++;
        }
        /*
        if((j<ag->n_parents)&&j==i){
            state_aux = ag->population[j];

            ag->population[j] = ag->population[i];

            ag->population[i] = state_aux;
            //ag->population[j] = ag->parents[j];
        }
        *//*
    }
    printf("\n\nfilal: parents  na população\n");
    for(i = 0;i<ag->n_parents;i++){
        printf("%d : %f\n",i,ag->population[i]->evaluation);
    }
}
*/
/*
void select_parents(struct ag *ag){
    uint16_t i,j,k;
    struct state *state_aux;
    //uint8_t p_selected;

    //ag->parents[0] = ag->population[0];

    for(i=0;i<ag->n_population;i++){
        //ag->population[i]
        //do while
        for(j=0;(j<i&&j<ag->n_parents);j++){
                    //printf("\noi\n");

            if(ag->population[i]->evaluation<ag->parents[j]->evaluation){
                state_aux = ag->parents[j];
                printf("i = %d j = %dpop:%f par:%f\n",i,j,ag->population[i]->evaluation,ag->parents[j]->evaluation);
                /*
                struct state *aux;
                for(k=j;k<i;k++){
                    aux = ag->parents[k+1];
                    ag->parents[k+1] = ag->parents[k];
                }
                *//*
                for(k=(ag->n_parents-1);k>j;k--){
                    ag->parents[k] = ag->parents[k-1];
                }
                ag->parents[j] = ag->population[i];

                ag->population[i] = state_aux;
                ag->population[j] = ag->parents[j];

                break;
            }
        }
        if((j<ag->n_parents)&&j==i){
            state_aux = ag->population[j];

            ag->parents[j] = ag->population[i];

            ag->population[i] = state_aux;
            ag->population[j] = ag->parents[j];
        }
    }
    printf("\n\nparents\n");
    for(i = 0;i<ag->n_parents;i++){
        printf("%d : %f\n",i,ag->parents[i]->evaluation);
    }

    printf("\n\nparents  na população\n");
    for(i = 0;i<ag->n_parents;i++){
        printf("%d : %f\n",i,ag->population[i]->evaluation);
    }
}
*/

void select_parents(struct ag *ag){
    struct state *state_aux;
    uint16_t index;
    for(uint16_t i=0;i<ag->n_parents;i++){
        index = i;
        for(uint16_t j=i+1;j<ag->n_population;j++){
            if(ag->population[j]->evaluation<ag->population[index]->evaluation){
                index = j;
            }
        }
        state_aux = ag->population[i];
        ag->population[i] = ag->population[index];
        ag->population[index] = state_aux;
    }
}

