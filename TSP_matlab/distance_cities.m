%Autor: João Paulo Vargas da Fonseca
%Data: 25/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:calcula a distância de todas as cidades para todas as cidades
%retornando uma matriz 

function distance = distance_cities(cities)
    n_cities = length(cities);
    
    c = double(cities);
    
    distance = double.empty(n_cities,0);
    
    for i = 1:1:n_cities
        for j = 1:1:n_cities
            distance(i,j) = sqrt((c(i,1)-c(j,1))^2+(c(i,2)-c(j,2))^2);
        end
    end
end