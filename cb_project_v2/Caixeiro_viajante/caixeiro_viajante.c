#include"caixeiro_viajante.h"


struct seed *create_seed(char *file_name,uint16_t n_cities){
    struct seed *seed = NULL;

    if(file_name==NULL||n_cities==0){
        printf("ERRO: file_name NULL ou n_cities = 0\n\tEm create_seed:seed\n");
        system("pause");
        return seed;
    }

    //cria seed aleatória
    seed = create_aleatory_seed(n_cities);
    if(seed == NULL){
        printf("ERRO: impossivel criar seed\n\tEm create_seed:seed\n");
        system("pause");
        return seed;
    }

    //escreve seed em arquivo txt
    //FILE *seed_file = fopen(file_name,"w");
    FILE* seed_file = fopen(file_name, "w");

    fprintf(seed_file,"%d\n",seed->n_cities);
    for(uint16_t i=0;i<seed->n_cities;i++){
        fprintf(seed_file,"%d %d\n",seed->cities[i].x,seed->cities[i].y);
    }
    fclose(seed_file);

    return seed;
}

struct seed *create_aleatory_seed(uint16_t n_cities){
    struct seed *seed = NULL;

    //cria seed aleatória
    seed = (struct seed*)malloc(sizeof(struct seed));
    if(seed == NULL){
        printf("ERRO: sem espaço para alocação\n\tEm create_aleatory_seed:seed\n");
        system("pause");
        return seed;
    }

    seed->n_cities = n_cities;
    seed->cities = (struct city*)malloc(n_cities*sizeof(struct city));

    if(seed->cities==NULL){
        printf("ERRO: sem espaço para alocação\n\tEm create_aleatory_seed:seed->cities\n");
        free(seed);
        seed = NULL;
        system("pause");
        return NULL;
    }

    //dependendo do número de cidades, é possível que isto forme um loop infinito,
    //o que é pouco provável, somente se n_cities for aproximadamente próximo ou
    //maior que 255^2
    for(uint16_t i=0;i<n_cities;i++){
        seed->cities[i].number = i;
        seed->cities[i].x = rand()%256;
        seed->cities[i].y = rand()%256;
        for(uint16_t j=0;j<i;j++){
            if(seed->cities[i].x==seed->cities[j].x&&
               seed->cities[i].y==seed->cities[j].y){
                i--;
                break;
            }
        }
    }
    return seed;
};

struct seed *open_seed(char *file_name){
    struct seed *seed = NULL;
    if(file_name==NULL){
        printf("ERRO: file_name NULL\n\tEm open_seed:file_name\n");
        system("pause");
        return seed;
    }

    //FILE *seed_file = fopen(file_name,"r");
    FILE* seed_file = fopen(file_name, "r");
    if(seed_file==NULL){
        printf("ERRO: arquivo inexistente\n\tEm open_seed:%s",file_name);
        system("pause");
        return seed;
    }

    seed = (struct seed*)malloc(sizeof(struct seed));
    if(seed == NULL){
        printf("ERRO: sem espaço para alocação\n\tEm open_seed:seed\n");
        system("pause");
        return seed;
    }

    fscanf(seed_file,"%d",&seed->n_cities);

    seed->cities = (struct city*)malloc(seed->n_cities*sizeof(struct city));
    if(seed->cities==NULL){
        printf("ERRO: sem espaço para alocação\n\tEm open_seed:seed->cities\n");
        free(seed);
        seed = NULL;
        system("pause");
        return NULL;
    }

    for(uint16_t i=0;i<seed->n_cities;i++){
        seed->cities[i].number = i;
        fscanf(seed_file,"%d %d",&seed->cities[i].x,&seed->cities[i].y);
    }
    fclose(seed_file);

    return seed;
};

uint8_t print_seed(struct seed *seed){
    if(seed==NULL||seed->cities==NULL||seed->n_cities==0){
        printf("ERRO: seed NULL\n\tEm print_seed:seed\n");
        system("pause");
        return 0;
    }

    for(uint16_t i=0;i<seed->n_cities;i++){
        printf("Cidade %d: x:%d\ty:%d\n",i,seed->cities[i].x,seed->cities[i].y);
    }
    return 1;
}

float distance(struct city *c1,struct city *c2){

    return sqrt(pow(c1->x - c2->x,2) + pow(c1->y-c2->y,2));
}

float total_distance(struct path *path_start){
    float return_value = 0;

    struct path *path_pointer;
    path_pointer = path_start;

    do{
        return_value+= distance(path_pointer->city,path_pointer->next->city);
        path_pointer = path_pointer->next;
    }while(path_pointer!=path_start);

    return return_value;
}

