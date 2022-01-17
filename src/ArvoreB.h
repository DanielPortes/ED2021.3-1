#pragma once

#include "Leitura.h"
#include "Timer.h"

using namespace std;
class Timer;

class No
{
private:
	vector<pair<string, int>> chaves; // {id, localizacao}, localizacao exata no arquivo bin
	int t; // Grau mínimo (define o intervalo para o número de chaves)
	No** filhos;
	int n; // nos ocupados
	bool folha;

public:
	No(int t, bool folha);

	void inserir(pair<string, int> chave, Timer* timer);

	void dividirFilho(int i, No* p, Timer* timer);

	void imprimir();

	No* procurar(string chave, Timer* timer); // Procurar uma chave na arvore

	friend class ArvoreB;
};

class ArvoreB
{
private:
	No* raiz;
	int t; // Grau minimo

public:
	ArvoreB(int elemento);

	void imprimir();

	No* procurar(string chave, Timer* timer);

	void inserir(pair<string, int> chave, Timer* timer);

	void popularArvoreAleatoriamente(Timer* timer, int tam);
};
