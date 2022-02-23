#pragma once
#include <chrono>
#include <string>

#include "ArvoreB.h"
#include "Leitura.h"

class ArvoreB;
using namespace std;
using namespace std::chrono;

class Timer
{
private:
	string m_legenda;
	time_point<high_resolution_clock> m_tempoInicio;
	unsigned long m_swaps;
	unsigned long m_comparacoes;

public:
	double m_duracao;

	Timer(string legenda);

	~Timer();

	void Stop();

	void acrecentaSwaps();

	void acrecentaComparacoes();

	void benchHeapSort(int trials, const string& saidaPath = "saida.txt");

	void benchQuickSort(int trials, const string& saidaPath = "saida.txt");

	void benchCombSort(int trials, const string& saidaPath = "saida.txt");

	void ModuloTesteHeapSort(int trials, const string& saidaPath = "teste.txt");

	void ModuloTesteQuickSort(int trials, const string& saidaPath = "teste.txt");

	void ModuloTesteCombSort(int trials, const string& saidaPath = "teste.txt");

	void buscaAleatoriaBTree(fstream& arquivoBinario, ArvoreB* arvore, Timer* timer);

	void benchBTree(int trials, int ordem, const string& saidaPath = "saida.txt");

	NoHF* getNoHF(char ch, int freq, NoHF* esq, NoHF* dir);
	bool verificaFolha(NoHF* raiz);
	void codificar(NoHF* raiz, string str, unordered_map<char, string> &mapaHuffman);
	void codificaHuffman(string text,dadosParaDescompressao *dados);
	void codificaNAleatorios(string *auxConcatena, int n,dadosParaDescompressao *dados);
	void imprimeCodigosHuffmanAlt(dadosParaDescompressao *dados);
	void descomprimir(string *texto,dadosParaDescompressao *dados);
	float calcTaxaCompressao (string auxConcatena, dadosParaDescompressao dados);

	void binDescomprimir(int n);
	void registraDados(dadosParaDescompressao *dados);

	Timer(const Timer&) = delete;

	Timer& operator=(const Timer&) = delete;

private:
	void zeraMedicoes();
};
