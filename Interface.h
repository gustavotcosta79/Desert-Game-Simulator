//
// Created by Duarte Santos on 18/12/2024.
//

#ifndef TP_POO_INTERFACE_H
#define TP_POO_INTERFACE_H
#include "Dados.h"
#include "Buffer/Mapa.h"
#include "string"

class Interface {
private:
    Dados *dados; // Ponteiro para a classe Dados

public:
    Interface(Dados *d);
    bool fase1;

    void executa();

private:
    void configComando(const std::string& nomeFicheiro);
    void execComandoFicheiro(const std::string& nomeFicheiro);
    void proxComando(int n);
    void processaComando(const std::string& comando);



    void sair();


};


#endif //TP_POO_INTERFACE_H
