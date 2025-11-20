#include "CaravanaBarbara.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

CaravanaBarbara::CaravanaBarbara(int linha, int coluna, const Mapa& mapa)
        : Caravana(-1, linha, coluna, 0, 0, 40, '!'), turnosAtivos(0), desaparecida(false) {
    turnos_max = mapa.getConfiguracao("duracao_barbaros");  // Obtém o limite de turnos do mapa
}

void CaravanaBarbara::moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador) {
    if (desaparecida) return; // Não faz nada se a caravana já desapareceu

    turnosAtivos++;

    // Verifica se atingiu o limite de turnos
    if (turnosAtivos >= turnos_max) {
        cout << "Caravana Barbara desapareceu apos " << turnos_max << " turnos!" << endl;
        desaparecida = true;
        return;
    }

    // Movimento: Aleatório ou perseguindo uma caravana
    int novaLinha = linha, novaColuna = coluna;

    // Localiza uma caravana do jogador a uma distância <= 8
    Caravana* alvo = nullptr;
    for (Caravana* caravana : caravanasJogador) {
        if(!caravana->getDestruida()){//verifica se a caravana nao esta destruida
            int distancia = abs(caravana->getLinha() - linha) + abs(caravana->getColuna() - coluna);
            if (distancia <= 8) {
                alvo = caravana;
                break;
            }
        }
    }

    // Verifica se a caravana está numa cidade
    bool estaEmCidade = false;
    char simboloCidade = '\0';

    // Guarda a linha e a coluna antes de mover
    int linhaAnterior = getLinha();
    int colunaAnterior = getColuna();

    // Verifica se a posição atual da caravana corresponde a uma cidade
    for (const auto& cidade : cidadesJogador) {
        if (cidade.getLinha() == linhaAnterior && cidade.getColuna() == colunaAnterior) {
            estaEmCidade = true;
            simboloCidade = cidade.getNome(); // Armazena o símbolo da cidade
            break;
        }
    }

    if (alvo) {
        // Persegue a caravana do jogador
        if (alvo->getLinha() > linha) novaLinha++;
        else if (alvo->getLinha() < linha) novaLinha--;

        if (alvo->getColuna() > coluna) novaColuna++;
        else if (alvo->getColuna() < coluna) novaColuna--;
    } else {
        // Movimento aleatório
        novaLinha = linha + (rand() % 3 - 1); // -1, 0 ou 1
        novaColuna = coluna + (rand() % 3 - 1); // -1, 0 ou 1
    }
    char destino = mapa.getBuffer().at(novaLinha, novaColuna);

    // Verificar se a célula é válida (deserto ou cidade)
    if (!(destino != '.' && (destino < 'a' || destino > 'z'))) {

        if (estaEmCidade) {
            // Se estava numa cidade, mantém a letra da cidade na posição anterior
            mapa.getBuffer().at(linhaAnterior, colunaAnterior) = simboloCidade;
        } else {
            // Se estava no deserto (.), coloca um "." na posição anterior
            mapa.getBuffer().at(linhaAnterior, colunaAnterior) = '.';
        }

        setNovaPosicao(novaLinha, novaColuna);
        atualizarNoMapa(mapa);
        ///verifica se o destino é cidade e se for, permanece o caracter da cidade
        if (destino >= 'a' && destino <= 'z'){
            mapa.getBuffer().at(novaLinha, novaColuna) = destino;
        }else{
            mapa.getBuffer().at(novaLinha, novaColuna) = '!';
        }
    }


}

void CaravanaBarbara::isTempestade() {
    if (desaparecida) return; // Não faz nada se já desapareceu

    if (rand() % 4 == 0) { // 25% de chance de destruição total
        cout << "Caravana Barbara foi destruida por uma tempestade!" << endl;
        desaparecida = true;
        return;
    }

    // Perde 10% dos bárbaros
    nTripulantes -= nTripulantes / 10;
    if (nTripulantes <= 0) {
        cout << "Caravana Barbara desapareceu devido a tempestade!" << endl;
        desaparecida = true;
    }
}

bool CaravanaBarbara::getDesaparecida() const {
    return desaparecida;
}


int CaravanaBarbara::getMaxTripulantes() const {
    return 40; // Número fixo de bárbaros
}

int CaravanaBarbara::getMaxMovimentos() const {
    return 1;
}

void CaravanaBarbara::setIncrementaTurno() {
    turnosAtivos ++;
}

Caravana* CaravanaBarbara:: clone() const{
    return new CaravanaBarbara(*this);
}

void CaravanaBarbara::consumirAgua() {

}

void CaravanaBarbara::semTripulantes(Mapa &mapa) {

}


