//
// Created by Duarte Santos on 19/12/2024.
//

#ifndef TP_POO_ARCATESOURO_H
#define TP_POO_ARCATESOURO_H

#include "../Caravana/Caravana.h"
#include "Item.h"

class ArcaTesouro : public Item{

public:
    ArcaTesouro(Mapa& mapa, int linha, int coluna);  // Passar Mapa para o construtor de Item
    void efeito(Caravana& caravana, Mapa& mapa) override;
    Item* clone() const override;
};


#endif //TP_POO_ARCATESOURO_H
