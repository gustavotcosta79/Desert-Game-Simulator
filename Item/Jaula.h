//
// Created by Duarte Santos on 19/12/2024.
//

#ifndef TP_POO_JAULA_H
#define TP_POO_JAULA_H


#include "Item.h"
#include "../Caravana/Caravana.h"

class Jaula : public Item{
public:
    Jaula(Mapa& mapa,int linha, int coluna );
    void efeito(Caravana& caravana, Mapa& mapa) override;
    Item* clone() const override;


};


#endif //TP_POO_JAULA_H
