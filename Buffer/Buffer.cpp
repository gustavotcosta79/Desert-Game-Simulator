//
// Created by Duarte Santos on 19/11/2024.
//
#include <iostream>

#include "Buffer.h"

using namespace std;

Buffer::Buffer(int l, int c) : linhas(l), colunas(c),cursorLinha(0),cursorColuna(0) {
    matriz = new char*[linhas]; //->Alocacao da memoria dinamica para as linhas do buffer
    for (int i = 0; i < linhas;i++){
        matriz[i] = new char[colunas];//->Alocacao da memoria para cada linha
    }
    esvaziar(); //-> INICIALIZAR O BUFFER SÓ COM ESPACOS
}

Buffer::Buffer() : linhas(20), colunas(20),cursorLinha(0),cursorColuna(0){
    matriz = new char*[linhas];
    for (int i = 0; i < linhas; i++) {
        matriz[i] = new char[colunas];
    }
    esvaziar();
}

Buffer::~Buffer() {
    for (int i = 0; i< linhas; i++){
        delete [] matriz [i]; //-> liberta cada linha alocada
    }
    delete []matriz; //->liberta para as linhas
}

int Buffer::getLinhas() const {
    return linhas;
}

int Buffer::getColunas() const {
    return colunas;
}

void Buffer::esvaziar() {
    for (int i = 0;i<linhas;i++){
        for (int j = 0; j<colunas;j++){
            matriz[i][j] = ' ';
        }
    }
}

void Buffer::imprimir() const {
    for (int i = 0; i<linhas; i++){
        for (int j = 0;j<colunas;j++){
            cout << matriz[i][j];
        }
        cout<<endl;
    }
}

void Buffer::moverCursor(int l, int c) {
    if (l>=0 && c >= 0 && l<linhas && c<colunas){ //verifica se os parametros estao dentro dos limites
        cursorLinha = l;
        cursorColuna = c;
    }
}

void Buffer::inserirChar(char ch) {
    if (cursorLinha < linhas && cursorColuna < colunas){
        matriz [cursorLinha][cursorColuna] = ch; //-> associa o caracter na posicao especifica do cursor
        cursorColuna ++ ; //move o cursor
    }
    if (cursorColuna >= colunas){ // -> verifica se o cursor chegou a ultima posicao da linha
        cursorColuna = 0;
        cursorLinha++;
    }
}

void Buffer::inserirString(const char *str) {
    while (*str){ // -> avanca pela string, escrevendo caracter por caracter
        inserirChar(*str);
        str++; // -> avanca a string para a proxima posicao
    }
}

void Buffer::inserirInt(int num) {
    char buffer[20]; //buffer temp
    snprintf (buffer,sizeof(buffer),"%d",num); ///->formata o num e armazena a string resultante no buffer
    inserirString(buffer); //passa para funcao inserirString para tratar o inteiro como uma string por este ter sido convertido para string
}

Buffer& Buffer::operator<<(char ch) {
    inserirChar(ch);
    return *this; //-> retorna o proprio objeto para permitir encadeamento
}
Buffer& Buffer::operator<<(const char *str) {
    inserirString(str);
    return *this;
}

Buffer& Buffer::operator<<(int num) {
    inserirInt(num);
    return *this;
}

void Buffer::setColunas(int c) {
    colunas = c;
}
void Buffer::setLinhas(int l) {
    linhas = l;
}



char& Buffer::at(int linha, int coluna){
    if (linha >= 0 && colunas >= 0 && linha < linhas && coluna < colunas){
        return matriz[linha][coluna];
    }

    throw "Posicao invalida";
}

Buffer::Buffer(const Buffer& other) : linhas(other.linhas), colunas(other.colunas), cursorLinha(other.cursorLinha), cursorColuna(other.cursorColuna) {
    // Alocar memória para a matriz
    matriz = new char*[linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new char[colunas];
        // Copiar os dados linha por linha
        std::copy(other.matriz[i], other.matriz[i] + colunas, matriz[i]);
    }
}

Buffer& Buffer::operator=(const Buffer& other) {
    if (this != &other) { // Verifica auto-atribuição
        // Liberar memória alocada previamente
        for (int i = 0; i < linhas; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;

        // Atualizar dimensões
        linhas = other.linhas;
        colunas = other.colunas;

        // Realocar memória para a nova matriz
        matriz = new char*[linhas];
        for (int i = 0; i < linhas; ++i) {
            matriz[i] = new char[colunas];
            std::copy(other.matriz[i], other.matriz[i] + colunas, matriz[i]);
        }

        cursorLinha = other.cursorLinha;
        cursorColuna = other.cursorColuna;
    }
    return *this;
}
/*
Buffer::Buffer(const Buffer& other) {
    linhas = other.linhas;
    colunas = other.colunas;

    // Aloca memória para a nova matriz
    matriz = new char*[linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new char[colunas];
        std::copy(other.matriz[i], other.matriz[i] + colunas, matriz[i]);
    }

    cursorLinha = other.cursorLinha;
    cursorColuna = other.cursorColuna;
}

Buffer& Buffer::operator=(const Buffer& other) {
    if (this != &other) { // Evitar auto-atribuição
        // Libera a memória alocada previamente
        for (int i = 0; i < linhas; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;

        // Copia os atributos do objeto `other`
        linhas = other.linhas;
        colunas = other.colunas;

        // Realoque a memória para a nova matriz
        matriz = new char*[linhas];
        for (int i = 0; i < linhas; ++i) {
            matriz[i] = new char[colunas];
            std::copy(other.matriz[i], other.matriz[i] + colunas, matriz[i]);
        }

        cursorLinha = other.cursorLinha;
        cursorColuna = other.cursorColuna;
    }
    return *this; // Retorna o próprio objeto
}

 */