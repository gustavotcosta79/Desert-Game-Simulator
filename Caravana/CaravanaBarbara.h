 //
// Created by Duarte Santos on 22/12/2024.
//

#ifndef TP_POO_CARAVANABARBARA_H
#define TP_POO_CARAVANABARBARA_H

#include <vector>
#include "../Buffer/Mapa.h"
#include "Caravana.h"

 class CaravanaBarbara : public Caravana {
     int turnosAtivos;       // Contador de turnos ativos
     bool desaparecida;      // Flag que indica se a caravana desapareceu
     int turnos_max;         // Número máximo de turnos antes do desaparecimento

public:
     // Construtor
     CaravanaBarbara(int linha, int coluna, const Mapa& mapa);

     // Métodos sobrescritos
     void moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador) override;
     void isTempestade() override;
     int getMaxMovimentos() const override;
     int getMaxTripulantes() const override;
     void semTripulantes (Mapa &mapa) override;

     // Métodos auxiliares
     bool getDesaparecida() const ;
     void setIncrementaTurno();

     // Métodos irrelevantes para bárbaros
     void consumirAgua() override ;
    Caravana* clone() const override;  // Método virtual
 };




#endif //TP_POO_CARAVANABARBARA_H
