#ifndef HARVEST_H
#define HARVEST_H

#include <vector>
#include <iostream>
#include <algorithm>


class Harvester{
  public:
	//Construtor vazio
	Harvester(){};

	//Armazena os valores de entrada na matriz field
	void readInput();

    //Função que retorna um vetor de tamanho F+1 onde os primeiros F elementos são os índices percorridos 
    //para atingir o número máximo de maçãs e o elemento F+1 é a soma total
    std::vector<int> maxApples();

    //Executa o algoritmo principal e imprime o resultado
    void printPath();


  private:
	int F , W;   							//número de fileiras de macieiras e número de macieiras por fileira, respectivamente
	std::vector<std::vector<int>> field;	//field[i][j] armazena o número de maças na árvore da fileira i e coluna j

};

#endif