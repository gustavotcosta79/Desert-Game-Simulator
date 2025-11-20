//
// Created by Duarte Santos on 19/12/2024.
//

#include "Jaula.h"
#include <iostream>

Jaula::Jaula(Mapa& mapa,int linha, int coluna)  : Item(mapa, "Jaula", linha, coluna) {}

void Jaula::efeito(Caravana& caravana, Mapa& mapa) {
    // Adiciona prisioneiros à tripulação, até o máximo permitido
    int novosTripulantes = 5; // Exemplos de prisioneiros libertados
    int adicionados = caravana.ganhaTripulantes(novosTripulantes);
    std::cout << "A Jaula adicionou " << adicionados << " tripulantes à caravana!" << std::endl;

}

Item* Jaula::clone() const {
    return new Jaula(*this);
}