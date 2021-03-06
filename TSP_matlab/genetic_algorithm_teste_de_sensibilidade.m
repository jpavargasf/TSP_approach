%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:demora uma hora pra rodar este código 

tic;


rng('shuffle');

n_population = 1000;
%n_parents = 2;



max_iterations = 10000;

p_mutation = 0.01;
p_genes_equal = 0.95;

%pdf linear
pdf = @(n,N) 2*(-n+N)/((N^2-N));



for n_cities = 3:1:100
    
    cities = read_seed(n_cities);
    [path,cost_history] = genetic_algorithm(cities,n_population,max_iterations,p_mutation,p_genes_equal,pdf);
    n_iter(n_cities-2) = length(cost_history);
    x(n_cities-2) = n_cities;
    sens(n_cities-2) = 100*(cost_history(1)/cost_history(end)-1);
end

figure, plot(x,n_iter,'DisplayName',"Número de Gerações"),xlabel("Número de cidades"),ylabel("Número de gerações");
m = repmat(mean(n_iter),1,length(n_iter));
hold on;
plot(x,m,'DisplayName',"Média");
legend;

figure, plot(x,sens,'DisplayName',"Melhoria"),xlabel("Número de cidades"),ylabel("Melhoria da população final");
ytickformat('percentage');
m = repmat(mean(sens),1,length(sens));
hold on;
plot(x,m,'DisplayName',"Média");
legend;
toc;
    