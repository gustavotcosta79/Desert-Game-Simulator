//
// Created by Duarte Santos on 20/12/2024.
//

#include "CaravanaComercio.h"
#include <iostream>
#include <cstdlib>

using namespace std;

CaravanaComercio::CaravanaComercio(int id, int linha, int coluna)
        : Caravana(id, linha, coluna, 40, 200, 20, 'C'), turnosSemTripulantes(0) {
}

void CaravanaComercio::moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador) {
    // A caravana de comércio tenta se mover ao lado de outra caravana ou em direção a um item a 2 linhas/colunas
   int movimentosLivres = 2;
   while (movimentosLivres > 0){
    int novaLinha = linha;
    int novaColuna = coluna;

    mapa.getBuffer().at(linha, coluna) = '.';

    // Vamos tentar nos mover para proteger-se ou pegar um item
    if (rand() % 2 == 0) { // 50% de chance de mover para pegar item
        novaLinha = linha + (rand() % 3 - 1); // -1, 0 ou 1
        novaColuna = coluna + (rand() % 3 - 1); // -1, 0 ou 1
    } else {
        // Tentativa de se mover ao lado de outra caravana do usuário
        novaLinha = (linha + 1) % mapa.getBuffer().getLinhas();
        novaColuna = (coluna + 1) % mapa.getBuffer().getColunas();
    }
    // Atualiza a posição
    setNovaPosicao(novaLinha, novaColuna);
    atualizarNoMapa(mapa);
    movimentosLivres--;
    if (movimentosLivres == 0){
        break;
    }
   }
}

void CaravanaComercio::isTempestade() {
    // Garante que o gerador de números aleatórios é inicializado
    srand(time(0));
    // Verifica se a caravana está dentro da tempestade
    if (rand() % 100 < 50) {  // 50% de chance de ser afetada pela tempestade
        // Inicializa a variável para a probabilidade de destruição
        float probabilidadeDestruicao;

        // Se a carga ocupada for maior que 50%, a chance de destruição é de 50%
        if (capAtualCarga > capCargaTotal / 2) {
            probabilidadeDestruicao = 50.0;
        } else {
            probabilidadeDestruicao = 25.0;
        }

        // Gera um número aleatório entre 0 e 99
        int chance = rand() % 100;

        // Verifica se a caravana é destruída
        if (chance < probabilidadeDestruicao) {
            cout << "Caravana de Comercio destruida pela tempestade!" << endl;
            destruida = true;
        } else {
            cout << "Caravana de Comercio sobreviveu a tempestade!" <<endl;
            // Se não for destruída, perde 25% da carga
            capAtualCarga -= capAtualCarga / 4;  // Perde 25% da carga
            cout << "A caravana perdeu 25% da carga! Carga atual: " << capAtualCarga << endl;
        }
    }
}

void CaravanaComercio::semTripulantes(Mapa &mapa) {
    // Se a caravana ficar sem tripulantes, ela se move aleatoriamente
    // e depois desaparece após 5 turnos
    if (nTripulantes == 0) {
        turnosSemTripulantes++;

        std::cout << "Caravana de Comercio sem tripulantes!" << std::endl;
        std::cout << "A caravana se move aleatoriamente." << std::endl;

        // Se já passaram 5 turnos, a caravana desaparece
        if (turnosSemTripulantes >= 5) {
            std::cout << "Caravana de Comercio desapareceu após 5 turnos sem tripulantes." << std::endl;
            // Aqui, o código pode remover a caravana do mapa ou do sistema, dependendo da implementação do Mapa
        } else {
            int novaLinha = rand() % 10; // Movimento aleatório
            int novaColuna = rand() % 10; // Movimento aleatório
            setNovaPosicao(novaLinha, novaColuna);
            atualizarNoMapa(mapa); // Atualiza o mapa com a nova posição
        }
    }
}

void CaravanaComercio::consumirAgua() {
    int litrosGastados = 2;
    if (nTripulantes < 10){
        litrosGastados = 1;
    }

    if (nTripulantes == 0){
        litrosGastados = 0;
    }

    capAtualAgua = capAtualAgua - litrosGastados;
    if (capAtualAgua < 0){
        capAtualAgua = 0;
    }

    cout << "Agua restante: " << capAtualAgua << " litros. " << endl;
}

int CaravanaComercio::getMaxMovimentos() const {
    return 2;
}

int CaravanaComercio:: getMaxTripulantes() const {
    return 20;
}
/*
void CaravanaComercio::reabastecerAgua() {
    capAtualAgua = capAguaTotal;
    cout << "A agua da caravana "<< id << "foi reabastecida. Tem agora: "<< capAtualAgua << " litros. " << endl;

}
*/

Caravana* CaravanaComercio:: clone() const{
    return new CaravanaComercio(*this);
}