%Autor: João Paulo Vargas da Fonseca
%Data: 25/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:calcula a distancia total através de um caminho

function tpd = total_path_distance(distance,path)
    n_cities = length(path);

    tpd = distance(path(1),path(n_cities));
    for i = 1:1:(n_cities-1)
        tpd = tpd + distance(path(i),path(i+1));
    end
end