#include "../include/manager.h"

enum Manager::Labels Manager::assignment(std::string input){
        if(input == "MG") return MG;
        if(input == "PR") return PR;
        if(input == "SP") return SP;
        if(input == "SC") return SC;
        if(input == "RJ") return RJ;
        if(input == "RN") return RN;
        if(input == "RS") return RS;
        if(input == "DINHEIRO") return dinheiro;
        if(input == "DEBITO") return debito;
        if(input == "CREDITO") return credito;
        return Undefined;
    }

int Manager::scoreCount(std::string input){
    switch(assignment(input)){
        case MG:        return 0;
        case PR:        return 10;
        case SP:        return 20;
        case SC:        return 30;
        case RJ:        return 40;
        case RN:        return 50;
        case RS:        return 60;
        case dinheiro:  return 1;
        case debito:    return 2;
        case credito:   return 3;
        default:        return -1;
    }
}

float Manager::ticketCalc(int idade_cliente, int score_estado , int score_pagamento){
    return ( float( abs(60 - idade_cliente) + score_estado ) / float(score_pagamento)  );
}

int Manager::minDistance(Client c , Shop s){
    int x_1 = c.getCoord().first , y_1 = c.getCoord().second;
    int x_2 = s.getCoord().first , y_2 = s.getCoord().second;
    
    return std::max( abs(y_1 - y_2) - 1 , abs(x_1 - x_2) - 1 );
}

/*  Esta função auxiliar de comparação é útil para fazer a ordenação 
    da lista de preferência das lojas
*/
bool sortPair(const std::pair<float,int> &a, const std::pair<float,int> &b){
    if(a.first == b.first)  return (a.second < b.second);   //condição de desempate entre dois clientes
    else return (a.first > b.first);                        //ordenamento comum entre clientes de tickets diferentes
}

void Manager::registration(){
    int N,M,m,n;

    std::cin>>N>>M;                             //tamanho do mapa
    std::cin>>m;                                //número de lojas

    lojas.reserve(m);
    lojas.resize(m);

    //Todas as lojas devem fazer a proposta pro primeiro cliente da lista de preferência no início,
    //por isso todas as entradas são iniciadas com 0
    clientIter.reserve(m);
    clientIter.resize(m,0);
    
	int i = 0;
    while(i < m){
        int e,x,y;                              //estoque e coordenadas de cada loja
        std::cin >> e >> x >> y;
        Shop entrada(e,x,y,i);
        lojas[i] = entrada;

		i++;
    }
	std::cin >> n;                              //número de clientes

    clientes.reserve(n);
    clientes.resize(n);

	i = 0;
	while(i < n){
		int age, x , y;                         //idade, coordenadas , pagamento e estado de cada cliente
		std::string state, pay;
		std::cin >> age >> state >> pay >> x >> y;
		float ticket = ticketCalc(age,scoreCount(state),scoreCount(pay));
		Client customer(age,state,pay,x,y,ticket,i);
        clientes[i] = customer;
        
		i++;
	}

    //Lista auxiliar de preferência das lojas - (score , id do cliente ) 
    std::vector< std::pair<float,int> > aux;
    aux.reserve(n);
    prefShop.reserve(n);
    

    i = 0;
    for(Client c:clientes){
        //Armazena cada par (score do cliente i, i)
        aux.push_back(std::make_pair(c.getTicket(),i));
        i++;
    }

    //Ordena a lista auxiliar de preferencia de acordo com as diretrizes de desempate, definidas em sortPair
    std::stable_sort(aux.begin(), aux.end(), sortPair ); 

    //Extrai apenas os índices dos clientes já ordenados de acordo com a prioridade
    for(std::pair<float,int> p:aux)
        prefShop.push_back(p.second);
    
}

int Manager::nextCustomer(int idS){
    int nClients = clientes.size();
    if(clientIter[idS] < nClients) return clientIter[idS];
   
   //Indica que todos os clientes já foram consultados pela loja idS
    return -1;
}

int Manager::frstNonfull(){
    int nShops = lojas.size();
    int i = 0;
    for(Shop s: lojas){
        if( (!s.isFull()) && nextCustomer(i) != -1) return i;
        i++;
    }

    //Indica que todas as lojas já estão com seus estoques preenchidos de forma otimizada
    return nShops; 
}


void Manager::schedule(){
    int nShops = lojas.size();
    int sIndx = 0;  //sIndx é o id da próxima loja a fazer os agendamentos

    while(sIndx != nShops){
        while( !lojas[sIndx].isFull() && nextCustomer(sIndx) != -1){
            //próximo cliente cIndx é o primeiro da lista de preferência que ainda não foi consultado por sIndx
            int cIndx = prefShop[nextCustomer(sIndx)];
            clientIter[sIndx]++;
            
            if(clientes[cIndx].isFree()){
                clientes[cIndx].designa(sIndx);
                lojas[sIndx].addCliente(clientes[cIndx]);
            }
            else{
                //id da loja s' a qual o cliente c está atualmente associado
                int other_sIndx = clientes[cIndx].getIdShop() ;
                int dist_other_S = minDistance(clientes[cIndx], lojas[other_sIndx]), dist_S = minDistance(clientes[cIndx], lojas[sIndx]);
                
                //cliente c prefere loja s à sua loja atual s'
                if( (dist_other_S > dist_S) || ( (dist_other_S == dist_S) && (sIndx < other_sIndx) ) ){   

                    //Remove o par (c,s')
                    int indxa = clientes[cIndx].getIdShop();
                    clientes[cIndx].freeClient();
                    lojas[indxa].removeClient(clientes[cIndx]);
                
                    //Associa o par (c,s)
                    clientes[cIndx].designa(sIndx);
                    lojas[sIndx].addCliente(clientes[cIndx]);
                
                }
            }
        }
        //próxima loja é a primeira com estoque disponível e que ainda possui clientes a propor
        //se não houver, o loop é finalizado
        sIndx = frstNonfull();
        
    }
}

void Manager::printSchedule(){
    int i = 0;
    for(Shop s:lojas){
        std::cout<<i<<std::endl;
        s.printClients();
        i++;
    }
}