//
// Created by Duarte Santos on 19/12/2024.
//

#ifndef TP_POO_CIDADE_H
#define TP_POO_CIDADE_H
#include "vector"
#include "Caravana/Caravana.h"
#include <string>

class Cidade {
private:
    char nome;
    int linha, coluna;
    //std::vector<Caravana*> caravanas;
    int qntdMercadorias; //-> mercadorias disponiveis para venda (configuravel)
    ///cada cidade tem disponivel para venda uma caravana de cada tipo
    bool cComercio= false,cMilitar = false, cSecreta = false;
public:
    Cidade();
    Cidade (char nome,int linha, int coluna);
    int getLinha() const;
    int getColuna() const;
    char getNome()const;

    //void adicionaCaravana(Caravana* caravana);
    //void removeCaravana(Caravana* caravana);
    //const std::vector<Caravana*> &listarCaravanas () const;
    void setCComercio (bool estado) ;
    void setCMilitar (bool estado) ;
    void setCSecreta (bool estado) ;
    bool getCComercio () const;
    bool getCMilitar () const;
    bool getCSecreta () const;


    Cidade* operator[](char nome);

};


#endif //TP_POO_CIDADE_H
