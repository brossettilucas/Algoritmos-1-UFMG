#ifndef LOJA_H
#define LOJA_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <limits.h>
#include <float.h>

//Classe representante das lojas
class Loja{
  public:

    //Construtores da classe
    Loja(int x, int y, int ID){x_coord = x; y_coord = y; id = ID;}
    Loja(){}

    //Retornam as coordenadas da loja

    int getX(){return x_coord;}

    int getY(){return y_coord;}

    //Retorna o número de identificação da loja
    int getId(){return id;}

  private:
    int x_coord, y_coord;   //coordenadas geográficas da loja
    int id;                 //número de identificação da loja
};

#endif