%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:
tic;
clear all;close all;

rng('shuffle');

n_population = 1000;
%n_parents = 2;

n_cities = 100;

max_iterations = 10000;

p_mutation = 0.01;
p_genes_equal = 0.95;

%pdf linear
pdf = @(n,N) 2*(-n+N)/((N^2-N));

%pdf tipo sino
pdf_p = @(n,p) 1/(1+(n/p)^2);

%pdf quadrática
%pdf2 = @(n,N) ((n-N)^2)/((N^3)/3+(2/3)*(N^2)+N/6);

%pdf exponencial
%pdfe = @(n,N) ((exp(1)-1)/((N-1)*exp(-N)-N*exp(-(N-1))+1)*(exp(-n)-exp(-N)));




cities = read_seed(n_cities);



[path,cost_history] = genetic_algorithm(cities,n_population,max_iterations,p_mutation,p_genes_equal,pdf);

draw_path(cities,path);
figure,plot(cost_history),xlabel("Geração"),ylabel("Média do custo de caminho");
toc;
if false
%-------------------------------plota pdfs---------------------------------
p1 = double.empty(0,n_population);

p2_p = double.empty(0,n_population);
p_passo = 50;
n_p2 = 5;
for i = 1:1:n_population
    p1(i) = pdf(i,n_population);
    for j = 1:1:n_p2
        p2_p(j,i) = pdf_p(i,p_passo*j);
    end
end
figure, plot(p1), ylabel("p1"), xlabel("n");
figure,
for j = 1:1:n_p2
    p2_p(j,:) = p2_p(j,:)/sum(p2_p(j,:));
    plot(p2_p(j,:),'DisplayName',"p = " + num2str(j*p_passo));
    hold on;
end
ylabel("p2"),xlabel("n");
legend;
hold off;

end