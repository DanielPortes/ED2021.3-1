#pragma once

#include "Leitura.h"
#include "Timer.h"

using namespace std;
class Timer;

class No
{
private:
	vector<pair<string, unsigned int>> chaves; // {id, localizacao}, eh a localizacao exata no arquivo bin
	No** filhos;
	int t; // Grau mínimo
	int m; // g max
	int n; // nos ocupados
	bool folha;

public:
	No(int ordem, bool folha);

	void inserir(pair<string, int> chave, Timer* timer);

	void dividirFilho(int i, No* p, Timer* timer);

	void imprimir();

	No* procurar(const string& chave, Timer* timer); // Procurar uma chave na arvore

	friend class ArvoreB;
};

class ArvoreB
{
private:
	No* raiz;
	int t; // Grau minimo
	int m; // g max


public:
	ArvoreB(int ordem);

	~ArvoreB();

	void liberaNo(No* no);

	void imprimir();

	No* procurar(const string& chave, Timer* timer);

	void inserir(pair<string, int> chave, Timer* timer);

	void popularArvoreAleatoriamente(Timer* timer, int tam);
};
