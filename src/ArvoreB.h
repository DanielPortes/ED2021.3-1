#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include <iostream>
#include "Leitura.h"
#include "Timer.h"

using namespace std;

class No
{
private:
    vector<pair<string, int>> chaves; // {id, localizacao}, localizacao exata no arquivo bin
    int t; // Grau mínimo (define o intervalo para o número de chaves)
    No **filhos;
    int n; // nos ocupados
    bool folha;
public:
    No(int t, bool folha);

    void inserir(pair<string, int> chave);

    void dividirFilho(int i, No *p);

    void imprimir();

    No *procurar(pair<string, int>); // Procurar uma chave na arvore

    friend class ArvoreB;

};

class ArvoreB
{
private:
    No *raiz;
    int t; // Grau minimo

public:
    ArvoreB(int elemento);

    void imprimir();

    No *procurar(pair<string, int> chave);

    void inserir(pair<string, int> chave);

    void popularArvoreAleatoriamente();
};

#endif
