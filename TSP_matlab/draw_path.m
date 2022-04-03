%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

function draw_path(cities,path)
    n_cities = length(path);
    figure,plot([cities(path(n_cities),1),cities(path(1),1)],[cities(path(n_cities),2),cities(path(1),2)]);
    hold on;
    plot(cities(path(n_cities),1),cities(path(n_cities),2),'r*');
    for i = 1:1:(n_cities-1)
        plot([cities(path(i),1),cities(path(i+1),1)],[cities(path(i),2),cities(path(i+1),2)]);
        plot(cities(path(i),1),cities(path(i),2),'r*');
    end
    hold off;
end