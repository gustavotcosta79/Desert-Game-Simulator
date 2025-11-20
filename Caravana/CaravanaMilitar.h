//
// Created by Duarte Santos on 20/12/2024.
//

#ifndef TP_POO_CARAVANAMILITAR_H
#define TP_POO_CARAVANAMILITAR_H
#include "Caravana.h"
#include "string"
#include "../Buffer/Mapa.h"

class CaravanaMilitar : public Caravana {
private:
    int turnosSemTripulantes;
    std::string ultimaDirecao;




public:
    int getMaxMovimentos() const override ;

    CaravanaMilitar( int id, int linha, int coluna);
    void moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador) override; //-> movimento autónomo
     void isTempestade () override; // -> comportamento em tempestade
     void semTripulantes (Mapa &mapa) override; // -> comportamento sem tripulação
     void consumirAgua() override;
     int moverCaravanaUmaPosicao( Mapa& mapa, std::string direcao) override;
    bool verificarBarbarosProximos( Mapa &mapa) ;
    void moverParaBarbaros(Mapa &mapa);
    int getMaxTripulantes() const override;
    //void reabastecerAgua() override;
    Caravana* clone() const override;  // Método virtual

};


#endif //TP_POO_CARAVANAMILITAR_H
