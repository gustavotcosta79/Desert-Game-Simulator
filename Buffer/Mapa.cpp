#include "Mapa.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

Mapa::Mapa(const string& caminhoFicheiro){

    carregarDeFicheiro(caminhoFicheiro);


}

Mapa::Mapa(){}


// Método para carregar mapa e configurações de um ficheiro de texto
void Mapa::carregarDeFicheiro(const string& caminhoFicheiro) {
    ifstream ficheiro(caminhoFicheiro);

    if (!ficheiro.is_open()) {
        cerr << "Erro ao abrir o ficheiro!" << endl;
        return;
    }

    string linha;
    int linhas,colunas;
    // Lê a linha com "linhas <valor>" e extrai o valor
    getline(ficheiro, linha);
    istringstream(linha) >> linha >> linhas;  // "linhas" é o valor que queremos
    //cout << buf.getLinhas() << endl;

    // Lê a linha com "colunas <valor>" e extrai o valor
    getline(ficheiro, linha);
    istringstream(linha) >> linha >> colunas;

    buf = new Buffer(linhas, colunas);

    // Ler as linhas do mapa e armazenar na matriz do Buffer
    for (int i = 0; i < buf->getLinhas(); ++i) {
        if (getline(ficheiro, linha)) {
            for (int j = 0; j < linha.length() && j < buf->getColunas(); ++j) {
                buf->at(i, j) = linha[j];
            }
        }
    }

    // Ler as configurações restantes
    while (getline(ficheiro, linha)) {
        std::istringstream iss(linha);
        std::string chave;
        int valor;

        if (iss >> chave >> valor) {
            configuracoes[chave] = valor;
        }
    }

    ficheiro.close();
}

void Mapa::mostrarConfiguracoes() const {
    cout << "Linhas: " << buf->getLinhas() << endl;
    cout << "Colunas: " << buf->getColunas() << endl;

    if (configuracoes.empty()) {
        cout << "Nao ha configuracoes carregadas." << endl;
        return;
    }
        buf->imprimir();
        cout << endl << "Configuracoes: " << endl;
        // itera sobre o mapa de configurações e imprime chave-valor
        for (const auto &[chave, valor]: configuracoes) {
            cout << chave << ": " << valor << endl;
        }
}

 Buffer& Mapa:: getBuffer()  {
    return *buf;
}


// Alterar uma configuração do mapa
void Mapa::alterarConfiguracao(const std::string& chave, int novoValor) {
    configuracoes[chave] = novoValor;
    std::cout << "Configuracao \"" << chave << "\" atualizada para: " << novoValor << std::endl;
}
// Inserir um elemento no mapa e atualizar o buffer
void Mapa::inserirElemento(int linha, int coluna, char elemento) {
    if (linha >= buf->getLinhas() || coluna >= buf->getColunas()) {
        std::cerr << "Posicao fora dos limites do mapa!" << std::endl;
        return;
    }

    buf->at(linha, coluna) = elemento; // Atualiza o buffer diretamente
    std::cout << "Elemento '" << elemento << "' inserido na posicao (" << linha << ", " << coluna << ")." << std::endl;
}

int Mapa::getConfiguracao(const std::string& chave) const {
    auto it = configuracoes.find(chave);
    if (it != configuracoes.end()) {
        return it->second; // Retorna o valor da configuração, se existir
    } else {
        throw std::runtime_error("Configuracao nao encontrada: " + chave);
    }
}

bool Mapa::isAdjacente (int linha1, int coluna1, int linha2, int coluna2) const{
    int calcLinha = abs (linha1 - linha2) ;
    int calcColuna =  abs (coluna1 - coluna2);

    return (calcLinha <= 1 && calcColuna <= 1) && !(calcLinha == 0 && calcColuna == 0);

}
