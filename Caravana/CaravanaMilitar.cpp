//
// Created by Duarte Santos on 20/12/2024.
//

#include "CaravanaMilitar.h"
#include "cstdlib"
#include "iostream"
#include "string"

using namespace std;


CaravanaMilitar::CaravanaMilitar(int id, int linha, int coluna)
: Caravana(id, linha, coluna, 5, 400, 40, 'M'), turnosSemTripulantes(0), ultimaDirecao("C") {


}

bool CaravanaMilitar::verificarBarbarosProximos( Mapa &mapa) {
    for (int i = -6; i <= 6; i++) {
        for (int j = -6; j <= 6; j++) {
            int verificaLinha = (linha + i + mapa.getBuffer().getLinhas() % mapa.getBuffer().getLinhas()); //exemplo: se linha = 0 e i = -1 irá ficar (-1 + mapa.getBuffer().getLinhas() % mapa.getBuffer().getLinhas()
                                                                                                            // como nao existe linhas = -1, teriamos que ir para a última linha do buffer
                                                                                                            // imaginando que as linhas sao 10 irá ficar
                                                                                                            //(9) % mapa.getBuffer().getLinhas() que e igual a 9
            int verificaColuna = (coluna + j + mapa.getBuffer().getColunas()); //mesma logica para as colunas

            if (mapa.getBuffer().at(verificaLinha, verificaColuna) == '!') {
                return true;
            }
        }
    }
    return false;
}

void CaravanaMilitar::moverParaBarbaros(Mapa &mapa) {
    int alvoLinha = 0, alvoColuna = 0;
    int menorDistancia = 7; //o maximo de distancia que a caravana consegue ver e a 6 celulas de distancia
    for (int i = -6; i <= 6; i++){
        for (int j = -6; j <= 6; j++ ){
            int verificaLinha = (linha + i + mapa.getBuffer().getLinhas() % mapa.getBuffer().getLinhas()); //exemplo: se linha = 0 e i = -1 irá ficar (-1 + mapa.getBuffer().getLinhas() % mapa.getBuffer().getLinhas()
                                                                                                            // como nao existe linhas = -1, teriamos que ir para a última linha do buffer
                                                                                                            // imaginando que as linhas sao 10 irá ficar
                                                                                                            //(9) % mapa.getBuffer().getLinhas() que e igual a 9
            int verificaColuna = (coluna + j + mapa.getBuffer().getColunas()); //mesma logica para as colunas

            if (mapa.getBuffer().at(verificaLinha, verificaColuna) == '!'){
                int distancia = 0;
                if (i < 0){
                    distancia = distancia + (-i);
                }
                else{
                    distancia = distancia + i;
                }

                if (j < 0){
                    distancia = distancia + (-j);
                }
                else{
                    distancia = distancia + j;
                }

                if (distancia < menorDistancia ){
                    menorDistancia = distancia;
                    alvoLinha = verificaLinha;
                    alvoColuna = verificaColuna;
                }
            }
        }
    }
    if (alvoLinha != 0 && alvoColuna != 0){
        if (alvoLinha > linha){
            linha ++;
        }
        else if (alvoLinha < linha){
            linha --;
        }
        if (alvoColuna > coluna){
            coluna ++;
        }
        else if (alvoColuna < coluna){
            coluna --;
        }
        atualizarNoMapa(mapa);
        cout << "Caravana militar movendo-se em direcao aos barbaros!"<<endl;

    }
}

void CaravanaMilitar:: moverAutonomo(Mapa& mapa, const std::vector<Caravana*>& caravanasJogador,const std::vector<Cidade>& cidadesJogador) {
    int movimentosRestantes = 3;

    if (verificarBarbarosProximos(mapa)){
    while (movimentosRestantes  > 0){
        moverParaBarbaros(mapa);
        movimentosRestantes --;
        if (movimentosRestantes == 0){
            break;
            }
        }
    }
    else
        cout << "Sem barbaros proximos, a caravana ira ficar parada." << endl;
}

