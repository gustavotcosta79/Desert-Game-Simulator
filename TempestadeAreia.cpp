//
// Created by Duarte Santos on 19/12/2024.
//

#include "TempestadeAreia.h"
#include "Buffer/Mapa.h"
#include "iostream"

using namespace std;

TempestadeAreia::TempestadeAreia(int linhaCentro, int colunaCentro, int raio) : linhaC(linhaCentro), colunaC (colunaCentro), raio(raio), ativa(true){

}

TempestadeAreia::TempestadeAreia(){}

bool TempestadeAreia:: isAtiva () const{
   return ativa;
}

bool TempestadeAreia:: isDentro(int linha_caravana, int coluna_caravana) const{
    return (linha_caravana >= linhaC - raio && linha_caravana <= linhaC + raio) &&
           (coluna_caravana >= colunaC - raio && coluna_caravana <= colunaC + raio);
}

void TempestadeAreia::setInativa (){
    ativa = false;
}