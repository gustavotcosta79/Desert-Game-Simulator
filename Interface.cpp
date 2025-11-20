//
// Created by Duarte Santos on 18/12/2024.
//

#include "Interface.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "Dados.h"

using namespace std;


Interface::Interface(Dados* dados)  {
    this->dados = dados;
    this->fase1 = true;
}

void Interface::executa() {
    string comando;
    bool executando = true;


    while (executando) {
        cout << "Digite um comando: ";
        getline(cin, comando);  // Lê a linha inteira (comando e argumentos)
        // Fase 1 - Comandos antes de iniciar o jogo
        if (comando.substr(0, 6) == "config") {
            if (fase1){
                string nomeFicheiro = comando.substr(7);
                configComando(nomeFicheiro);  // Carrega as configurações do mapa
                fase1 = false;
            }

        }
        else if (comando == "sair") {
            sair();  // Sai do programa
            executando = false;
        }
        else if (comando.substr(0, 4) == "exec") {
            string nomeFicheiro = comando.substr(5);
            execComandoFicheiro(nomeFicheiro);  // Executa comandos de um ficheiro
        }
        else if (comando.substr(0, 4) == "prox") {
            stringstream ss(comando);
            string cmd;
            int n = 1;  // Valor default para n
            ss >> cmd >> n;
            proxComando(n);  // Avança no tempo
        }
            // Fase 2 - Comandos após o início do jogo
        else {
            if (!fase1)
            processaComando(comando);  // Processa outros comandos da fase 2
            else{
                cout << "Esta na fase 1. Carregue ficheiro ou saia" << endl;
            }
        }
    }
}

void Interface::configComando(const string& nomeFicheiro) {
    dados->carregarDeFicheiro(nomeFicheiro);  // Carrega o mapa a partir do ficheiro
    cout << "Configuracao carregada do arquivo " << nomeFicheiro << endl;

}

void Interface::execComandoFicheiro(const string& nomeFicheiro) {
    ifstream arquivo(nomeFicheiro);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeFicheiro << endl;
        return;
    }

    string linha;
    while (getline(arquivo, linha)) {
        // Executa cada linha como um comando
        processaComando(linha);
    }

    cout << "Comandos do arquivo " << nomeFicheiro << " executados com sucesso." << endl;
}

void Interface::proxComando(int n) {
    // A lógica de avanço de instantes do jogo
    for (int i = 0; i < n; ++i) {
        dados->avancarTurno();  // Avança o jogo para o próximo turno, imprime e faz alteracoes necessarias como colocar os nMovimentos a 0
    }
}


void Interface::sair() {
    // Realiza qualquer limpeza necessária (exemplo: salvar estado, liberar recursos)
    std::cout << "Saindo do programa..." << std::endl;
    // Encerra o loop principal
    //this->executando = false;  // Define que o programa deve parar de rodar
}


void Interface::processaComando(const std::string& comando) {
    std::stringstream ss(comando);
    std::string cmd;
    ss >> cmd;

    if (cmd == "comprac") {
        char cidade;
        std::string tipo;
        ss >> cidade >> tipo;
        dados->comprarCaravana(cidade, tipo);  // Compra uma caravana
    }
    else if (cmd == "precos") {
        dados->listarPrecos();  // Lista os preços das mercadorias
    }
    else if (cmd == "cidade") {
        char cidade;
        ss >> cidade;
        dados->mostrarCidade(cidade);  // Mostra a cidade e suas caravanas
    }
    else if (cmd == "caravana") {
        int num;
        ss >> num;
        dados->mostrarCaravana(num);  // Mostra a caravana
    }
    else if (cmd == "compra") {
        int num, mercadoria;
        ss >> num >> mercadoria;
        dados->comprarMercadoria(num, mercadoria);  // Compra mercadorias para a caravana
    }
    else if (cmd == "vende") {
        int num;
        ss >> num ;
        dados->venderMercadoria(num);  // Compra mercadorias para a caravana
    }
    else if (cmd == "move") {
        int num;
        std::string direcao;
        ss >> num >> direcao;
        dados->moverCaravana(num, direcao);  // Move a caravana
    }
    else if (cmd == "auto") {
        int num;
        ss >> num;
        dados->autoGestaoCaravana(num);  // Coloca a caravana em auto-gestão
    }
    else if (cmd == "stop") {
        int num;
        ss >> num;
        dados->pararCaravana(num);  // Para a caravana
    }
    else if (cmd == "barbaro") {
        int linha, coluna;
        ss >> linha >> coluna;
        dados->criarBarbaro(linha, coluna);  // Cria uma caravana bárbara
    }
    else if (cmd == "areia") {
        int linha, coluna, raio;
        ss >> linha >> coluna >> raio;
        dados->criarTempestadeAreia(linha, coluna, raio);  // Cria uma tempestade de areia
    }
    else if (cmd == "moedas") {
        int moedas;
        ss >> moedas;
        dados->alterarMoedas(moedas);  // Acrescenta moedas
    }
    else if (cmd == "tripul") {
        int num, tripulantes;
        std::string tipo;
        ss >> num >> tripulantes;
        dados->comprarTripulantes(num, tripulantes);  // Compra tripulantes para a caravana
    }
    else if (cmd == "saves") {
        std::string nome;
        ss >> nome;
        dados->salvarBuffer(nome);  // Salva o estado visual do jogo
    }
    else if (cmd == "loads") {
        std::string nome;
        ss >> nome;
        dados->carregarBuffer(nome);  // Carrega um estado visual salvo anteriormente
    }
    else if (cmd == "lists") {
        dados->listarBuffers();  // Lista todos os buffers salvos
    }
    else if (cmd == "dels") {
        std::string nome;
        ss >> nome;
        dados->removerBuffer(nome);  // Apaga um buffer salvo
    }
    else if (cmd == "terminar") {
        fase1 = true;
        dados->terminarSimulacao();  // Termina a simulação e retorna à fase 1
    }
    else {
        std::cout << "Comando desconhecido: " << comando << std::endl;
    }
}


