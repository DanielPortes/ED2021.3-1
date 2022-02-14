#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include <cassert>
#include <sstream>

#include "Timer.h"
#include "Leitura.h"
#include "ordenacao.h"

Timer::Timer(std::string legenda)
	: m_legenda(move(legenda)), m_tempoInicio(std::chrono::high_resolution_clock::now()), m_swaps(0),
	  m_comparacoes(0)
{
}

Timer::~Timer()
{
	Stop();
	double ms = m_duracao * 0.001;
	std::cout << m_legenda << ": " << m_duracao << "us (" << ms << "ms)\n";
}

void Timer::Stop()
{
	auto fimTempo = std::chrono::high_resolution_clock::now();
	auto inicio = std::chrono::time_point_cast<std::chrono::microseconds>(m_tempoInicio).time_since_epoch().count();
	auto fim = std::chrono::time_point_cast<std::chrono::microseconds>(fimTempo).time_since_epoch().count();

	m_duracao = fim - inicio;
}

void Timer::benchHeapSort(int trials, const string& saidaPath)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in), saidaTxt
		        ("./" + saidaPath, ios::app | ios::out);
	if ((arquivoBinario.fail() || inputFile.fail() || saidaTxt.fail()))
	{
		cerr << "[ERROR] arquivo nao pode ser aberto na funcao benchHeapSort()\n";
		assert(false);
	}
	int montanteSwaps = 0, montanteComparacoes = 0;
	string linha;
	vector<Review> reviews;
	while (getline(inputFile, linha))
	{
		saidaTxt << "\t *** \t" << linha << "\t *** \n";
		for (int i = 0; i < trials; ++i)
		{
			int size = atoi(linha.c_str());
			inicializaVetorAleatorio(reviews, size);
			ostringstream msg;
			msg << "HeapSort, trial " << i;
			{
				Timer cronometro(msg.str());
				heapSort(reviews, reviews.size(), this);
				cronometro.Stop();
				saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
					m_duracao * 0.001 << "ms)\n";
			}
			montanteComparacoes += this->m_comparacoes;
			montanteSwaps += this->m_swaps;
			saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
				endl;
			zeraMedicoes();
		}
		this->Stop();
		saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
		saidaTxt << "\tnumero de trials:" << trials << endl;
		saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
		saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
		saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
			"ms)\n";
		saidaTxt << endl << endl << endl;
		zeraMedicoes();
	}
}

void Timer::ModuloTesteHeapSort(int trials, const string& saidaPath)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary),
	        saidaTxt("./" + saidaPath, ios::app | ios::out);
	if ((arquivoBinario.fail() || saidaTxt.fail()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}
	int montanteSwaps = 0, montanteComparacoes = 0;
	vector<Review> reviews(100);
	for (int i = 0; i < trials; ++i)
	{
		inicializaVetorAleatorio(reviews, reviews.size());
		ostringstream msg;
		msg << "HeapSort, trial " << i;
		{
			Timer cronometro(msg.str());
			heapSort(reviews, reviews.size(), this);
			cronometro.Stop();
			saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
				m_duracao * 0.001 << "ms)\n";
		}
		montanteComparacoes += this->m_comparacoes;
		montanteSwaps += this->m_swaps;
		saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
			endl;
		zeraMedicoes();
		escreverSaidaTxt(saidaTxt, reviews);
	}
	this->Stop();
	saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
	saidaTxt << "\tnumero de trials:" << trials << endl;
	saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
	saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
	saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
		"ms)\n";
	saidaTxt << endl << endl << endl;
	zeraMedicoes();
}

void Timer::ModuloTesteQuickSort(int trials, const string& saidaPath)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary),
	        saidaTxt("./" + saidaPath, ios::app | ios::out);
	if ((arquivoBinario.fail() || saidaTxt.fail()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}
	int montanteSwaps = 0, montanteComparacoes = 0;
	vector<Review> reviews(100);
	for (int i = 0; i < trials; ++i)
	{
		inicializaVetorAleatorio(reviews, reviews.size());
		ostringstream msg;
		msg << "QuickSort, trial " << i;
		{
			Timer cronometro(msg.str());
			quickSort(reviews, 0, reviews.size() - 1, this);
			cronometro.Stop();
			saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
				m_duracao * 0.001 << "ms)\n";
		}
		montanteComparacoes += this->m_comparacoes;
		montanteSwaps += this->m_swaps;
		saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
			endl;
		zeraMedicoes();
		escreverSaidaTxt(saidaTxt, reviews);
	}
	this->Stop();
	saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
	saidaTxt << "\tnumero de trials:" << trials << endl;
	saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
	saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
	saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
		"ms)\n";
	saidaTxt << endl << endl << endl;
	zeraMedicoes();
}

