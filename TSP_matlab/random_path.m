%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

function path = random_path(n_cities)
    aux = 2:1:n_cities;
    path = uint16.empty(n_cities,0);
    path(1) = 1;
    for i = 2:1:n_cities
        r = randi([1,length(aux)]);
        path(i) = aux(r);
        aux(r) = [];
    end
end