//
// Created by Duarte Santos on 19/12/2024.
//

#include <algorithm>
#include "Cidade.h"

using namespace std;

Cidade::Cidade(char nome, int l, int c) : nome(nome), linha(l), coluna(c) {}

int Cidade::getLinha() const {
    return linha;
}

int Cidade::getColuna() const {
    return coluna;
}

char Cidade::getNome() const {
    return nome;
}



Cidade *Cidade::operator[](char nome) {
    return nullptr;
}

Cidade::Cidade() {

}


void Cidade::setCComercio(bool estado)  {
    cComercio = estado;
}

void Cidade::setCMilitar(bool estado) {
    cMilitar = estado;
}

void Cidade::setCSecreta(bool estado)  {
    cSecreta = estado;
}


bool Cidade::getCComercio() const {
    return cComercio;
}

bool Cidade::getCMilitar() const  {
    return cMilitar;
}

bool Cidade::getCSecreta() const {
    return cSecreta;
}