void print_path(struct path *path_start){
    struct path *path_pointer;
    path_pointer = path_start;
    //printf("\nprint_path oi\n");
    //if(path_pointer==NULL){
    //    printf("NULL");
    //    system("pause");
    //}

    uint16_t i = 0;
    do{
        printf("%d:Cidade %d\n",i,path_pointer->city->number);
        path_pointer = path_pointer->next;
        i++;
    }while(path_pointer!=path_start);
}


void push_path(struct path *path_start,struct city *city);

struct path *start_path(struct city *city);

struct path *create_blank_path(uint16_t path_size){
    struct path *path_start = NULL;
    if(path_size == 0)  return path_start;

    path_start = (struct path*)malloc(sizeof(struct path));
    path_start->city = NULL;
 /*//o caso abaixo já é contemplado no geral
    if(path_size==1){
        path_start->next = path_start;
        path_start->previous = path_start;
        return path_start;
    }
*/
    struct path *aux;
    struct path *aux2;

    aux = path_start;

    for(uint16_t i=1;i<path_size;i++){
        aux2 = (struct path*)malloc(sizeof(struct path));
        aux2->city = NULL;
        aux2->previous = aux;
        aux->next = aux2;
        aux = aux2;
    }

    path_start->previous = aux;
    aux->next = path_start;

    return path_start;
}

/*
struct state *aleatory_state(struct seed *seed){
    struct state *state = NULL;
    state = (struct state*)malloc(sizeof(state));
    struct path *path_start = NULL;
    path_start = (struct path*)malloc(sizeof(struct path));

    state->path_start = path_start;

    struct path *aux = NULL;
    struct path *aux2 = NULL ;

    aux = path_start;

    path_start->city = &seed->cities[0];

    uint16_t i,aa;
    uint16_t a = seed->n_cities - 1;
    uint16_t *aux_vector;
    aux_vector = (uint16_t*)malloc(a*sizeof(uint16_t));
    for(i=0;i<a;i++){
        aux_vector[i] = i+1;
    }

    for(i=1;i<(seed->n_cities);i++){

        aux2 = (struct path*)malloc(sizeof(struct path));

        aa = rand()%a;
        a--;
        aux2->city = &seed->cities[aux_vector[aa]];
        //printf("i=%d aux_vec=%d aux2=%d\n",i,aux_vector[aux2],aux2);
        //printf("%d\n",aux_path->city->number);
        for(uint16_t j = aa;j<a;j++){
            aux_vector[j] = aux_vector[j+1];
        }

        //aux2->city = NULL;
        aux2->previous = aux;
        aux->next = aux2;
        aux = aux2;
        //aux2 = NULL;
    }

    path_start->previous = aux;
    aux->next = path_start;

    state->evaluation = total_distance(path_start);

    //printf("\n\n%f\n",state->evaluation);
    //print_path(path_start);
    //system("pause");

    free(aux_vector);
    aux_vector = NULL;

    return state;
};
*/
struct state *aleatory_state(struct seed *seed){
    struct state *state = NULL;
    state = (struct state*)malloc(sizeof(state));
    //struct path *path_start = NULL;
    state->path_start = (struct path*)malloc(sizeof(struct path));

    //state->path_start = path_start;

    struct path *aux = NULL;
    struct path *aux2 = NULL ;

    aux = state->path_start;

    state->path_start->city = &seed->cities[0];

    uint16_t i,aa;
    uint16_t a = seed->n_cities - 1;
    uint16_t *aux_vector;
    aux_vector = (uint16_t*)malloc(a*sizeof(uint16_t));
    for(i=0;i<a;i++){
        aux_vector[i] = i+1;
    }

    for(i=1;i<(seed->n_cities);i++){

        aux2 = (struct path*)malloc(sizeof(struct path));

        aa = rand()%a;
        a--;
        aux2->city = &seed->cities[aux_vector[aa]];
        //printf("i=%d aux_vec=%d aux2=%d\n",i,aux_vector[aux2],aux2);
        //printf("%d\n",aux_path->city->number);
        for(uint16_t j = aa;j<a;j++){
            aux_vector[j] = aux_vector[j+1];
        }

        //aux2->city = NULL;
        aux2->previous = aux;
        aux->next = aux2;
        aux = aux2;
        //aux2 = NULL;
    }

    state->path_start->previous = aux;
    aux->next = state->path_start;

    state->evaluation = total_distance(state->path_start);

    //printf("\n\n%f\n",state->evaluation);
    //print_path(path_start);
    //system("pause");

    free(aux_vector);
    aux_vector = NULL;

    return state;
};
