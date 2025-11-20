//
// Created by Duarte Santos on 19/12/2024.
//

#ifndef TP_POO_MINA_H
#define TP_POO_MINA_H


#include "Item.h"
#include "../Caravana/Caravana.h"


class Mina : public Item{
public:
    Mina(Mapa& mapa, int linha, int coluna);
    void efeito(Caravana& caravana,Mapa &mapa) override;
    Item* clone() const override;

};


#endif //TP_POO_MINA_H
