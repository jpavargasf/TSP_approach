%Autor: João Paulo Vargas da Fonseca
%Data: 25/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:temperatura inicial 

function [path,cost_history] = simulated_annealing(cities,final_temperature,max_iterations)
    cost_history = [];

    n_cities = length(cities);
    distance = distance_cities(cities);
    
    initial_temperature = mean(distance,"all");
    
    %temperature = @(x) initial_temperature*exp(-x/tal_temperature);
    temperature = @(x) (x<max_iterations)*(final_temperature + (initial_temperature-final_temperature)*((1-x/max_iterations)^2));
    
    probability = @(dE,temp) exp(-dE/temp);
    
    %cities = read_seed(n_cities);
    
    
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
%         if(t<1&&i==(n_cities-2))
%             break;
%         end
        if(n_iterations>=max_iterations&&i==(n_cities-2))
            break;
        end
    end
    disp(n_iterations);
end