// ED2.cpp: define o ponto de entrada para o aplicativo.
//
#include "Leitura.h"
#include <iostream>
#include "Timer.h"
#include "tabelaHash.h"
#include "moduloArvoreVP.h"

using namespace std;

enum EscolhasChamada
{
	lerCSV = 'l',
	escreverBinario = 'e',
	modulo_de_teste = 't',
	ordenacao = 'o',
	sair = 's',
	arvoreVerPre = 'v',
	BTree = 'b',
	tabela_Hash = 'h'
};

void menu(const string& caminhoEntrada, vector<Review>& reviews)
{
	while (true)
	{
		cout << "\n**************\tMENU\t**************";
		cout << "\nEscolhe entre usar as funcoes:\n";
		cout << "\tDigite 'l' para: lerCSV() \n";
		cout << "\tDigite 'e' para: escreverBinario()\n";
		cout << "\tDigite 'o' para: ordenacao() \n";
		cout << "\tDigite 'h' para: tabelaHash() \n";
		cout << "\tDigite 'v' para: arvoreVP() \n";
		cout << "\tDigite 'b' para: BTree() \n";
		cout << "\tDigite 't' para: Modulo de teste \n";
		cout << "\tDigite 's' para sair " << endl;

		char entrada = '\0';
		cin >> entrada;

		switch (entrada)
		{
		case lerCSV:
			{
				{
					Timer timer("Tempo para lerArquivoCSV()");
					lerArquivoCSV(caminhoEntrada, reviews);
					break;
				}
			}
		case escreverBinario:
			{
				{
					Timer timer("Tempo para escreveBin():");
					escreverSaidaBinaria(reviews);
					break;
				}
			}
		case modulo_de_teste:
			{
				moduloTeste();
				break;
			}
		case ordenacao:
			{
				// os algoritmos de sorting estao todos em ordenacao.cpp, mas os de benchmark foi realizado em Timer para aproveitamento da classe
				{
					Timer timer("HeapSort");
					timer.benchHeapSort(3);
				}
				{
					Timer timerQuick("QuickSort");
					timerQuick.benchQuickSort(3);
				}
				{
					Timer timerComb("CombSort");
					timerComb.benchCombSort(3);
				}
				break;
			}
		case tabela_Hash:
			{
				cout << "Digite quantos reviews aleatorios devem ser importados: ";
				int input = 0; // nao representa tamanho real da tabela, m_tam = N * 1.x
				cin >> input;
				vector<pair<string, int>> populares = testaTabelaHash(input);
				cout << "Digite um valor de N, para imprimir o TOP N versoes mais populares: ";
				cin >> input;
				imprimeNMaisFrequentes(populares, input);
				break;
			}
		case arvoreVerPre:
			{
				cout << "qual opcao deseja?\n1-modo de analise\n2-busca manual" << endl;
				int opcaovp = 0;
				cin >> opcaovp;
				switch (opcaovp)
				{
				case 1:
					{
						benchmarkArvoreVP();
						break;
					}
				case 2:
					{
						testArvoreVP();
						break;
					}
				default:
					{
						cout << "opcao invalida" << endl;
						break;
					}
				}
				break;
			}
		case BTree:
			{
				{
					Timer timer("Total Btree");
					timer.benchBTree(3, 20);
				}
				{
					Timer timer("Total Btree");
					timer.benchBTree(3, 200);
				
				}

				break;
			}
		case sair:
			{
				return;
			}
		default:
			{
				break;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));

	vector<Review> reviews;

	menu(argv[1], reviews);
	// menu(arquivo_path, reviews);

	return 0;
}
