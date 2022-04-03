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

%pdf linear
pdf = @(n,N) 2*(-n+N)/((N^2-N));

%pdf quadrática
pdf2 = @(n,N) ((n-N)^2)/((N^3)/3+(2/3)*(N^2)+N/6);

%pdf exponencial
pdfe = @(n,N) ((exp(1)-1)/((N-1)*exp(-N)-N*exp(-(N-1))+1)*(exp(-n)-exp(-N)));

% x = 1:1:n_population;
% % pdff = pdf2(x,n_cities);
% for i = 1:1:n_population
%     pdff(i) = pdfe(i,n_population);
% end
% pd = [];
% %pd(1) = pdf(1);
% for i = 2:1:n_population
%     %pd(i) = P(i);
%     pd(i) = sum(pdff(1:i));
% end
% figure, plot(pdff);
% figure, plot(x,pd);


cities = read_seed(n_cities);



[path,cost_history] = genetic_algorithm(cities,n_population,max_iterations,p_mutation,p_genes_equal,pdf);

draw_path(cities,path);
figure,plot(cost_history);