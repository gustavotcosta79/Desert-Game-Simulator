//
// Created by Duarte Santos on 19/12/2024.
//

#include "ArcaTesouro.h"
#include <iostream>

ArcaTesouro::ArcaTesouro(Mapa &mapa, int linha, int coluna)
        : Item(mapa, "Arca do Tesouro",linha, coluna)  {  // Agora o construtor de Item é chamado diretamente
}
void ArcaTesouro::efeito(Caravana& caravana, Mapa& mapa) {
    // Obtenha o número atual de moedas
    int moedasAtuais = mapa.getConfiguracao("moedas");

    // Calcule 10% a mais
    int moedasAdicionais = moedasAtuais * 0.1;

    // Atualize as moedas no mapa
    mapa.alterarConfiguracao("moedas", moedasAtuais + moedasAdicionais);

    // Exiba o resultado
    std::cout << "A Arca do Tesouro adicionou " << moedasAdicionais << " moedas à caravana!" << std::endl;
}

Item* ArcaTesouro::clone() const {
    return new ArcaTesouro(*this);
}