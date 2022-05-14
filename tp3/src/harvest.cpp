#include "../include/harvest.h"

void Harvester::readInput(){
    std::cin>>F>>W;
    field.resize(F,std::vector<int>(W));
    for(int i = 0; i < F; i++){
        for(int j = 0; j < W; j++){
            int var;
            std::cin>>var;
            field[i][j] = var;
        }
    }
    
}

std::vector<int> Harvester::maxApples(){

    //Vetor que armazena o caminho indexado na matriz para atingir a soma máxima
    std::vector<int> path;
    path.resize(F+1);
    
    //Matriz de somas parciais definida primeiramente como uma cópia da matriz de dados
    
    std::vector<std::vector<int>> sumMirror(field);

    //Construção da matriz de somas parciais usando bottom-up
    //Primeira linha irá conter as somas máximas obtíveis a partir de cada indíce ao final do loop

    for(int i = F-2; i >= 0 ; i--){
        for(int j = 0; j < W ; j++){
            //Meio do campo, os três movimentos são possíveis
            if(j != 0 && j != W-1)
                sumMirror[i][j] += std::max(sumMirror[i+1][j] ,std::max(sumMirror[i+1][j-1] , sumMirror[i+1][j+1]));
            
            //Canto esquerdo do campo, movimento diagonal esquerda não é possível
            else if(j == 0)
                sumMirror[i][j] += std::max(sumMirror[i+1][j] , sumMirror[i+1][j+1]);

            //Canto direito do campo, movimento diagonal direita não é possível
            else if(j == W - 1)
                sumMirror[i][j] += std::max(sumMirror[i+1][j-1], sumMirror[i+1][j]);
            
        }

    }

    //Construção do caminho de índices
    
    //o índice do ponto de partida do caminho ideal está no elemento da primeira linha que gerou a maior soma em sumMirror
    path[0] = std::max_element(sumMirror[0].begin(), sumMirror[0].end()) - sumMirror[0].begin();

    //contador da soma máxima 
    int partSum = field[0][path[0]];
    
	for(int i = 1; i < F; i++){
        //soma máxima dentre as 3 (ou 2) opções imediatas de trajeto
		int parcSum;

        //índice anterior estava no meio da matriz
		if(path[i-1] != W-1 && path[i-1] != 0){
			parcSum = std::max({ sumMirror[i][path[i-1]] , sumMirror[i][path[i-1] + 1]  , sumMirror[i][path[i-1] - 1] });
			if(parcSum == sumMirror[i][path[i-1]])
				path[i] = path[i-1];
			else if(parcSum == sumMirror[i][path[i-1] + 1])
				path[i] = path[i-1] + 1;
			else if(parcSum == sumMirror[i][path[i-1] - 1])
				path[i] = path[i-1] - 1;

		}
        //índice anterior estava no canto direito da matriz
		else if(path[i-1] == W - 1){
			parcSum = std::max(sumMirror[i][path[i-1]] , sumMirror[i][path[i-1] - 1] );
			if(parcSum == sumMirror[i][path[i-1]])
				path[i] = path[i-1];
			else if(parcSum == sumMirror[i][path[i-1] - 1])
				path[i] = path[i-1] - 1;
			
		}
        //índice anterior estava no canto esquerdo da matriz
		else if(path[i-1] == 0){
			parcSum = std::max(sumMirror[i][path[i-1]] , sumMirror[i][path[i-1] + 1] );
			if(parcSum == sumMirror[i][path[i-1]])
				path[i] = path[i-1];
			else if(parcSum == sumMirror[i][path[i-1] + 1])
				path[i] = path[i-1] + 1;
		}

		
		partSum += field[i][path[i]];
    }

    //O último elemento do vetor armazena a quantidade total máxima de maçãs
	path[F] = partSum;

    return path;

}

void Harvester::printPath(){
    //Gera matriz de dados
    readInput();

    //Gera vetor de caminhos a partir dos dados
    std::vector<int> path = maxApples();

    std::cout<<path[F]<<std::endl;
    for(int i = 0 ; i < F ; i++)
        std::cout<<path[i]<<" ";
   
    printf("\n");     
}