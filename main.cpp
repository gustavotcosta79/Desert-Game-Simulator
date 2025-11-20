#include <iostream>
#include <sstream>
#include "Buffer/Mapa.h"
#include "Interface.h"
#include "Dados.h"

using namespace std;
int main() {

    Dados dados;  // Cria a classe Dados

    Interface i(&dados);  // Cria a interface e passa a instância de Dados
    i.executa();  // Executa a interação

    Dados outro(dados);//se der erro de execucao destas linhas ha algum problema
    Dados outro2;
    outro2= dados;

    return 0;



/*
  Dados dados;
    string comando, operacao;





    bool running = true;
    cout << "Digite um comando: ";

    while(running){
        cin >> comando;

        istringstream input(comando);
        input >> operacao;

        if ( operacao == "config"){
            string nomeFicheiro;
            input >> nomeFicheiro;

            if (!nomeFicheiro.empty()){
                 dados.carregarDeFicheiro(nomeFicheiro);
            }
        }else if (comando == "sair" )
            running = false;
    }

    Interface i(&dados);



    Dados dados1();//class composta com todas os dados (objetos)
    Interface i(&dados);
    i.executa();



    // Criar uma instância do Mapa, com as dimensões especificadas no arquivo
    Mapa mapa("ficheiro.txt");

    //mapa.carregarDeFicheiro("ficheiro.txt");

    //cout << mapa.getBuffer().getLinhas() << " " << mapa.getColunas()<<endl;


    mapa.mostrarConfiguracoes();

 * */



    return 0;

}
///Perguntas:
//A nossa estrutura do Mapa e buffer esta a fazer sentido?
//perguntar se é para fazer o getbuf()
//É para criar bufer com memoria dinamica???
//Ver porque o switch esta a dar mal

