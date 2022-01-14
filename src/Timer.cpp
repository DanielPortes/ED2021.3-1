#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include <cassert>
#include <sstream>

#include "ArvoreB.h"
#include "Leitura.h"
#include "ordenacao.h"
#include "Parametros.h"

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
		saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001
			<<
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
		saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001
			<<
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
		saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001
			<<
			"ms)\n";
		saidaTxt << endl << endl << endl;
		zeraMedicoes();
	}
}

void Timer::benchBTree(int trials, const string& saidaPath)
{
	fstream saidaTxt("./" + saidaPath, ios::app | ios::out),
	        arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
	int montanteComparacoesInsercao = 0;
	int montanteComparacoesBusca = 0;

	for (int i = 0; i < trials; ++i)
	{
		auto* arvoreB = new ArvoreB(3);
		ostringstream msg;
		msg << "Insercao benchBTree, trial " << i;
		{
			Timer cronometro(msg.str());
			arvoreB->popularArvoreAleatoriamente(&cronometro, 1'000'000);
			cronometro.Stop();
			saidaTxt << "TEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
				m_duracao * 0.001 << "ms)\n";
			montanteComparacoesInsercao += cronometro.m_comparacoes;
			saidaTxt << "\tbreve resumo: comparacoes insercao = " << cronometro.m_comparacoes << endl;
		}
		msg.str(string());
		msg << "\tbusca BTree, trial " << i;
		Timer cronometro(msg.str());
		for (int i = 0; i < 100; ++i) // busca
		{
			buscaAleatoriaBTree(arquivoBinario, arvoreB, &cronometro);
		}
		cronometro.Stop();
		saidaTxt << "\tbreve resumo: comparacoes busca = " << cronometro.m_comparacoes << endl;
		saidaTxt << "TEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
				m_duracao * 0.001 << "ms)\n";
		montanteComparacoesBusca += cronometro.m_comparacoes;
		cronometro.zeraMedicoes();
		delete arvoreB;
	}
	this->Stop();
	saidaTxt << "\nresumo algoritmo B Tree para size = " << "1'000'000" << endl; // todo: numero magico
	saidaTxt << "\tnumero de trials:" << trials << endl;
	saidaTxt << "\tnumero de comparacoes medias insercao:" << montanteComparacoesInsercao / trials << endl;
	saidaTxt << "\tnumero de comparacoes medias busca:" << montanteComparacoesBusca / trials << endl;
	saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
		"ms)\n" << endl << endl << endl;
	zeraMedicoes();
}

void Timer::buscaAleatoriaBTree(fstream& arquivoBinario, ArvoreB* arvore, Timer* timer)
{
	if (arquivoBinario.fail())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao buscaAleatoriaBTree()";
		assert(false);
	}
	int rank = retonaNumeroAleatorio(0, reviews_totais);
	Review review = retornaReviewEspecifica(rank, arquivoBinario);
	arvore->procurar(review.review_id, timer);
}
