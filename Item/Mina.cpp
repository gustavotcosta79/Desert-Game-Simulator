//
// Created by Duarte Santos on 19/12/2024.
//

#include "Mina.h"
#include <iostream>


Mina::Mina(Mapa& mapa, int linha, int coluna) : Item(mapa, "Mina", linha, coluna) {}

void Mina::efeito(Caravana& caravana, Mapa& mapa) {
    // Destrói a caravana
    caravana.setDestruida();
    std::cout << "A Mina destruiu completamente a caravana!" << std::endl;
}

Item* Mina::clone() const {
    return new Mina(*this);
}