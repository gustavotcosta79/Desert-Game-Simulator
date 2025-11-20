//
// Created by Duarte Santos on 19/11/2024.
//

#ifndef TP_POO_MAPA_H
#define TP_POO_MAPA_H


#include <map>
#include <string>
#include "Buffer.h"


class Mapa {
private:
    std::map<std::string, int> configuracoes;  // configuracoes do mapa (nome -> valor)
    Buffer *buf;
public:
    Mapa(const std::string& caminhoFicheiro);
    Mapa();

    // Carregar mapa e configurações de um ficheiro de texto
    void carregarDeFicheiro(const std::string& caminhoFicheiro);
    void mostrarConfiguracoes() const;
     Buffer& getBuffer();
    int getConfiguracao(const std::string& chave) const;
    bool isAdjacente (int linha1, int coluna1, int linha2, int coluna2) const;


    void inserirElemento(int linha, int coluna, char elemento);
    void alterarConfiguracao(const std::string& chave, int novoValor);


};

#endif //TP_POO_MAPA_H
