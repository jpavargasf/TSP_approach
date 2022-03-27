%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

clear all;close all;

rng('shuffle');

n_population = 1000;
%n_parents = 2;

n_cities = 15;

max_iterations = 10000;

p_mutation = 0.01;
p_genes_equal = 0.95;

pdf = @(n,N) 2*(-n+N)/((N^2-N));

% x = 1:1:n_cities;
% pdff = pdf(x);
% pd = [];
% %pd(1) = pdf(1);
% for i = 2:1:n_cities
%     %pd(i) = P(i);
%     pd(i) = sum(pdff(1:i));
% end
% plot(x,pd);


cities = read_seed(n_cities);



[path,cost_history] = genetic_algorithm(cities,n_population,max_iterations,p_mutation,p_genes_equal,pdf);

draw_path(cities,path);
figure,plot(cost_history);