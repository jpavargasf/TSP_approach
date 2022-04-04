%Autor: João Paulo Vargas da Fonseca
%Data: 27/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:
%
%Com este método de crossover, a quantidade de parentes que passam para a
%próxima geração é de aproximadamente 53% a 54% com pdf linear e 50% com
%pdf quadrática

function children = ga_crossover(population,n_population,n_cities,p_parent,p_mutation,distance)
    children = uint16.empty(0,n_cities);
    
    points_crossover = floor([n_cities/3,2*n_cities/3]);
    
    %representa os parentes que fizeram o crossover e já estão na nova
    %população, sem necessidade de serem inseridos novamente
    %parents_survived = zeros([1,n_population])
    parents_survived = false(1,n_population);
    
    %salvo o melhor
    children(1,:) = population(1,:);
    parents_survived(1) = true;
    
    n_children = 1;
    while(n_children<n_population)
        
        %-------------------encontra os indices dos pais-------------------
%         while(true)
%             p1_index = 1;
%             p2_index = 1;
%             p1 = rand;
%             p2 = rand;
%             for i = 1:1:n_population
%                 if(p1<p_parent(i))
%                     p1_index = i;
%                     break;
%                 end
%             end
%             for i = 1:1:n_population
%                 if(p2<p_parent(i))
%                     p2_index = i;
%                     break;
%                 end
%             end
%             
%             if(p1_index~=p2_index)
%                 break;
%             end
%         end
        %------------------------------------------------------------------
        %-------------------encontra os indices dos pais-------------------
        while(true)
            parents_index = [1,1];
            p = [rand,rand];
            for j = 1:1:2 
                for i = 1:1:n_population
                    if(p(j)<p_parent(i))
                        parents_index(j) = i;
                        break;
                    end
                end
            end
            if(parents_index(1)~=parents_index(2))
                break;
            end
        end
        %------------------------------------------------------------------
        
        %----------------------------pmx-----------------------------------
        n_children = n_children + 1;
        children(n_children,:) = pmx(population(parents_index(1),:),population(parents_index(2),:),points_crossover(1),points_crossover(2));
        %------------------------------------------------------------------
        
        %--------------------------mutação---------------------------------
        %troca duas cidades adjacentes de posição se obtiver sucesso,
        mut = rand;
        if(mut<p_mutation)
            
            neighboors = 1:1:n_cities;
            fitness_actual = total_path_distance(distance,children(n_children,:));
            
            for i = 1:1:n_cities
                
                position = randi([1,length(neighboors)]);
                children_aux = children(n_children,:);
                if(neighboors(position)==1)
                    city_aux = children_aux(2);
                    children_aux(2:(length(children_aux)-1)) = children_aux(3:length(children_aux));
                    children_aux(length(children_aux)) = city_aux;
                elseif(neighboors(position)==n_cities)
                    city_aux = children_aux(neighboors(position));
                    children_aux(3:length(children_aux)) = children_aux(2:(length(children_aux)-1));
                    children_aux(2) = city_aux;
                else
                    children_aux(neighboors(position)) = children(n_children,neighboors(position)+1);
                    children_aux(neighboors(position)+1) = children(n_children,neighboors(position));
                end
                
                new_fit = total_path_distance(distance,children_aux);
                
                if(new_fit<fitness_actual)
                    break;
                end
               
                neighboors(position) = [];
            end
            
            children(n_children,:) = children_aux;
            
        end
        %------------------------------------------------------------------
        
        %------verifica se ha espaço na nova população para os pais--------
        for i = 1:1:2
            if(parents_survived(parents_index(i))==false)
                n_children = n_children + 1;
                if(n_children<=n_population)
                    parents_survived(parents_index(i))=true;
                    children(n_children,:) = population(parents_index(i),:);
                end
            end
        end
        %------------------------------------------------------------------
        
        
    end
    
    
    
end