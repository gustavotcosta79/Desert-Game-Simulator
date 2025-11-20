//
// Created by Duarte Santos on 21/11/2024.
//

#ifndef TP_POO_CARAVANA_H
#define TP_POO_CARAVANA_H

#include <vector>
#include "../Buffer/Mapa.h"
#include "string"
#include "../Cidade.h"

class Cidade;

class Caravana {
protected:
    static int proximoID;
    int capAtualAgua, nTripulantes, capAtualCarga,linha,coluna,id,capCargaTotal,capAguaTotal;
    char tipo;
    bool destruida ; // nova variável para o estado da caravana
    int nMovimentos = 0;
    bool autoGestao = false;
    bool isGato = false;

public:
    Caravana (int id, int linha, int coluna, int capCarga, int capAgua, int trip, const char &tipo);

    virtual ~Caravana();
    int getId () const;

    int getLinha() const;
    int getColuna() const;
    int getTripulacao () const;
    bool getDestruida() const;
    char getTipo() ;
    int getAguaTotal () const;
    int getAguaAtual () const;
    int getCargaTotal () const;
    int getCargaAtual () const;
    int getNMovimentos() const;
    void setCarga (int num);
    void setAutoGestao(bool estado);  // Define se está em auto-gestão
    bool isAutoGestao() const;       // Retorna se está em auto-gestão

    void setNMOVIMENTOS0 ();
    void setNMovimentos(int num );
    void setDestruida();
    int perderTripulantes (int valor);
    int ganhaTripulantes(int valor) ;
    void adicionaCarga(int qntd);
    void removeCarga(int qntd);
    void atualizarNoMapa(Mapa &mapa) const;
    void setNovaPosicao(int novaLinha,int novaColuna);

    void reabastecerAgua() ;
    void setGato (bool estado);
    bool getGato () const;

    //****//
    virtual int moverCaravanaUmaPosicao( Mapa& mapa, std::string direcao);
    virtual int getMaxMovimentos() const = 0; // Método virtual puro
    virtual void moverAutonomo (Mapa &mapa, const std::vector<Caravana*>& caravanasJogador = {},const std::vector<Cidade>& cidadesJogador = {}) = 0; //-> movimento autónomo
    virtual void isTempestade () = 0; // -> comportamento em tempestade
    virtual void semTripulantes (Mapa &mapa) = 0; // -> comportamento sem tripulação
    virtual void consumirAgua() = 0;
    virtual int getMaxTripulantes() const = 0; // Número máximo de tripulantes
    virtual Caravana* clone() const = 0;  // Método virtual
};




#endif //TP_POO_CARAVANA_H
