//
// Created by Duarte Santos on 21/11/2024.
//
using namespace std;

#include <iostream>
#include "Caravana.h"
#include "string"

//int Caravana::proximoID = 0;  // inicializar a variável estática


Caravana:: Caravana (int id, int linha, int coluna, int capCarga, int capAgua, int trip, const char& tipo)
    : id (id),linha (linha), coluna(coluna), capCargaTotal(capCarga), capAtualCarga(0),
      nTripulantes(trip), capAguaTotal(capAgua), capAtualAgua(capAgua), tipo (tipo), destruida(false){
    if (id > 9){
        throw ("Numero maximo de caravanas atingido!!");
    }

}

int Caravana::getId()const{
    return id;
}

int Caravana::getColuna() const {
    return coluna;
}
int Caravana::getLinha() const {
    return linha;
}

int Caravana::getTripulacao() const {
    return nTripulantes;
}

bool Caravana::getDestruida() const {
    return destruida;
}


void Caravana::setDestruida() {

    destruida= true;
}

int Caravana::perderTripulantes(int valor) {
    if (valor < 0){
        //cout<< "Nao e possivel remover tripulantes com um valor negativo "<<endl;
        return 0;
    }
    if (valor > nTripulantes){
        //cout<< "Quantidade que quer remover excede a tripulacao total. Toda a tripulacao sera removida!"<<endl;
        nTripulantes = 0;
    }
    else {
        nTripulantes = nTripulantes - valor;
        //cout<< "Tripulantes removidos! Tripulantes atuais: "<<nTripulantes<<endl;
    }
    return valor;
}

int Caravana::ganhaTripulantes(int valor) {
    if (valor < 0){
        cout<< "Nao e possivel adicionar tripulantes com um valor negativo "<<endl;
        return 0;
    }
    else {
        nTripulantes = nTripulantes + valor;
        cout<< "Tripulantes removidos! Tripulantes atuais: "<<nTripulantes<<endl;
    }
    return valor;
}

char Caravana:: getTipo() {
    return tipo;
}

void Caravana::atualizarNoMapa(Mapa &mapa) const{
    mapa.getBuffer().at(linha, coluna) = (char)('0' + id % 10);
}

void Caravana::setNovaPosicao(int novaLinha, int novaColuna) {
    linha = novaLinha;
    coluna = novaColuna;
}

int Caravana:: moverCaravanaUmaPosicao( Mapa& mapa, string direcao){
    ///if movimentos restantes > 0 {
    int novaLinha = linha, novaColuna = coluna;
    if (direcao == "D"){
        novaColuna++;
        ///movimentosRestantes--;
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
    else {
        cerr << "Direcao invalida" << endl;
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
        cout << "Nao e possivel mover: a celula (" << novaLinha << ", " << novaColuna
             << ") nao e valida para movimento." << endl;
        return 0; // Interrompe o movimento
    }

    ///verifica se o destino é cidade e se for, permanece o caracter da cidade
    if (destino >= 'a' && destino <= 'z'){
        reabastecerAgua();
        mapa.getBuffer().at(novaLinha, novaColuna) = destino;
    }else{
        char pila =('0' + id % 10);
        mapa.getBuffer().at(novaLinha, novaColuna) = pila;
    }
    setNovaPosicao(novaLinha,novaColuna);

    return 1;
}

void Caravana::adicionaCarga(int qntd) {
    int aux;

    if (qntd < 0 ){
        cout<<"Nao e possivel adicionar cargas negativas!"<<endl;
        return;
    }
    aux = capAtualCarga + qntd;
    if (aux > capCargaTotal){
        cout << "Carga excede a carga maxima. Apenas foi adicionado"<< (capCargaTotal - capAtualCarga) << " toneladas"<<endl;
        capAtualCarga = capCargaTotal;
    }
    else{
        capAtualCarga = aux;
        cout << "Carga adicionada com sucesso. Carga atual ->"<<capAtualCarga<< " toneladas"<<endl;
    }
}

void Caravana::removeCarga(int qntd) {

    if (qntd < 0 ){
        cout<<"Nao e possivel remover cargas negativas!"<<endl;
        return;
    }
    if (capAtualCarga < qntd){
        cout<< "Quantidade que quer remover excede a carga atual. Toda a carga sera removida!"<<endl;
        capAtualCarga = 0;
    }
    else {
        capAtualCarga = capAtualCarga- qntd;
    }
}
int Caravana:: getAguaTotal () const{
    return capAguaTotal;
}

int Caravana::getAguaAtual() const {
    return capAtualAgua;
}

int Caravana::getCargaTotal() const {
    return capCargaTotal;
}

int Caravana::getCargaAtual() const {
    return capAtualCarga;
}
void Caravana::setCarga (int num){
    capAtualCarga = capAtualCarga + num;
}

void Caravana::setNMovimentos(int num ) {
    nMovimentos+= num;
}

int Caravana::getNMovimentos() const {
    return nMovimentos;
}

void Caravana::setAutoGestao(bool estado) {
    autoGestao = estado;
    if (autoGestao) {
        std::cout << "Caravana " << id << " esta agora em modo automatico." << std::endl;
    } else {
        std::cout << "Caravana " << id << " saiu do modo automatico." << std::endl;
    }
}

bool Caravana::isAutoGestao() const {
    return autoGestao;
}

void Caravana::setNMOVIMENTOS0() {
    nMovimentos = 0;
}

void Caravana::reabastecerAgua() {
    capAtualAgua = capAguaTotal;
}

void Caravana:: setGato (bool estado) {
    isGato = estado;
}

bool Caravana::getGato() const {
    return isGato;
}

Caravana::~Caravana() = default;
