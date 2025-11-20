    //
    // Created by Duarte Santos on 18/12/2024.
    //

#include <iostream>
#include <cmath>
#include "Dados.h"
#include "Caravana/CaravanaMilitar.h"
#include "Caravana/CaravanaComercio.h"
#include "Caravana/CaravanaSecreta.h"
#include "TempestadeAreia.h"
#include "Item/CaixaPandora.h"
#include "Item/ArcaTesouro.h"
#include "Item/Jaula.h"
#include "Item/Mina.h"
#include "Item/Surpresa.h"
#include <ctime>
#include <cstdlib>
using namespace std;
// Chamar isso uma vez no início do programa:



    Dados::Dados() : mapa(), buffer(), instante(0){}

    Dados::Dados (const Dados& other)
    : mapa(other.mapa), buffer (other.buffer), instante (other.instante), moedas (other.moedas), cidades (other.cidades), caravanas (),
    itens(),barbaros(other.barbaros), tempestades(other.tempestades)
    {
        for (const auto& par : other.caravanas) {
            Caravana* caravanaCopia = par.second->clone();  // Assumindo que Caravana tem um método clone
            caravanas[par.first] = caravanaCopia;
        }

        // Para os itens, fazemos uma cópia profunda também
        for (auto item : other.itens) {
            itens.push_back(item->clone());  // Copia cada item
        }
    }


    // Método para carregar os dados a partir de um ficheiro
    void Dados::carregarDeFicheiro(const std::string& caminhoFicheiro) {
       mapa.carregarDeFicheiro(caminhoFicheiro);

       inicializarCidades(); // inicializa as cidades a partir do ficheiro
       buffer.esvaziar() ;
       caravanas.clear();
       barbaros.clear();
       itens.clear();
       buffers.clear();
       instante = 0;
       combatesVencidos = 0;
       moedas = mapa.getConfiguracao("moedas");//inicializar moedas?

       buffer = mapa.getBuffer();

       mapa.mostrarConfiguracoes();
    }

    void Dados::inicializarCidades() {
        // Limpar qualquer dado existente (caso o método seja chamado mais de uma vez)
        cidades.clear();

        // Percorrer o buffer
        for (int linha = 0; linha < mapa.getBuffer().getLinhas(); ++linha) {
            for (int coluna = 0; coluna < mapa.getBuffer().getColunas(); ++coluna) {
                char simbolo = mapa.getBuffer().at(linha, coluna); // Obter o caractere do buffer

                if (std::islower(simbolo)) {
                    cidades.emplace(simbolo, Cidade(simbolo, linha, coluna));

                }
            }
        }
    }





    void Dados::mostrarCidades() const {
        for (const auto& [simbolo, cidade] : cidades) {
            cout << "Cidade: " << cidade.getNome()
                      << " | Posição: (" << cidade.getLinha() << ", " << cidade.getColuna() << ")\n";
        }
    }

    // Getters
    Mapa& Dados::getMapa() {
        return mapa;
    }

    Buffer& Dados::getBuffer() {
        return buffer;
    }


    void Dados::mostrarEstado() {
        mapa.mostrarConfiguracoes();
    }



    int Dados::getInstanteAtual() const {
        return instante;
    }

    void Dados::comprarCaravana(char cidade, const std::string& tipo) {
        if (moedas < mapa.getConfiguracao("preco_caravana")){
            std::cerr << "Moedas insuficientes! " << endl;
            return;
        }

        auto it = cidades.find(cidade);
        if (it == cidades.end()) {
            std::cerr << "Cidade nao encontrada: " << cidade << endl;
            return;
        }

        Cidade& cidadeRef = it->second;

        // Verifica se o tipo de caravana está disponível
        if (tipo == "M") {
            if (cidadeRef.getCMilitar()) {
                std::cerr << "Caravana militar ja foi comprada nesta cidade!" << std::endl;
                return;
            }
            // Cria uma caravana militar
            Caravana* novaCaravana = new CaravanaMilitar(caravanas.size(),cidadeRef.getLinha(),cidadeRef.getColuna());
            caravanas[caravanas.size()] = novaCaravana; // Adiciona ao mapa de caravanas
            moedas -= mapa.getConfiguracao("preco_caravana");
            cout << "Moedas Restantes: " << moedas << " moedas" << endl;
            cidadeRef.setCMilitar(true); // Marca como comprada
        }
        else if (tipo == "C") {
            if (cidadeRef.getCComercio()) {
                std::cerr << "Caravana de comercio ja foi comprada nesta cidade!" << std::endl;
                return;
            }
            // Cria uma caravana de comércio
            Caravana* novaCaravana = new CaravanaComercio(caravanas.size(),cidadeRef.getLinha(),cidadeRef.getColuna());
            caravanas[caravanas.size()] = novaCaravana; // Adiciona ao mapa de caravanas
            moedas -= mapa.getConfiguracao("preco_caravana");
            cout << "Moedas Restantes: " << moedas << " moedas" << endl;
            cidadeRef.setCComercio(true); // Marca como comprada
        }
        else if (tipo == "S") {
            if (cidadeRef.getCSecreta()) {
                std::cerr << "Caravana secreta ja foi comprada nesta cidade!" << std::endl;
                return;
            }
            // Cria uma caravana secreta
            Caravana* novaCaravana = new CaravanaSecreta(caravanas.size(),cidadeRef.getLinha(),cidadeRef.getColuna());
            caravanas[caravanas.size()] = novaCaravana; // Adiciona ao mapa de caravanas
            moedas -= mapa.getConfiguracao("preco_caravana");
            cout << "Moedas Restantes: " << moedas << " moedas" << endl;
            cidadeRef.setCSecreta(true); // Marca como comprada
        }
        else {
            std::cerr << "Tipo de caravana invalido: " << tipo << std::endl;
            return;
        }

        std::cout << "Caravana do tipo " << tipo << " comprada em cidade " << cidade << "." << std::endl;
    }


    void Dados::listarPrecos() {
        // Implementação vazia
        cout << "Preco de compra: " << mapa.getConfiguracao("preco_compra_mercadoria")<<" moedas"<< endl;
        cout << "Preco de venda: "<<mapa.getConfiguracao("preco_venda_mercadoria") << " moedas" << endl ;
    }

    void Dados::mostrarCidade(char cidade) {///percorrer o map de cidades e comparar  as linhas e colunas de cada uma das caravanas do map de caravanas e se for igual, quer dizer que a caravana esta na cidade.
        // Encontra a cidade no mapa
        auto itCidade = cidades.find(cidade);
        if (itCidade == cidades.end()) {
            std::cerr << "Cidade nao encontrada: " << cidade << std::endl;
            return;
        }

        // Obtém a referência da cidade
        const Cidade& cidadeRef = itCidade->second;

        std::cout << "Cidade: " << cidadeRef.getNome()
                  << " (Linha: " << cidadeRef.getLinha()
                  << ", Coluna: " << cidadeRef.getColuna() << ")" << std::endl;

        bool encontrouCaravanas = false;

        // Percorre o mapa de caravanas
        for (const auto& [id, caravana] : caravanas) {
            if (caravana->getLinha() == cidadeRef.getLinha() &&
                caravana->getColuna() == cidadeRef.getColuna()) {
                std::cout << "  Caravana ID: " << id
                          << " Tipo: " << caravana->getTipo() << std::endl;
                encontrouCaravanas = true;
            }
        }

        if (!encontrouCaravanas) {
            std::cout << "  Nenhuma caravana encontrada nesta cidade." << std::endl;
        }
    }

    void Dados::mostrarCaravana(int id) {

        auto it = caravanas.find(id);
        if (it == caravanas.end()) {
            std::cerr << "Caravana nao encontrada com ID: " << id << std::endl;
            return;
        }

        Caravana *caravana = it->second;

        if (caravana->getDestruida()){
            std::cout << "Detalhes da Caravana ID: " << id << "\n";
            cout << "Caravana destruida."<< endl;
            return;
        }

        // Exibir os detalhes da caravana
        std::cout << "Detalhes da Caravana ID: " << id << endl;
        std::cout << "Tipo: " << caravana->getTipo() << endl;
        std::cout << "Posicao: (" << caravana->getLinha() << ", " << caravana->getColuna() << ")"<< endl;
        std::cout << "Tripulantes (atual/total): " << caravana->getTripulacao()<< "/" <<caravana->getMaxTripulantes() << endl;
        std::cout << "Carga (atual/total):  " << caravana->getCargaAtual()<<"/" << caravana->getCargaTotal()<< " toneladas." << endl;
        std::cout << "Agua (atual/total): " << caravana->getAguaAtual()<< "/"<<caravana->getAguaTotal()<< " litros."<< endl;
        if(caravana->getGato()){
            cout<< "Gato: miau" << endl;
        }
    }



    void Dados::comprarMercadoria(int id, int mercadoria) {
        // Verifica se a caravana existe no mapa de caravanas
        auto itCaravana = caravanas.find(id);
        if (itCaravana == caravanas.end()) {
            std::cerr << "Caravana com ID " << id << " nao encontrada!" << std::endl;
            return;
        }

        Caravana* caravana = itCaravana->second;

        // Verifica se a caravana está destruída
        if (caravana->getDestruida()) {
            std::cerr << "A caravana esta destruida e nao pode comprar mercadorias." << std::endl;
            return;
        }

        // Verifica se a caravana está em uma cidade
        bool caravanaEmCidade = false;
        for (const auto& [nomeCidade, cidade] : cidades) {
            if (caravana->getLinha() == cidade.getLinha() && caravana->getColuna() == cidade.getColuna()) {
                caravanaEmCidade = true;
                break;
            }
        }

        if (!caravanaEmCidade) {
            std::cerr << "A caravana nao esta em uma cidade e nao pode comprar mercadorias." << std::endl;
            return;
        }

        // Verifica se há espaço suficiente para as mercadorias
        int cargaDisponivel = caravana->getCargaTotal() - caravana->getCargaAtual();
        if (mercadoria > cargaDisponivel) {
            std::cerr << "A caravana nao tem espaço suficiente para " << mercadoria << " toneladas de mercadorias." << std::endl;
            return;
        }

        // Compra as mercadorias e atualiza a carga da caravana
        caravana->setCarga(mercadoria);
        std::cout << "Foram compradas " << mercadoria << " toneladas de mercadorias para a caravana com ID "
                  << id << "." << std::endl;
    }

    void Dados::venderMercadoria(int id) {
        auto itCaravana = caravanas.find(id);
        if (itCaravana == caravanas.end()) {
            std::cerr << "Caravana com ID " << id << " nao encontrada!" << std::endl;
            return;
        }
        Caravana* caravana = itCaravana->second;

        // Verifica se a caravana está destruída
        if (caravana->getDestruida()) {
            std::cerr << "A caravana esta destruída e nao pode vender mercadorias." << std::endl;
            return;
        }

        bool caravanaEmCidade = false;
        for (const auto& [nomeCidade, cidade] : cidades) {
            if (caravana->getLinha() == cidade.getLinha() && caravana->getColuna() == cidade.getColuna()) {
                caravanaEmCidade = true;
                break;
            }
        }

        if (!caravanaEmCidade) {
            std::cerr << "A caravana nao esta em uma cidade e nao pode vender mercadorias." << std::endl;
            return;
        }

        int cargaAtual = caravana->getCargaAtual();
        if (cargaAtual == 0) {
            std::cerr << "A caravana não possui mercadorias para vender." << std::endl;
            return;
        }

        // Obtém o preço de venda da mercadoria a partir da configuração do mapa
        int precoVendaMercadoria = mapa.getConfiguracao("preco_venda_mercadoria");

        // Calcula o valor total obtido pela venda
        int valorVenda = cargaAtual * precoVendaMercadoria;

        moedas += valorVenda;

        caravana->removeCarga(caravana->getCargaAtual());

        cout << "Mercadorias vendidas com sucesso! Saldo atual: "<< moedas<< " moedas, Carga Atual: "<< caravana->getCargaAtual()<< " toneladas"<<endl;
    }

    void Dados::moverCaravana(int id, const std::string& direcao) {
        /// Verifica se a caravana existe no mapa de caravanas
        auto itCaravana = caravanas.find(id);
        if (itCaravana == caravanas.end()) {
            std::cerr << "Caravana com ID " << id << " nao encontrada!" << std::endl;
            return;
        }
        Caravana* caravana = itCaravana->second;

        /// Verifica se a caravana está destruída
        if (caravana->getDestruida()) {
            std::cerr << "A caravana esta destruida e nao pode ser movida." << std::endl;
            return;
        }
        ///verificar se tem movimentos restantes
        if (caravana->getNMovimentos() == caravana->getMaxMovimentos()){
            std::cerr << "A caravana ja realizou o numero maximo de movimentos permitidos neste turno." << std::endl;
            return;
        }
        ///verifica se a caravana esta em movimento auto ?

        try {
            // Verifica se a caravana está numa cidade
            bool estaEmCidade = false;
            char simboloCidade = '\0';

            // Guarda a linha e a coluna antes de mover
            int linhaAnterior = caravana->getLinha();
            int colunaAnterior = caravana->getColuna();

            // Verifica se a posição atual da caravana corresponde a uma cidade
            for (const auto& cidade : cidades) {
                if (cidade.second.getLinha() == linhaAnterior && cidade.second.getColuna() == colunaAnterior) {
                    estaEmCidade = true;
                    simboloCidade = cidade.first; // Armazena o símbolo da cidade
                    break;
                }
            }

            // Move a caravana em uma única posição na direção fornecida
            int sucesso = caravana->moverCaravanaUmaPosicao(mapa, direcao);
            if (sucesso){

                std::cout << "Caravana com ID " << id << " movida para a direcao: " << direcao << std::endl;
                caravana->setNMovimentos(1); // Incrementa o número de movimentos
                if (caravana->getGato()){
                    cout << "MIAUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU!!!"<< endl;
                    moedas ++;
                }

            }


            // Atualiza o mapa com base na posição anterior
            if (estaEmCidade) {
                // Se estava numa cidade, mantém a letra da cidade na posição anterior
                mapa.getBuffer().at(linhaAnterior, colunaAnterior) = simboloCidade;
            } else {
                // Se estava no deserto (.), coloca um "." na posição anterior
                mapa.getBuffer().at(linhaAnterior, colunaAnterior) = '.';
            }

        }

        catch (const char* erro) {
            std::cerr << "Erro ao mover a caravana: " << erro << std::endl;
        }

    }

    void Dados::autoGestaoCaravana(int id) {
        auto it = caravanas.find(id);  // Localizar a caravana pelo ID
        if (it == caravanas.end()) {
            std::cout << "Erro: Caravana " << id << " nao encontrada!" << std::endl;
            return;
        }

        Caravana* caravana = it->second;
        // Verifica se já está em modo automático
        if (caravana->isAutoGestao()) {
            std::cerr << "Caravana com ID " << id << " ja esta em modo automatico!" << std::endl;
            return;
        }

        // Ativa o modo automático
        caravana->setAutoGestao(true);

        caravana->moverAutonomo(mapa);
    }

    void Dados::pararCaravana(int id) {
        auto it = caravanas.find(id);  // Localizar a caravana pelo ID
        if (it == caravanas.end()) {
            std::cout << "Erro: Caravana " << id << " nao encontrada!" << endl;
            return;
        }
        Caravana* caravana = it->second;  // Obter o ponteiro para a caravana
        if (!caravana->isAutoGestao()) {
            std::cout << "Caravana " << id << " ja nao esta em modo automatico." << endl;
            return;
        }
        caravana->setAutoGestao(false);
        std::cout << "Modo automatico desativado para a caravana " << id << "." << endl;
    }

    void Dados::criarBarbaro(int linha, int coluna) {
        char destino = mapa.getBuffer().at(linha, coluna);

        // Garantir que a posição é deserto
        if (destino != '.' && (destino < 'a' || destino > 'z')) {
            cout << "A celula (" << linha << ", " << coluna
                 << ") nao e valida para movimento." << endl;
            return; // Interrompe
        }

        if (destino >= 'a' && destino <= 'z') {
            mapa.getBuffer().at(linha, coluna) = destino;
        }else{
                mapa.getBuffer().at(linha, coluna) = '!';
            }
            // Criar a caravana bárbara e adicioná-la ao vetor
        CaravanaBarbara novaBarbara(linha, coluna,mapa);
        barbaros.push_back(novaBarbara);

        cout << "Nova caravana barbara criada na posicao (" << linha << ", " << coluna << ")." << endl;
    }

    void Dados::criarTempestadeAreia(int linha, int coluna, int raio) {
        if (tempestades.isAtiva()){
            cout << "Ja existe uma tempestade ativa." << endl;
            return;
        }
        TempestadeAreia tempestade (linha,coluna,raio);
        tempestades = tempestade;

        cout << "Tempestade criada na posicao (" << linha << ", " << coluna
                  << ") com raio " << raio << "." << endl;
    }

    bool Dados:: verificarCaravanaDentroTempestade(int linha_caravana, int coluna_caravana) {
        return tempestades.isAtiva() && tempestades.isDentro(linha_caravana, coluna_caravana);
    }

    void Dados::alterarMoedas(int valor) {
        moedas = moedas + valor;
        if (moedas < 0){
            moedas = 0;
            cout << "O valor das moedas nao pode ser negativo. O saldo foi ajustado para 0."<< endl;
        }
        cout << "O seu saldo foi atualizado. Saldo atual: " << moedas << " moedas."<<endl;
    }

    void Dados::comprarTripulantes(int id, int tripulantes) {
        auto itCaravana = caravanas.find(id);
        if (itCaravana == caravanas.end()) {
            std::cerr << "Caravana com ID " << id << " nao encontrada!" << std::endl;
            return;
        }
        Caravana* caravana = itCaravana->second;

        // Verifica se a caravana está destruída
        if (caravana->getDestruida()) {
            std::cerr << "A caravana esta destruída e nao pode vender mercadorias." << std::endl;
            return;
        }

        bool caravanaEmCidade = false;
        for (const auto& [nomeCidade, cidade] : cidades) {
            if (caravana->getLinha() == cidade.getLinha() && caravana->getColuna() == cidade.getColuna()) {
                caravanaEmCidade = true;
                break;
            }
        }

        if (!caravanaEmCidade) {
            std::cerr << "A caravana nao esta em uma cidade e nao pode vender mercadorias." << std::endl;
            return;
        }
        if (caravana->getTripulacao() + tripulantes > caravana->getMaxTripulantes()){
            cerr << "A caravana ja tem a tripulacao maxima. Tripulantes: "<< caravana->getTripulacao()<<endl;
            return;
        }
        int custoPorTripulante = 10; // Defina o custo por tripulante
        int custoTotal = tripulantes * custoPorTripulante;
        if (moedas < custoTotal) {
            std::cerr << "Erro: Moedas insuficientes. São necessárias " << custoTotal << " moedas." << std::endl;
            return;
        }
        caravana->ganhaTripulantes(tripulantes);
        moedas = moedas - custoTotal;
        cout << "Sucesso: Foram adicionados " << tripulantes
             << " tripulantes  caravana " << id << "." << endl;
    }

    void Dados::salvarBuffer(const std::string& nome) {
        cout << "Estado atual do Buffer antes de salvar:" << endl;
        mapa.getBuffer().imprimir(); // Verificar o estado do buffer
        Buffer novoBuffer = mapa.getBuffer();

        buffers[nome] = novoBuffer; // Adiciona ao mapa 'buffers' com a chave 'nome'
        cout << "Buffer salvo com o nome: " << nome << endl;
    }

    void Dados::carregarBuffer(const std::string& nome) {
        auto it = buffers.find(nome); // Procura pelo buffer no mapa usando o nome fornecido

        if (it != buffers.end()) {
            // Se o buffer for encontrado, imprime o conteúdo
           cout << "Conteudo do buffer \"" << nome << "\":" << endl;
            it->second.imprimir(); // Chama o método imprimir() do buffer correspondente
        } else {
            // Se o buffer não existir, informa que não foi encontrado
            cout << "Erro: Nenhum buffer encontrado com o nome \"" << nome << "\"." << endl;
        }
    }

    void Dados::listarBuffers() const {
        if (buffers.empty()){
            cout << "Nao existe copia de nenhum buffer!" << endl;
        }
        else {
            cout << "IDs das copias existentes: " << endl;
            for (const auto &it: buffers) {
                cout << "- " << it.first << endl;
            }
        }
    }

    void Dados::removerBuffer(const std::string& nome) {
        auto it = buffers.find(nome);
        if (it != buffers.end()) {
            buffers.erase(it);
           cout << "Copia do buffer com o nome '" << nome << "' foi apagada." << endl;
        } else {
            cout << "Erro: Nao existe nenhuma copia do buffer com o nome '" << nome << "'." << endl;
        }
    }

    void Dados::terminarSimulacao() {
        cout << "A SIMULACAO FOI TERMINADA!!" << endl;
        cout << "INSTANTES DECORRIDOS: " << instante << endl;
        cout << "COMBATES VENCIDOS: " << combatesVencidos << endl;
        cout << "MOEDAS RESTANTES: " << moedas << endl;
    }
    //}

    void Dados::avancarTurno() {
        instante++;
// Imprime o instante atual com formatação estilizada
        cout << "===============================" << endl;
        cout << "          INSTANTE " << instante << endl;
        cout << "===============================" << endl;
        cout << "      MENSAGENS DE DEBUG: " << endl;


        ///de 40 em 40 instanates -> criarCaravanaBarbara
        if (instante % mapa.getConfiguracao("instantes_entre_novos_barbaros") == 0) {
            criarCaravanaBarbara();  // Chama a função para criar uma nova Caravana Bárbara
        }


        // A cada "instantes_entre_novos_itens" -> criar itens no mapa
        if (instante % mapa.getConfiguracao("instantes_entre_novos_itens") == 0) {
            if (itens.size() < mapa.getConfiguracao("max_itens")) {
                criarItemAleatorio();  // Gera um novo item em uma posição aleatória válida
            }
        }

        // Atualizar e verificar duração dos itens no mapa
        for (auto it = itens.begin(); it != itens.end();) {
            (*it)->decrementarDuracao();  // Reduz a duração do item
            if ((*it)->getDuracao() <= 0) {
                cout << "Item (" << (*it)->getTipo() << ") desapareceu." << endl;
                mapa.getBuffer().at((*it)->getLinha(), (*it)->getColuna()) = '.'; // Limpa o item do mapa
                delete *it; // Libera a memória
                it = itens.erase(it); // Remove o ponteiro do vetor
            } else {
                ++it;
            }
        }

        // Verificar se alguma caravana apanhou um item
        for (auto& par : caravanas) {
            Caravana* caravana = par.second;
            verificarItensProximos(caravana);
        }

        // Definir nMovimentos como 0 para todas as caravamnonas
        for (auto& par : caravanas) {
            Caravana* caravana = par.second;
            caravana->setNMOVIMENTOS0(); // Reseta os movimentos
        }

        // Atualizar caravanas em modo automático
        for (auto& par : caravanas) {
            Caravana* caravana = par.second;
            if (caravana->isAutoGestao() == true) {
                caravana->moverAutonomo(mapa);  // Executa o comportamento automático
            }

            caravana->consumirAgua();
        }

        if (tempestades.isAtiva()){
            for (auto& par : caravanas){
                Caravana* caravana = par.second;

                if (verificarCaravanaDentroTempestade(caravana->getLinha(),caravana->getColuna())){
                    cout << "Caravana " << caravana->getId() << " foi afetada pela tempestade!" << endl;
                    caravana->isTempestade();
                }
            }
            cout << "A tempestade terminou." <<endl;
            tempestades.setInativa(); // fim da tempestade
        }

        /// Convertendo o mapa para um vetor, para passar como parametro
        std::vector<Caravana*> caravanasV;
        caravanasV.reserve(caravanas.size()); // Pré-aloca memória para o tamanho do mapa
        for (const auto& c : caravanas) {
            caravanasV.push_back(c.second); // Adicionando o valor (Caravana*) ao vetor
        }

        /// Convertendo o mapa para um vetor, para passar como parametro
        std::vector<Cidade> cidadesV;
        caravanasV.reserve(cidades.size()); // Pré-aloca memória para o tamanho do mapa
        for (const auto& c : caravanas) {
            caravanasV.push_back(c.second); // Adicionando o valor (Caravana*) ao vetor
        }



        for (auto it = barbaros.begin(); it != barbaros.end(); ) {
            it->moverAutonomo(mapa, caravanasV, cidadesV);
            it->setIncrementaTurno();

            if (it->getDesaparecida()) {
                cout << "Caravana barbara desapareceu por tedio!" << endl;

                // Verificar se a posição da caravana é uma cidade
                bool estaEmCidade = false;
                char simboloCidade = '.'; // Valor padrão caso não seja uma cidade
                for (const auto& cidade : cidadesV) {
                    if (cidade.getLinha() == it->getLinha() && cidade.getColuna() == it->getColuna()) {
                        estaEmCidade = true;
                        simboloCidade = cidade.getNome(); // Obter o símbolo da cidade
                        break;
                    }
                }

                // Atualizar o mapa com o símbolo apropriado
                if (estaEmCidade) {
                    mapa.getBuffer().at(it->getLinha(), it->getColuna()) = simboloCidade;
                } else {
                    mapa.getBuffer().at(it->getLinha(), it->getColuna()) = '.';
                }

                // Remover a caravana do vetor
                it = barbaros.erase(it);  // `erase` retorna o próximo iterador
            } else {
                ++it;  // Se não foi removido, apenas avança o iterador
            }
        }

        /*************************************/
        // LÓGICA PARA COMBATES ENTRE CARAVANAS E BÁRBAROS
        for (auto& par : caravanas) { // PERCORRE TODAS AS CARAVANAS
            Caravana* caravana = par.second;

            for (auto& barbaro : barbaros) { // PERCORRE TODOS OS BÁRBAROS
                if (mapa.isAdjacente(caravana->getLinha(), caravana->getColuna(),
                                     barbaro.getLinha(), barbaro.getColuna())) { // VERIFICA ADJACÊNCIA
                    resolverCombate(caravana, &barbaro); // CHAMA FUNÇÃO DE COMBATE
                }
            }
        }
/*****************************************/
        cout << "===============================" << endl << endl;

        mapa.getBuffer().imprimir();

        cout << endl << "Moedas disponiveis: " << moedas << endl;


    }

    // Método para criar uma nova caravana bárbara
    void Dados::criarCaravanaBarbara() {
        // Escolher uma posição aleatória no deserto
        int linha = rand() % mapa.getBuffer().getLinhas();
        int coluna = rand() % mapa.getBuffer().getColunas();

        // Garantir que a posição é deserto
        while (mapa.getBuffer().at(linha, coluna) != '.') {
            linha = rand() % mapa.getBuffer().getLinhas();
            coluna = rand() % mapa.getBuffer().getColunas();
        }

        // Criar a caravana bárbara e adicioná-la ao vetor
        CaravanaBarbara novaBarbara(linha, coluna,mapa);
        barbaros.push_back(novaBarbara);

        cout << "Nova caravana bárbara criada na posição (" << linha << ", " << coluna << ")." << endl;
    }


    // Destrutor
    Dados::~Dados() {
        for (auto& par : caravanas) {
            delete par.second;  // Deleta a caravana apontada
        }

        for (auto item : itens) {
            delete item;  // Deleta cada item
        }

    }

    Dados& Dados::operator=(const Dados& other){
    if (this != &other) {  // Evita auto-atribuição
        // Primeiramente, libera qualquer recurso que a instância já tenha
        // No caso, isso pode incluir destruir as caravanas, itens e outros membros
        for (auto& par : caravanas) {
        delete par.second;  // Libera memória das caravanas
        }
        for (auto item : itens) {
        delete item;  // Libera memória dos itens
        }

        // Copia os dados do objeto "other"
        mapa = other.mapa;  // Copia o mapa
        buffer = other.buffer;  // Copia o buffer
        instante = other.instante;
        moedas = other.moedas;
        cidades = other.cidades;
        barbaros = other.barbaros;
        tempestades = other.tempestades;


        // Clonagem das caravanas (profunda)
        for (const auto& par : other.caravanas) {
        Caravana* caravanaCopia = par.second->clone();  // Clona a caravana
        caravanas[par.first] = caravanaCopia;
        }

        // Clonagem dos itens (profunda)
        for (auto item : other.itens) {
        itens.push_back(item->clone());  // Clona cada item
        }
    }
    return *this;  // Retorna o objeto atual para permitir a atribuição encadeada
    }


    void Dados:: resolverCombate(Caravana* caravana1, Caravana* caravana2) {
        if (caravana1->getDestruida() || caravana2->getDestruida()) {
            cout << "Uma das caravanas ja foi destruida, por isso nao ha combate!" << endl;
            return;
        }

        // Sorteio de valores
        int sorteio1 = rand() % (caravana1->getTripulacao() );
        int sorteio2 = rand() % (caravana2->getTripulacao() );

        cout << "Combate entre Caravana " << caravana1->getId()
             << " e Caravana " << caravana2->getId() << endl;
        cout << "Sorteio: " << sorteio1 << " vs " << sorteio2 << endl;

        // Determina a caravana vencedora e as consequências
        if (sorteio1 > sorteio2) {
            cout << "Caravana " << caravana1->getId() << " venceu o combate!" << endl;

            int perda = floor(caravana1->getTripulacao() * 0.2); // Perda arredondada para baixo
            caravana1->perderTripulantes(perda); // Perda da vencedora
            int perdaDerrotado = caravana2->perderTripulantes(perda * 2); // Perda do derrotado

            cout << "Caravana " << caravana1->getId() << " perdeu " << perda
                 << " tripulantes. Restantes: " << caravana1->getTripulacao() << endl;

            cout << "Caravana " << caravana2->getId() << " perdeu " << perdaDerrotado
                 << " tripulantes. Restantes: " << caravana2->getTripulacao() << endl;

            if (caravana2->getTripulacao() <= 0) {
                caravana2->setDestruida();
                caravana1->adicionaCarga(caravana2->getCargaAtual());
                caravana2->setCarga(0);

                cout << "Caravana " << caravana2->getId()
                     << " foi destruida no combate!" << endl;
                cout << "A carga da caravana destruida foi transferida para a Caravana "
                     << caravana1->getId() << "." << endl;
                combatesVencidos++;

            } else {
                cout << "Caravana " << caravana2->getId()
                     << " sobreviveu ao combate, mas ficou com poucos tripulantes." << endl;
            }

        } else if (sorteio2 > sorteio1) {
            cout << "Caravana " << caravana2->getId() << " venceu o combate!" <<endl;

            int perda = floor(caravana2->getTripulacao() * 0.2); // Perda arredondada para baixo
            caravana2->perderTripulantes(perda); // Perda da vencedora
            int perdaDerrotado = caravana1->perderTripulantes(perda * 2); // Perda do derrotado

            cout << "Caravana " << caravana2->getId() << " perdeu " << perda
                 << " tripulantes. Restantes: " << caravana2->getTripulacao() << endl;

            cout << "Caravana " << caravana1->getId() << " perdeu " << perdaDerrotado
                 << " tripulantes. Restantes: " << caravana1->getTripulacao() << endl;

            if (caravana1->getTripulacao() <= 0) {
                caravana1->setDestruida();
                caravana2->adicionaCarga(caravana1->getCargaAtual());
                caravana1->setCarga(0);

                cout << "Caravana " << caravana1->getId()
                     << " foi destruida no combate!" << endl;
                cout << "A carga da caravana destruida foi transferida para a Caravana "
                     << caravana2->getId() << "." << endl;
            } else {
                cout << "Caravana " << caravana1->getId()
                     << " sobreviveu ao combate, mas ficou com poucos tripulantes." << endl;
            }

        } else {
            cout << "O combate terminou em empate!" <<endl;
        }
    }


    void Dados::criarItemAleatorio() {
        srand(time(0));
        int linha, coluna;

        // Procura uma posição aleatória válida no deserto
        do {
            linha = rand() % mapa.getBuffer().getLinhas();
            coluna = rand() % mapa.getBuffer().getColunas();
        } while (mapa.getBuffer().at(linha, coluna) != '.'); // Apenas no deserto

        // Sorteia um tipo de item
        string tipos[] = {"Caixa de Pandora", "Arca do Tesouro", "Jaula", "Mina", "Surpresa"};
        string tipoSorteado = tipos[rand( ) % 5];

        // Cria o item correspondente
        Item* novoItem = nullptr;
        if (tipoSorteado == "Caixa de Pandora") {
            novoItem = new CaixaPandora(mapa, linha, coluna);
        } else if (tipoSorteado == "Arca do Tesouro") {
            novoItem = new ArcaTesouro(mapa, linha, coluna);
        } else if (tipoSorteado == "Jaula") {
            novoItem = new Jaula(mapa, linha, coluna);
        } else if (tipoSorteado == "Mina") {
            novoItem = new Mina(mapa, linha, coluna);
        } else if (tipoSorteado == "Surpresa") {
            novoItem = new Surpresa(mapa, linha, coluna);
        }

        // Adiciona o item ao vetor de itens e ao mapa
        itens.push_back(novoItem);
        mapa.getBuffer().at(linha, coluna) = 'I'; // Representação genérica no mapa

        cout << "Novo item (" << tipoSorteado << ") criado na posica o (" << linha << ", " << coluna << ")." << endl;
    }

    void Dados::verificarItensProximos(Caravana* caravana) {
        int linha = caravana->getLinha();
        int coluna = caravana->getColuna();

        // Percorre os itens para verificar se algum está numa posição adjacente
        for (auto it = itens.begin(); it != itens.end(); ++it) {
            if (mapa.isAdjacente(linha, coluna, (*it)->getLinha(), (*it)->getColuna())) {
                (*it)->efeito(*caravana, mapa); // Aplica o efeito do item
                cout << "Caravana " << caravana->getId() << " apanhou o item (" << (*it)->getTipo() << ")." << endl;

                // Remove o item do mapa e da lista
                mapa.getBuffer().at((*it)->getLinha(), (*it)->getColuna()) = '.';
                delete *it; // Libera a memória
                itens.erase(it); // Remove o item do vetor
                return;
            }
        }
    }

///fazer delete doss itens









