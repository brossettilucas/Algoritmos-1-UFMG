#include "../include/cliente.h"

Client::Client(int idadeInput , std::string estadoInput , std::string pay , int xCord , int yCord , float score , int idNumber){
    idade = idadeInput;
    originState = estadoInput;
    payment = pay;
    x = xCord;
    y = yCord;
    ticket = score;
	idShop = -1;
    id = idNumber;
}

std::pair<int,int> Client::getCoord(){
	std::pair<int,int> coordenadas(x,y);
	return coordenadas;
}

int Client::getId(){
    return id;
}

int Client::getIdade(){
    return idade;
}

std::string Client::getState(){
    return originState;
}

std::string Client::getPay(){
    return payment;
}
	
float Client::getTicket(){
    return ticket;
}

int Client::getIdShop(){
    return idShop;
}

bool Client::isFree(){
    //idShop = -1 indica que o cliente não está associado a nenhuma loja
    return idShop == -1;
}

void Client::designa(int idN){
    idShop = idN;
}

void Client::freeClient(){
    idShop = -1;
}