%Autor: João Paulo Vargas da Fonseca
%Data: 25/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:lê a seed de um arquivo da pasta seeds. Caso ele não exista, 
% cria um com com a quantidade desejada de cidades

function cities = read_seed(n_cities)
    file = fopen("seeds\city"+num2str(n_cities)+".txt","r");
    if(file == -1)%arquivo inexistente
        file = fopen("seeds\city"+num2str(n_cities)+".txt","w");
        cities = randi([0,intmax("uint16")],n_cities,2);
        for i = 1:1:n_cities
            for j = 1:1:n_cities
                if(cities(i,:)==cities(j,:))
                    cities(i,:) = randi([0,intmax("uint16")],1,2);
                    i = i - 1;
                    break;
                end
            end
        end
        %fprintf(file,"%d\n",n_cities);
        for i = 1:1:n_cities
            fprintf(file,"%d %d\n",cities(i,1),cities(i,2));
        end
        fclose(file);
    else
        cities = int16.empty(n_cities,0);
        for i = 1:1:n_cities
            cities(i,:) = fscanf(file,"%d %d\n");
        end
        fclose(file);
    end
end
