#include "../include/loja.h"

Shop::Shop(int est, int xCord , int yCord , int idNumber){
    estoque = est;
    x = xCord;
    y = yCord;
    id = idNumber;
    customers.reserve(est);
}

int Shop::getId(){
    return id;
}

std::pair<int,int> Shop::getCoord(){
	std::pair<int,int> coordenadas(x,y);
	return coordenadas;
}

void Shop::addCliente(Client c) {
    customers.push_back(c);
}

void Shop::removeClient(Client c){
    int i = 0;
    for(Client k: customers){
        if (c.getId() == k.getId()){
            customers.erase(customers.begin() + i);
            break;
        }
        i++;   
    }
}

bool Shop::isFull(){
    int nClients = customers.size();
    return nClients == estoque;
}

void Shop::printClients(){
    int i = 0 , nClients = customers.size();
    for(Client c : customers){
        if(i == nClients - 1)   std::cout<<c.getId();
        else                    std::cout<<c.getId()<<" ";   
        i++;
    }
    std::cout<<std::endl;
}