#ifndef MANAGER_H
#define MANAGER_H

#include <algorithm>

#include "loja.h"

class Manager{
    
  public:

	//Enumeração dos diferentes dados de entrada 
	enum Labels {Undefined , MG , PR , SP , SC , RJ , RN , RS , dinheiro , debito, credito};
	
	//Retorna a label de acordo com a entrada 'input'
	Labels assignment(std::string input);

	//Retorna os valores da pontuação de um cliente de acordo com o dado 'input' de entrada 
	int scoreCount(std::string input);

	//Retorna o valor do ticket de acordo com os dados inseridos
	float ticketCalc(int idade_cliente, int score_estado , int score_pagamento);

	//Calcula a menor distância entre um cliente c e uma loja s
	int minDistance(Client c , Shop s);

    //Cadastra os dados de entrada
    void registration();

    //Se houver, retorna o id do próximo cliente a ser consultado pela loja de indíce idS 
    int nextCustomer(int idS);

    //Retorna o id da primeira loja que ainda tem estoque disponível
    int frstNonfull();
    
    //Realiza o itinerário de agendamento
	void schedule();

    //Imprime o resultado final do agendamento
    void printSchedule();
    

  private:

	std::vector<Shop> lojas;						//vetor de lojas 
	std::vector<Client> clientes;	  		        //vetor de clientes 
    std::vector<int> clientIter;                    //clientIter[i] é o index do próximo cliente a ser consultado pela loja i 
    std::vector<int> prefShop;						//Lista de preferência das lojas com os ids dos clientes
};



#endif