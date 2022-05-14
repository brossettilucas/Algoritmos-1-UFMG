#ifndef CLIENTE_H
#define CLIENTE_H

#include <utility>
#include <string>



class Client{
	
  public:

	//Construtores
	Client(int idadeInput , std::string estadoInput , std::string pay , int xCord , int yCord , float score , int idNumber);
	Client(){}
	
    //Retorna as coordenadas da localização do cliente
	std::pair<int,int> getCoord();

	//Retorna o número de identificação do cliente
	int getId();

	//Retorna a idade do cliente
	int getIdade();

	//Retorna o estado de origem do cliente
	std::string getState();

	//Retorna o tipo de pagamento que o cliente oferece
	std::string getPay();
	
	//Retorna o valor do ticket do cliente
	float getTicket();
    
    //Retorna o número de identificação da loja associada ao cliente
    int getIdShop();

    //Retorna verdadeiro se o cliente não está associado a nenhuma loja no momento
    bool isFree();

	//Atualiza o número de identificação da loja associada ao cliente
	void designa(int idN);

	//Desfaz o agendamento prévio do cliente
	void freeClient();

		
  private:
		
	std::string originState;	//sigla do estado de origem do cliente
	std::string payment;   		//tipo de pagamento usado pelo cliente
	int x,y;               		//coordenadas da residência do cliente
	int idade;					//idade do cliente
	float ticket;				//valor do ticket do cliente
	int id;						//número de identificação do cliente
	int idShop;					//identificação da loja a qual o cliente foi agendado

};


#endif