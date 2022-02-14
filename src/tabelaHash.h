#pragma once

#include "Leitura.h"

using namespace std;

void imprimeNMaisFrequentes(vector<pair<string, int>> &vetor, int nPrimeiros);

void escreveNMaisFrequentes(vector<pair<string, int>> &vetor, int nPrimeiros, const string &saidaPath = "teste.txt");

vector<pair<string, int>> testaTabelaHash(int hashSize);

class tabelaHash
{
private:
    vector<pair<string, int>>* vetor;
    int m_tam;
    int m_insertionsFails;
    int m_colisoes;

private:
    int hash(const string &chave, int i);

    int hashfunction(string str, int prime, int tam);

public:
    tabelaHash(int tam);

    ~tabelaHash();

    void insertion(const string &x);

    vector<pair<string, int>> retornaApenasElementosPreenchidosVetor();

    void escreveTabelaHash();
};
