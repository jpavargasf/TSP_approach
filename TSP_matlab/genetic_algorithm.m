%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

%path é o melhor caminho encontrado
%cost_history é a média de custo(ou fitness) de cada geração
function  [path,cost_history] = genetic_algorithm(cities,n_population,n_parents,max_iterations,p_mutation,p_genes_equal)
    n_cities = length(cities);
    distance = distance_cities(cities);
    
    cost_history = [];
    
    %criando população inicial
    population = int32.empty(0,n_cities);
    cost_population = double.empty(n_population,0);
    for i = 1:1:n_population
        population(i,:) = random_path(n_cities);
        cost_population(i) = total_path_distance(distance,population(i,:));
        %draw_path(cities,population(i,:));
    end    
    cost_history(end+1) = mean(cost_population(i));
    
    population = ga_order_population(population,cost_population);
    
    n_iterations = 0;
    while(n_iterations<max_iterations)
        
        
        population = ga_order_population(population,cost_population);
        n_iterations = n_iterations + 1;
    end
    path = population(1,:);
end