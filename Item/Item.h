//
// Created by Duarte Santos on 19/12/2024.
//

#ifndef TP_POO_ITEM_H
#define TP_POO_ITEM_H

#include <string>
#include "../Buffer/Mapa.h"

class Caravana; // Forward declaration para evitar dependências circulares
//class Mapa;

class Item {

private:
    int linha, coluna;
    int duracao; // Duração restante em instantes
    std::string tipo; // Tipo do item

public:
    Item(Mapa& mapa, const std::string& tipo,int linha, int coluna);
    virtual ~Item() = default;

    // Métodos para acesso aos atributos
    int getDuracao() const;
    std::string getTipo() const;
    int getLinha() const;
    int getColuna() const;

    // Métodos principais
    void decrementarDuracao(); // Decrementa a duração do item
    virtual void efeito(Caravana& caravana, Mapa& mapa) = 0;// Define o efeito ao ser apanhado
    virtual Item* clone() const = 0;
    Item& operator=(const Item& other);

};


#endif //TP_POO_ITEM_H
