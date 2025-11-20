//
// Created by Duarte Santos on 19/12/2024.
//

#ifndef TP_POO_TEMPESTADEAREIA_H
#define TP_POO_TEMPESTADEAREIA_H


class Mapa;

class TempestadeAreia {
private:
    int linhaC, colunaC, raio;
    bool ativa ;
public:
    TempestadeAreia (int linhaCentro, int colunaCentro, int raio);
    TempestadeAreia();
    bool isAtiva () const;
    bool isDentro(int linha_caravana, int coluna_caravana) const;
    void setInativa ();
};


#endif //TP_POO_TEMPESTADEAREIA_H
