#ifndef LOJA_H
#define LOJA_H

#include <iostream>
#include <vector>

#include "cliente.h"

class Shop{

  public:
	
	//Construtores
	Shop(int est, int xCord , int yCord , int idNumber );	
	Shop(){}

    //Retorna o número de identificação da loja
    int getId();

	//Retorna as coordenadas da loja
	std::pair<int,int> getCoord();

    //Adiciona um cliente c na lista da loja
	void addCliente(Client c);

    //Remove um cliente c de sua lista
	void removeClient(Client c);

    //Retorna verdadeiro se a loja está em sua capacidade máxima
	bool isFull();

    //Imprime as identificações dos clientes da loja 
    void printClients();
	
    
  private:
    
	int estoque;    	                //quantidade máxima de clientes
    int x,y;        	                //coordenadas da localização da loja
	int id;				                //número de identificação da loja 

	std::vector<Client> customers;		//vetor que armazena os atuais clientes da loja
};



#endif