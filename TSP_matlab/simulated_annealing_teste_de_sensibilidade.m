%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

tic;
clear all;close all;

final_temperature = 0;
max_iterations = 1000000;

sens = double.empty(0,100-2);
nn = double.empty(0,100-2);
for n_cities = 3:1:100
    aux = 0;
    for n = 1:1:1        
        cities = read_seed(n_cities);
        [path,cost_history,best_path,best_path_cost] = simulated_annealing(cities,final_temperature,max_iterations);
        aux = (cost_history(1)/best_path_cost(end) - 1) + aux;
    end
    sens(n_cities-2) = 100*aux/1;
    nn(n_cities-2) = n_cities;
end
figure,plot(nn,sens,'DisplayName',"Melhora"),xlabel("Número de Cidades"),ylabel("Melhora em relação ao estado inicial"),
ytickformat('percentage');
hold on;

m = repmat(mean(sens),1,length(sens));
plot(nn,m,'DisplayName',"Média");
legend;
hold off;

toc;