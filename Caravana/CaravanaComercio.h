//
// Created by Duarte Santos on 20/12/2024.
//

#ifndef TP_POO_CARAVANACOMERCIO_H
#define TP_POO_CARAVANACOMERCIO_H
#include "Caravana.h"
#include <cstdlib> // Para a função rand()
#include <ctime>   // Para a função time()

class CaravanaComercio : public Caravana {
private:
    int turnosSemTripulantes; // Para contar os turnos sem tripulantes

public:
    int getMaxMovimentos() const override ;

    CaravanaComercio(int id, int linha, int coluna);

    void moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador) override;
    void isTempestade() override;
    void semTripulantes(Mapa &mapa) override;
    void consumirAgua() override;
    int getMaxTripulantes() const override;
    //void reabastecerAgua() override;
    Caravana* clone() const override;  // Método virtual

};

#endif //TP_POO_CARAVANACOMERCIO_H