void CaravanaMilitar::isTempestade() {
    int chanceDeSerDestruido = rand() % 100;
    if (chanceDeSerDestruido <= 33){
        cout << "Caravana foi apanhada numa tempestade e foi destruida!" << endl;

        nTripulantes = 0;
        capAtualCarga = 0;
        capAtualAgua = 0;
        destruida = true;
        return;
    }
    int tripulantesPerdidos = (nTripulantes * 10) / 100;
    perderTripulantes(tripulantesPerdidos);
    cout << "A caravana militar perdeu "<< tripulantesPerdidos << " tripulantes, por causa da tempestade!" << endl;

}

void CaravanaMilitar::semTripulantes(Mapa &mapa) {
    if (turnosSemTripulantes >= 7) {
        std::cout << "Caravana militar desapareceu após 7 turnos sem tripulacao." << endl;
        mapa.getBuffer().at(linha, coluna) = '.'; // Remove a caravana do mapa
        return;
    }

    moverCaravanaUmaPosicao(mapa,ultimaDirecao);
    turnosSemTripulantes ++;
    std::cout << "Caravana militar moveu-se para " << ultimaDirecao << " sem tripulacao. Turnos sem tripulacao: "
              << turnosSemTripulantes << "." << endl;
}

void CaravanaMilitar::consumirAgua(){
    int litrosGastos = 3;

    if (nTripulantes < 20){
        litrosGastos = 1;
    }

    if (nTripulantes == 0){
        litrosGastos = 0;
    }

    capAtualAgua = capAtualAgua - litrosGastos;

    if (capAtualAgua < 0){
        capAtualAgua = 0;
    }

    cout << "(Caravana Militar) Agua restante: " << capAtualAgua << " litros. " << endl;
}


int CaravanaMilitar:: moverCaravanaUmaPosicao( Mapa& mapa, string direcao){

    int novaLinha = linha, novaColuna = coluna;
    if (direcao == "D"){
        novaColuna++;
    }
    else if (direcao == "E"){
        novaColuna--;
    }
    else if (direcao == "C"){
        novaLinha--;
    }
    else if (direcao == "B"){
        novaLinha++;
    }
    else if (direcao == "CE"){
        novaLinha--;
        novaColuna--;
    }
    else if (direcao == "CD"){
        novaLinha--;
        novaColuna++;
    }
    else if (direcao == "BE"){
        novaLinha++;
        novaColuna--;
    }
    else if (direcao == "BD"){
        novaLinha++;
        novaColuna++;
    }
    else{
        cerr << "Direcao invalida"<<endl;
        return 0;

    }

    if (novaLinha < 0 )
        novaLinha = mapa.getBuffer().getLinhas() - 1;
    if (novaColuna < 0)
        novaColuna = mapa.getBuffer().getColunas() - 1;
    if (novaLinha >= mapa.getBuffer().getLinhas())
        novaLinha = 0;
    if(novaColuna >= mapa.getBuffer().getColunas())
        novaColuna = 0;

    // Obter o conteúdo da célula destino
    char destino = mapa.getBuffer().at(novaLinha, novaColuna);

    // Verificar se a célula é válida (deserto ou cidade)
    if (destino != '.' && (destino < 'a' || destino > 'z')) {
        cout << "Movimento impossivel: a celula (" << novaLinha << ", " << novaColuna
             << ") nao e valida para movimento." << endl;
        return 0; // Interrompe o movimento
    }

    ///verifica se o destino é cidade e se for, permanece o caracter da cidade
    if (destino >= 'a' && destino <= 'z'){
        reabastecerAgua();
        mapa.getBuffer().at(novaLinha, novaColuna) = destino;
    }else{
        mapa.getBuffer().at(novaLinha, novaColuna) = (char)('0' + id % 10);
    }

    setNovaPosicao(novaLinha,novaColuna);

    ultimaDirecao = direcao;



    return 1;

}

int CaravanaMilitar::getMaxMovimentos() const {
    return 3;
}

int CaravanaMilitar:: getMaxTripulantes() const {
    return 40;
}
/*
void CaravanaMilitar:: reabastecerAgua() {
    capAtualAgua = capAguaTotal;
    cout << "A agua da caravana "<< id << "foi reabastecida. Tem agora: "<< capAtualAgua << " litros. " << endl;
}
*/

Caravana* CaravanaMilitar:: clone() const{
    return new CaravanaMilitar(*this);
}

