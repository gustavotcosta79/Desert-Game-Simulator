//
// Created by Duarte Santos on 19/12/2024.
//

#include "CaixaPandora.h"
#include <iostream>

CaixaPandora::CaixaPandora(Mapa& mapa, int linha, int coluna)
        : Item(mapa, "Caixa de Pandora", linha, coluna) {  // Agora o construtor de Item é chamado diretamente
}
void CaixaPandora::efeito(Caravana& caravana, Mapa& mapa) {
    // Remove 20% da tripulação da caravana
    int tripulantesPerdidos = caravana.getTripulacao() * 0.2;
    int tPerdidos = caravana.perderTripulantes(tripulantesPerdidos);
    std::cout << "A Caixa de Pandora matou " << tPerdidos << " tripulantes!" << std::endl;
}
Item* CaixaPandora::clone() const {
    return new CaixaPandora(*this);
}