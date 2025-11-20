//
// Created by Duarte Santos on 21/12/2024.
//

#ifndef TP_POO_CARAVANASECRETA_H
#define TP_POO_CARAVANASECRETA_H
#include "../Caravana/Caravana.h"
#include "../Buffer/Mapa.h"


class CaravanaSecreta : public Caravana {

    int turnosSemTripulantes;
    int turnosVisivel;
    bool invisivel;

public:
    CaravanaSecreta (int id, int linha, int coluna);


    void atualizarInvisibilidade (Mapa &mapa);
    void tornarVisivel (Mapa &mapa);
    void moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador) override; //-> movimento autónomo
    void isTempestade () override; // -> comportamento em tempestade
    void semTripulantes (Mapa &mapa) override; // -> comportamento sem tripulação
    void consumirAgua() override;
    int getMaxMovimentos() const override;
    int getMaxTripulantes() const override;
    Caravana* clone() const override;  // Método virtual
};


#endif //TP_POO_CARAVANASECRETA_H
