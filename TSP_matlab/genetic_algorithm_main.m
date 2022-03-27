%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

clear all;close all;

n_population = 10;
n_parents = 2;

n_cities = 10;

cities = read_seed(n_cities);

[path,cost_history] = genetic_algorithm(cities,n_population,n_parents);

draw_path(cities,path);