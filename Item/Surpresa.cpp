//
// Created by Duarte Santos on 19/12/2024.
//

#include "Surpresa.h"
#include "iostream"
using namespace std;


Surpresa::Surpresa(Mapa& mapa, int linha, int coluna)
        : Item(mapa, "Surpresa", linha, coluna) {  // Agora o construtor de Item é chamado diretamente
}

void Surpresa::efeito(Caravana &caravana, Mapa &mapa) {
    int tripulantesPerdidos = caravana.getTripulacao() * 0.2;
    int tPerdidos = caravana.perderTripulantes(tripulantesPerdidos);
    caravana.setGato(true);
    cout << "O item surpresa tirou-lhe " << tPerdidos << " tripulantes, mas recebeu o gato da fortuna!" << endl;
}

Item* Surpresa::clone() const {
    return new Surpresa(*this);
}

