#include <iostream>

#include "Parametros.h"
#include "tabelaHash.h"
#include "Timer.h"

using namespace std;

enum saidas
{
	consoleN = 'c',
	arquivoN = 'a',
	imprime_Review_Especifica = 'i',
	heapSort = 'h',
	quickSort = 'q',
	combSort = 'b',
	hashTable = 't',
	BTree = 'B',
	sair = 's'
};

void moduloTeste()
{
	cout << "\t\ttesteImportacao():\n" << endl;
	cout << "\t\t\tDigite 'c' para exporta N registros para o console," << endl;
	cout << "\t\t\tDigite 'a' para exportar N registros para arquivo texto" << endl;
	cout << "\t\t\tDigite 'i' para: imprimeReviewEspecifica(i)\n";
	cout << "\t\t\tDigite 'h' para: heapsort()\n";
	cout << "\t\t\tDigite 'q' para: quicksort()\n";
	cout << "\t\t\tDigite 'b' para: combsort()\n";
	cout << "\t\t\tDigite 't' para: hashTable()\n";
	cout << "\t\t\tDigite 'B' para: BTree()\n";
	cout << "\t\t\tDigite 's' para sair " << endl;
	cout << "\t\t\t";

	char input = '\0';
	cin >> input;

	switch (input)
	{
	case consoleN:
		{
			cout << "\n Digite o valor para N";
			int N = -1;
			cin >> N;
			fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
			for (int i = 0; i < N; i++)
			{
				imprimeReviewEspecifica(
					retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario));
			}
			break;
		}
	case arquivoN:
		{
			cout << "\n Digite o valor para N";
			int N = -1;
			cin >> N;
			vector<Review> reviews(N);
			fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
			fstream arquivoTexto("./saidaTxt.txt", ios::in | ios::trunc | ios::out);
			for (int i = 0; i < N; i++)
			{
				reviews[i] = retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario);
			}
			escreverSaidaTxt(arquivoTexto, reviews);
			cout << "\n\n-------------Exportacao finalizada!-------------\n\n";
			break;
		}
	case imprime_Review_Especifica:
		{
			cout << "\nDigite o numero da review a ser impressa: ";
			int nReview = -1;
			cin >> nReview;
			fstream saidaBinaria("./saidaBinaria.bin", ios::in | ios::binary);
			imprimeReviewEspecifica(nReview, saidaBinaria);
			break;
		}
	case heapSort:
		{
			Timer timer("[Modulo teste] HeapSort");
			timer.ModuloTesteHeapSort(3, "teste.txt");
			break;
		}
	case quickSort:
		{
			Timer timerQuick("[Modulo teste] QuickSort");
			timerQuick.ModuloTesteQuickSort(3, "teste.txt");
			break;
		}

	case combSort:
		{
			Timer timer("[Modulo teste] CombSort");
			timer.ModuloTesteCombSort(3, "teste.txt");
			break;
		}
	case hashTable:
		{
			cout << "Digite quantos reviews aleatorios devem ser importados: ";
			int qtd = 0, topN = 0; // nao representa tamanho real da tabela, m_tam real = N * 1.x
			cin >> qtd;
			vector<pair<string, int>> populares = testaTabelaHash(qtd);
			cout << "\nDigite um valor de N, para imprimir o TOP N versoes mais populares: ";
			cin >> topN;
			escreveNMaisFrequentes(populares, topN, "teste.txt");
			break;
		}
	case BTree:
		{
			cout << "Digite a ordem da B-Tree: ";
			int ordem = 0;
			cin >> ordem;

			ArvoreB arvoreB(ordem);
			Timer timer("BTree");
			arvoreB.popularArvoreAleatoriamente(&timer, 1'000'000);
			for (;;)
			{
				cout << "Digite s para sair, ou ";
				cout << "Digite a id a busca: ";
				string input = string();
				cin >> input;
				if (input == "s")
				{
					break;
				}
				auto retorno = arvoreB.procurar(input, &timer);
				if (!(retorno == nullptr))
				{
					cout << "busca encontrada\n\n";
					continue;
				}
				cout << "busca nao encontrada\n\n";
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
