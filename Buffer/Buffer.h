//
// Created by Duarte Santos on 19/11/2024.
//

#ifndef TP_POO_BUFFER_H
#define TP_POO_BUFFER_H


class Buffer {

private:
    char **matriz;
    int cursorLinha, cursorColuna;
    int linhas,colunas;

public:

    ///fazer operator>> para conseguir fazer na class Mapa?



    Buffer(int l, int c );
    Buffer();
    // Destrutor: libera a memória alocada
    ~Buffer();

    char& at(int linha,int coluna);

    ///getters
    int getLinhas() const;
    int getColunas() const;

    void setLinhas(int l);
    void setColunas(int c);

    // Esvazia o buffer preenchendo-o com espaços
    void esvaziar();

    // Imprime o conteúdo do buffer na consola
    void imprimir() const;

    // Move o cursor para uma posição específica
    void moverCursor(int l, int c);

    // Insere um caractere na posição atual do cursor
    void inserirChar(char ch);

    // Insere uma string na posição atual do cursor
    void inserirString(const char* str);

    // Insere um inteiro como string na posição atual do cursor
    void inserirInt(int num);

    // Sobrecarga do operador << para inserir uma string
    Buffer& operator<<(const char* str);

    // Sobrecarga do operador << para inserir um caractere
    Buffer& operator<<(char ch);

    // Sobrecarga do operador << para inserir um inteiro
    Buffer& operator<<(int num);

    Buffer(const Buffer& other) ;

    Buffer& operator=(const Buffer& other) ;

    };
#endif //TP_POO_BUFFER_H
