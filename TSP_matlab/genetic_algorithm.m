%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

%path é o melhor caminho encontrado
%cost_history é a média de custo(ou fitness) de cada geração
function  [path,cost_history] = genetic_algorithm(cities,n_population,max_iterations,p_mutation,p_genes_equal,pdf)
    
    n_cities = length(cities);
    distance = distance_cities(cities);
    
    %-------------------cria a função de probabilidade---------------------
    p = [];
    for i = 1:1:n_population
        p(i) = pdf(i,n_population);
    end
    p_parent = double.empty(n_population,0);
    p_parent(1) = p(1);
    for i = 2:1:n_population
        p_parent(i) = p_parent(i-1) + p(i);
    end
%     plot(p);
%     plot(p_parent);
    clear p;
    %----------------------------------------------------------------------
    
    cost_history = [];
    
    %--------------------criando população inicial-------------------------
    population = int32.empty(0,n_cities);
    cost_population = double.empty(n_population,0);
    for i = 1:1:n_population
        population(i,:) = random_path(n_cities);
        cost_population(i) = total_path_distance(distance,population(i,:));
        %draw_path(cities,population(i,:));
    end    
    cost_history(end+1) = mean(cost_population);
    
    population = ga_order_population(population,cost_population);
    
    %----------------------------------------------------------------------
    %draw_path(cities,population(1,:));
    n_iterations = 0;
    while(n_iterations<max_iterations)
        
        %crossover e mutação
        population = ga_crossover(population,n_population,n_cities,p_parent,p_mutation,distance);
        
        for i = 1:1:n_population
            cost_population(i) = total_path_distance(distance,population(i,:));
        end
        cost_history(end+1) = mean(cost_population);
        
        
        
        population = ga_order_population(population,cost_population);
        n_iterations = n_iterations + 1;
        
        %close all;
        %draw_path(cities,population(1,:));
        
        %------------------------condição de parada------------------------
        %verifica se p_genes_equal/n_population da população já tem os 
        %mesmos genes
        n_genes_equal = 1;
        aux = 1:1:n_population;
        while(~isempty(aux))
            i = 2;
            while(i<length(aux))
                if(cost_population(aux(1))==cost_population(aux(i)))
                    aux(i) = [];
                    n_genes_equal = n_genes_equal + 1;
                else
                    i = i + 1;
                end
            end
            aux(1) = [];
        end
        if((n_genes_equal/n_population)>=p_genes_equal)
            break;
        end
        %------------------------------------------------------------------
    end
    path = population(1,:);
end