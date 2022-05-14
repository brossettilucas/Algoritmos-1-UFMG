#ifndef CONTROL_H
#define CONTROL_H

#include "loja.h"

//Classe que organiza o fluxo de dados 
class Controller{

  public:

	//Construtor da classe
	Controller(){N = 0;}

	//Calcula a distância euclidiana entre duas lojas
	double distCalc(Loja s1 , Loja s2);

	//Recebe os dados de cada loja e organiza uma matriz de distâncias 
	void recordData();

	//Calcula uma MST a partir da matriz de adjacências e o custo final de transporte
	void minCostTree();
  

  private:

  	int N;											//Número de lojas
	int K , D;										//Respectivamente, km máximo p/motocicletas e número de drones 
	int custoKmMoto , custoKmCaminhao;										
	std::vector<std::vector<double>> distMatrix;    //Matriz de adjacência cuja entrada [i][j] possui a distância 
													//entre as lojas de id i e j
	std::vector<Loja> Shops;						//Vetor cuja entrada [i] armazena a loja de id i
	
};


#endif