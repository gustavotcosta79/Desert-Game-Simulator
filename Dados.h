  //
// Created by Duarte Santos on 18/12/2024.
//

#ifndef TP_POO_DADOS_H
#define TP_POO_DADOS_H
#include "Caravana/Caravana.h"
#include "Caravana/CaravanaBarbara.h"
#include "Buffer/Mapa.h"
#include "Buffer/Buffer.h"
#include "Cidade.h"
#include "Barbaro.h"
#include "TempestadeAreia.h"
#include "Item/Item.h"
#include <string>



class Dados {
    Mapa mapa;
    Buffer buffer;
    std::map<std::string,Buffer> buffers;


// Entidades do jogo
    std::map<char, Cidade> cidades;
    std::map<int, Caravana*> caravanas;// fazer destrutor na class dados com o map<caravanas*>,item* ,etc
    std::vector<CaravanaBarbara> barbaros;

    TempestadeAreia tempestades;
    std::vector<Item*> itens;

    int instante;
    int moedas;
    int combatesVencidos;
public:
    Dados() ;
    Dados (const Dados& other);
    ~Dados();
    void carregarDeFicheiro(const std::string& caminhoFicheiro);
    void mostrarEstado();  // Mostra o estado do jogo
    void mostrarCidades() const;

    void inicializarCidades();

    int getInstanteAtual() const;


        //getters
    Mapa& getMapa();
    Buffer& getBuffer();

    // Funções para os comandos da fase 2
    void comprarCaravana(char cidade, const std::string& tipo);
    void listarPrecos();
    void mostrarCidade(char cidade);
    void mostrarCaravana(int id);
    void comprarMercadoria(int id, int mercadoria);
    void venderMercadoria(int id);
    void moverCaravana(int id, const std::string& direcao);
    void autoGestaoCaravana(int id);
    void pararCaravana(int id);
    void criarBarbaro(int linha, int coluna);
    void criarTempestadeAreia(int linha, int coluna, int raio);
    bool verificarCaravanaDentroTempestade(int linha_caravana, int coluna_caravana);
    void alterarMoedas(int valor);
    void comprarTripulantes(int id, int tripulantes);
    void salvarBuffer(const std::string& nome);
    void carregarBuffer(const std::string& nome);
    void listarBuffers() const;
    void removerBuffer(const std::string& nome);
    void terminarSimulacao();
    void avancarTurno();  // Avança o jogo para o próximo turno
    void criarCaravanaBarbara();
    void resolverCombate (Caravana* caravana1, Caravana* caravana2);
    void criarItemAleatorio();
    void verificarItensProximos(Caravana* caravana);


    Dados& operator=(const Dados& other);


    };


#endif //TP_POO_DADOS_H
