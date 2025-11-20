//
// Created by Duarte Santos on 21/12/2024.
//

#include "CaravanaSecreta.h"
#include <cstdlib>
#include "iostream"
using namespace std;
CaravanaSecreta:: CaravanaSecreta (int id, int linha, int coluna)
: Caravana(id, linha, coluna,20,150,10,'S'), invisivel(true), turnosVisivel(0), turnosSemTripulantes(0){}

void CaravanaSecreta::atualizarInvisibilidade (Mapa &mapa){
    if (!invisivel && turnosVisivel > 0){
        turnosVisivel --;

        if (turnosVisivel == 0){
            invisivel = true;
            cout << "A caravana secreta tornou-se invisivel novamente!" << endl;

            mapa.getBuffer().at(linha,coluna) = '.';
        }
    }
}

void CaravanaSecreta::tornarVisivel(Mapa &mapa) {
    if (invisivel){
        invisivel = false;
        turnosVisivel = 3;
        cout << "A caravana secreta esta visivel!" << endl;

        mapa.getBuffer().at(linha, coluna) = (char)id;
    }
}

void CaravanaSecreta:: moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador){
     if (!invisivel){
         int movimentosRestantes = 2;

         while (movimentosRestantes > 0) {
         int novaLinha = linha + (rand() % 3 - 1); // -1, 0 ou 1
         int novaColuna = coluna + (rand() % 3 - 1); // -1, 0 ou 1
         novaLinha = (novaLinha + mapa.getBuffer().getLinhas()) % mapa.getBuffer().getLinhas();
         novaColuna = (novaColuna + mapa.getBuffer().getColunas()) % mapa.getBuffer().getColunas();

         // Atualizar no mapa
         mapa.getBuffer().at(linha, coluna) = '.';
         linha = novaLinha;
         coluna = novaColuna;
         mapa.getBuffer().at(linha, coluna) = char(id);
         cout << "Caravana secreta movida para (" << linha << ", " << coluna << ")" << endl;
         movimentosRestantes --;
         }
     } else {
         cout << "Caravana secreta esta invisivel e nao se moveu." << endl;
     }
}

void CaravanaSecreta::consumirAgua() {
    double litrosGastos = 1.0;
    if (nTripulantes < 5){
        litrosGastos = 0.5;
    }
    if (nTripulantes == 0){
        litrosGastos = 0.0;
    }
    capAtualAgua = capAtualAgua - (int)litrosGastos;
    if (capAtualAgua < 0){
        capAtualAgua = 0;
    }
    cout << "(CaravanaSecreta) Agua restante: " << capAtualAgua << "litros. " << endl;
}

void CaravanaSecreta::isTempestade() {
    // Chance de perder 10% dos tripulantes e 10% da carga
    int chanceDePerderTripulantes = rand() % 100;
    int chanceDePerderCarga = rand() % 100;

    // Verifica a chance de perder tripulantes
    if (chanceDePerderTripulantes < 50) {
        int tripulantesPerdidos = (nTripulantes * 10) / 100; // Perde 10% dos tripulantesº
        if (tripulantesPerdidos > 0){
            perderTripulantes(tripulantesPerdidos);
            cout << "A caravana secreta perdeu " << tripulantesPerdidos << " tripulantes por causa da tempestade." << endl;
        }
    }

    // Verifica a chance de perder carga
    if (chanceDePerderCarga < 10) { // 10% de chance
        int cargaPerdida = (capAtualCarga * 10) / 100; // Perde 10% da carga

        if (cargaPerdida > 0) {
            capAtualCarga -= cargaPerdida;
            if (capAtualCarga < 0) {
                capAtualCarga = 0;
            }
            cout << "A caravana secreta perdeu " << cargaPerdida << " de carga por causa da tempestade." << endl;
        }

        // Desativa a invisibilidade temporariamente para permitir recuperação
        if (invisivel) {
            invisivel = false;
            cout << "A invisibilidade da caravana secreta foi desativada por causa da tempestade." << endl;
        }
    }
}

void CaravanaSecreta:: semTripulantes(Mapa &mapa) {
   if (nTripulantes == 0){
       turnosSemTripulantes++;
       if (turnosSemTripulantes >= 7){
           cout << "A caravana secreta desapareceu apos 7 turnos sem tripulantes." << endl;
           mapa.getBuffer().at(linha,coluna) = '.';
           return;
       }
       // Move a caravana de forma aleatória
       int novaLinha = rand() % mapa.getBuffer().getLinhas();  // Posição aleatória para linha
       int novaColuna = rand() % mapa.getBuffer().getColunas();  // Posição aleatória para coluna

       // Atualiza a posição da caravana no mapa
       setNovaPosicao(novaLinha, novaColuna);
       atualizarNoMapa(mapa);  // Atualiza o mapa com a nova posição

       cout << "A caravana secreta moveu-se aleatoriamente para uma nova posicao. Turnos sem tripulantes: "
            << turnosSemTripulantes << "." << endl;
   }

}

int CaravanaSecreta::getMaxMovimentos() const {
    return 7;
}

int CaravanaSecreta:: getMaxTripulantes() const {
    return 10;
}

Caravana* CaravanaSecreta:: clone() const{
    return new CaravanaSecreta(*this);
}


