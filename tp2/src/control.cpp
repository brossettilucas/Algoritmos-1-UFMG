#include "../include/control.h"

double Controller::distCalc(Loja s1 , Loja s2){
    double x_part = static_cast<double>(s1.getX() - s2.getX());
    double y_part = static_cast<double>(s1.getY() - s2.getY());
    return sqrt(pow(x_part,2) + pow(y_part,2));
}

void Controller::recordData(){
    std::cin>>N>>K>>D>>custoKmMoto>>custoKmCaminhao;
    int i = 0;

    Shops.resize(N);
    distMatrix.resize(N);

    //Registro das lojas 
    while(i < N){
        int x,y;
        std::cin>>x>>y;
        Shops[i] = Loja(x,y,i);
        i++;
    }

    //Construção da matriz de adjacência representante do grafo 
    for(int i = 0; i < N ; i++){
        distMatrix[i].resize(N);
        for(int j = 0; j < N; j++)
            distMatrix[i][j] = distCalc(Shops[i], Shops[j]);                                         
    }
}

//Usa uma versão do Algoritmo de Prim para gerar a MST
void Controller::minCostTree(){

    //Vetor que indica se um vértice está na MST
    std::vector<bool> isInTree;
    isInTree.resize(N, false);

    int pred[N];                //O parente do vértice i na MST é dado pelo vértice de íncide pred[i]
    double cost[N];             //Possui o custo mínimo para se alcançar um vértice a partir do cutset atual
     
    //O custo de todos os vértices é infinito, exceto pelo vértice inicial s: irá determinar que apenas isInTree[s] = true
    int s = 0;
    for (int i = 0; i < N; i++)
        (i == s)? cost[i] = 0 : cost[i] = DBL_MAX;
    
    //Raiz da árvore não possui parente
    pred[0] = -1;
    
    //Determina os vértices e arestas da MST
    for (int e = 0; e < N - 1; e++){ 
        double minEdge = DBL_MAX;
        int minEdgeIndx;

        //Procura pelo vértice não presente na MST cuja aresta alcançável é a menor possível  
        for (int u = 0; u < N; u++)
            if (isInTree[u]==false && cost[u] < minEdge){
                minEdge = cost[u];
                minEdgeIndx = u;
            }
        
        // Adiciona o vértice com a menor aresta alcançável à MST
        isInTree[minEdgeIndx] = true;

        //Atualiza o peso das arestas alcançáveis de cada vértice e seus parentes na MST
        for (int v = 0; v < N; v++)                              
            //distMatrix[i][j] = 0 apenas para i = j : queremos apenas os vértices adjacentes
            //Os parentes e custos mínimos só são atualizados para vértices que não estão na MST e com custos atuais maiores
            if (distMatrix[minEdgeIndx][v]!=0 && isInTree[v]==false && distMatrix[minEdgeIndx][v] < cost[v]){
                pred[v] = minEdgeIndx;
                cost[v] = distMatrix[minEdgeIndx][v];
            }
    }

    double custo_moto = 0, custo_caminhao = 0;

    //Array com os valores das arestas da MST
    double tree[N-1];
    for (int i = 1; i < N; i++)
        tree[i-1] = distMatrix[i][pred[i]];
        
    //O posicionamento dos drones com custo total mínimo equivale a anular as maiores D-1 arestas da árvore 
    std::sort(tree, tree + N - 1, std::greater<double>());
    for(int i=0; i< D - 1; i++)
        tree[i] = 0;
    
    //O custo do km por trajeto depende da sua distância
    for(int i=0;i< N-1;i++){
        if(tree[i] <= K)    custo_moto += tree[i]*custoKmMoto;
        else                custo_caminhao += tree[i]*custoKmCaminhao;
    }

    printf("%.3f %.3f", custo_moto, custo_caminhao);
}