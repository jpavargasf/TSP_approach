%Autor: João Paulo Vargas da Fonseca
%Data: 25/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:

function [path,cost_history] = simulated_annealing(n_cities,initial_temperature,tal_temperature)
    cost_history = [];

    temperature = @(x) initial_temperature*exp(-x/tal_temperature);
    
    probability = @(dE,temp) exp(-dE/temp);
    
    cities = read_seed(n_cities);
    distance = distance_cities(cities);
    
    path = random_path(n_cities);
    cost_history(end+1) = total_path_distance(distance,path);
    
    n_iterations = 0;
    %t = temperature(n_iterations);
    
     while(true)
        %next_path = path;
        %t = temperature(n_iterations);
        %n_iterations = n_iterations + 1;
        
        neighboors = 2:1:n_cities-1;
        i = 0;
        while(i<(n_cities-2))%numero de vizinhos e n - 2
            
            t = temperature(n_iterations);
            n_iterations = n_iterations + 1;
            
            rand_neighboor = randi([1,length(neighboors)]);
            
            next_path = path;
            next_path(neighboors(rand_neighboor)) = path(neighboors(rand_neighboor)+1);
            next_path(neighboors(rand_neighboor)+1) = path(neighboors(rand_neighboor));
            
            neighboors(rand_neighboor) = [];
            
            next_cost = total_path_distance(distance,next_path);
            
            dE = next_cost - cost_history(end);
            
            if(dE<0)
                path = next_path;
                cost_history(end+1) = next_cost;
                break;
            else
                r = rand();
                if(r<=probability(dE,t))
                    path = next_path;
                    cost_history(end+1) = next_cost;
                    break;
                end
            end
            
            i = i + 1;
        end
        if(t<1&&i==(n_cities-2))
            break;
        end
    end
    disp(n_iterations);
end