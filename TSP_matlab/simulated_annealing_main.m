%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:
tic;
clear all;close all;

n_cities = 30;
%initial_temperature = 100;
%tal_temperature = 1000000;
final_temperature = 0;
max_iterations = 1000000;

cities = read_seed(n_cities);
[path,cost_history,best_path,best_path_cost] = simulated_annealing(cities,final_temperature,max_iterations);
%[path,cost_history] = simulated_annealing(n_cities,initial_temperature,tal_temperature);

draw_path(cities,path);
draw_path(cities,best_path);
figure, plot(cost_history,'DisplayName',"Iterador"), hold on;
plot(best_path_cost,'DisplayName',"Melhor estado"), hold off;

toc;