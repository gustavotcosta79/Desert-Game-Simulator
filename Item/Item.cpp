//
// Created by Duarte Santos on 19/12/2024.
//

#include "Item.h"

// Implementação da classe base Item
Item::Item(Mapa& mapa, const std::string& tipo, int linha, int coluna) : tipo(tipo), linha(linha), coluna(coluna) {
    // Agora buscamos o valor de duracao_item diretamente do Mapa
    this->duracao = mapa.getConfiguracao("duracao_item");
}

int Item::getDuracao() const {
    return duracao;
}

std::string Item::getTipo() const {
    return tipo;
}

void Item::decrementarDuracao() {
    if (duracao > 0) {
        --duracao;
    }
}

Item& Item:: operator=(const Item& other){
    if (this!= &other){
        duracao = other.duracao;
        tipo = other.tipo;
    }
    return *this;
}

int Item::getLinha() const {
    return linha;
}

int Item::getColuna() const {
    return coluna;
}


