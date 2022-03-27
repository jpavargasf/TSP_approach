%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

clear all;close all;

n_cities = 100;
%initial_temperature = 100;
%tal_temperature = 1000000;
final_temperature = 0;
max_iterations = 100000000;

cities = read_seed(n_cities);
[path,cost_history] = simulated_annealing(cities,final_temperature,max_iterations);
%[path,cost_history] = simulated_annealing(n_cities,initial_temperature,tal_temperature);

draw_path(cities,path);
figure, plot(cost_history);