void Timer::ModuloTesteCombSort(int trials, const string& saidaPath)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary),
	        saidaTxt("./" + saidaPath, ios::app | ios::out);
	if ((arquivoBinario.fail() || saidaTxt.fail()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}
	int montanteSwaps = 0, montanteComparacoes = 0;
	vector<Review> reviews(100);
	for (int i = 0; i < trials; ++i)
	{
		inicializaVetorAleatorio(reviews, reviews.size());
		ostringstream msg;
		msg << "CombSort, trial " << i;
		{
			Timer cronometro(msg.str());
			combSort(reviews, reviews.size(), this);
			cronometro.Stop();
			saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
				m_duracao * 0.001 << "ms)\n";
		}
		montanteComparacoes += this->m_comparacoes;
		montanteSwaps += this->m_swaps;
		saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
			endl;
		zeraMedicoes();
		escreverSaidaTxt(saidaTxt, reviews);
	}
	this->Stop();
	saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
	saidaTxt << "\tnumero de trials:" << trials << endl;
	saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
	saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
	saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
		"ms)\n";
	saidaTxt << endl << endl << endl;
	zeraMedicoes();
}

void Timer::benchQuickSort(int trials, const string& saidaPath)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in), saidaTxt
		        ("./" + saidaPath, ios::app | ios::out);
	if ((arquivoBinario.fail() || inputFile.fail() || saidaTxt.fail()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}

	int montanteSwaps = 0, montanteComparacoes = 0;
	string linha;
	vector<Review> reviews;
	while (getline(inputFile, linha))
	{
		saidaTxt << "\t *** \t" << linha << "\t *** \n";
		for (int i = 0; i < trials; ++i)
		{
			int newSize = atoi(linha.c_str());
			inicializaVetorAleatorio(reviews, newSize);
			ostringstream msg;
			msg << "QuickSort, trial " << i;
			{
				Timer cronometro(msg.str());
				quickSort(reviews, 0, reviews.size() - 1, this);
				cronometro.Stop();
				saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
					m_duracao * 0.001 << "ms)\n";
			}
			montanteComparacoes += this->m_comparacoes;
			montanteSwaps += this->m_swaps;
			saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
				endl;
			zeraMedicoes();
		}
		this->Stop();
		saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
		saidaTxt << "\tnumero de trials:" << trials << endl;
		saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
		saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
		saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
			"ms)\n";
		saidaTxt << endl << endl << endl;
		zeraMedicoes();
	}
}

void Timer::benchCombSort(int trials, const string& saidaPath)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in), saidaTxt
		        ("./" + saidaPath, ios::app | ios::out);
	if ((arquivoBinario.fail() || inputFile.fail() || saidaTxt.fail()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}

	int montanteSwaps = 0, montanteComparacoes = 0;
	string linha;
	vector<Review> reviews;
	while (getline(inputFile, linha))
	{
		saidaTxt << "\t *** \t" << linha << "\t *** \n";
		for (int i = 0; i < trials; ++i)
		{
			int size = atoi(linha.c_str());
			inicializaVetorAleatorio(reviews, size);
			ostringstream msg;
			msg << "CombSort, trial " << i;
			{
				Timer cronometro(msg.str());
				combSort(reviews, reviews.size(), this);
				cronometro.Stop();
				saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
					m_duracao * 0.001 << "ms)\n";
			}
			montanteComparacoes += this->m_comparacoes;
			montanteSwaps += this->m_swaps;
			saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
				endl;
			zeraMedicoes();
		}
		this->Stop();
		saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
		saidaTxt << "\tnumero de trials:" << trials << endl;
		saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
		saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
		saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
			"ms)\n";
		saidaTxt << endl << endl << endl;
		zeraMedicoes();
	}
}

void Timer::acrecentaSwaps()
{
	++m_swaps;
}

void Timer::acrecentaComparacoes()
{
	++m_comparacoes;
}

void Timer::zeraMedicoes()
{
	m_comparacoes = 0;
	m_swaps = 0;
}
