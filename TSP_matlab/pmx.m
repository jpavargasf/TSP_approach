%Autor: João Paulo Vargas da Fonseca
%Data: 26/03/2022
%Trabalho desenvolvido para a disciplina de Sistemas Inteligentes do Curso
%de Engenharia Eletrônica da Universidade Tecnológica Federal do Paraná
%
%Comentários:
%
%criança dividida em 3 sempre, para não ter aleatoriedade.
%bloco do centro onde se aplica a operação principal

function child = pmx(parent1,parent2,point1,point2)
    n_cities = length(parent1);
    
%     point1 = floor(n_cities/3);
%     point2 = 2*point1;
    
    child = zeros([1,n_cities]);
    %copia segmento para a criança
    child(point1:point2) = parent1(point1:point2);
    
    %verifica quais valores divergem entre parentes para point1:point2
    for i = point1:1:point2
        value_is_here = false;
        for j = point1:1:point2
            if(parent2(i)==parent1(j))
                value_is_here = true;
                break;
            end
        end
        if(value_is_here==false)
            k = parent1(i);
            ii = 0;
            while(ii<n_cities)
                ii = ii + 1;
                if(parent2(ii)==k)
                    if(ii>=point1&&ii<=point2)
                        k = parent1(ii);
                        ii = 0;
                    else
                        child(ii) = parent2(i);
                    end
                end
            end
        end
    end
    
    %copia o que falta ser preenchido na criança do parente 2
    for i = 1:1:n_cities
        if(child(i)==0)
            child(i) = parent2(i);
        end
    end
    
end