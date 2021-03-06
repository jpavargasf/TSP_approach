%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

%function [ordered_population,ordered_costs] = ga_order_popupation(population,cost_population)
function population = ga_order_population(population,cost_population)
    n_cities = length(population(1,:));
    n_population = length(cost_population);
    
    %ordered_population = int32.empty(0,n_cities);
    %ordered_costs = double.empty(n_population,0);
    
    for i = 1:1:n_population
        index = i;
        for j = i+1:1:n_population
            if(cost_population(index)>cost_population(j))
                index = j;
            end
        end
        aux(:) = population(i,:);
        population(i,:) = population(index,:);
        population(index,:) = aux(:);
        
        %ordered_population(i,:) = population(index,:);
        %ordered_costs(i) = cost_population(index);
    end
end