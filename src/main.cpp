// ED2.cpp: define o ponto de entrada para o aplicativo.
//
#include "Leitura.h"
#include <iostream>
#include <cstring>
#include <math.h>
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
	tabela_Hash = 'h',
	huffman = 'c'
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
        cout << "\tDigite 'c' para: Huffman \n";
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
                cout << "\n[AVISO] \t os modulos de testes da arvore b estao dentro da opcao modulo de teste\n";
                cout << "Digite a ordem da primeira B-Tree: ";
                int ordem = 0; // valor arbitrario
                cin >> ordem;

                {
                    Timer timer("Total Btree");
                    timer.benchBTree(3, ordem);
                }
                cout << "Digite a ordem da segunda B-Tree: ";
                int ordem2 = 0; // valor arbitrario
                cin >> ordem2;
                {
                    Timer timer("Total Btree");
                    timer.benchBTree(3, ordem2);
                }

                break;
            }
            case huffman:
            {
                cout << "Qual opcao deseja?\n1-Modo de analise\n2-Compressao manual" << endl;
                int opcaohf = 0;
                cin >> opcaohf;
                switch (opcaohf)
                {
                    case 1:
                    {
                         fstream saidaAnalise("saida.txt", ios::out | ios::app);
                         saidaAnalise << "\n\n\t\t Resumo analise de compressao: \n\n";

                        int numCompressoes[3] = { 10000, 100000, 1000000};
                        for (int i = 0; i < 3; i++)
                        {
                            Timer media("Huffman MEDIA 3 rodadas");

                            saidaAnalise << "\n\tTAMANHO: " << numCompressoes[i] << endl;
                            float somaTaxas = 0.0;
                            for (int j = 0; j < 3; j++)
                            {
                                saidaAnalise << "\nrodada: " << (j + 1) << endl;
                                cout << "Iteracao " << j+1<<" com " << numCompressoes[i]<<" reviews."<< endl;
                                int numReviews = numCompressoes[i];
                                dadosParaDescompressao dados;
                                string destinoDescompressao;
                                string auxConcatena="";
                                Timer timer("Huffman");
                                timer.codificaNAleatorios(&auxConcatena, numReviews,&dados);
                                escreverBinarioHuffman(dados.dadosComprimidos);

                                timer.Stop();
                                saidaAnalise << "tempo de compressao: " << ": " << timer.m_duracao << "us (" << timer.m_duracao * 0.001 << ")" << endl;
                                cout << "Dados comprimidos com sucesso!"<<endl;

                                float taxaCompressao=0.0;
                                taxaCompressao = timer.calcTaxaCompressao(auxConcatena, dados);
                                somaTaxas += taxaCompressao;
                                saidaAnalise << "taxa de compressao: " << taxaCompressao << endl;
                            }
                            media.Stop();
                            saidaAnalise << "tempo de compressao das 3 rodadas: " << ": " << media.m_duracao /3 << "us (" << (media.m_duracao * 0.001) /3 << ")\n" ;
                            cout << "Dados comprimidos com sucesso!"<<endl;

                            float mediaTaxas = somaTaxas/3;
                            saidaAnalise << "Media taxas de compressao para N= " <<numCompressoes[i] << " :"<<mediaTaxas<<endl;
                        }
                        break;
                    }
                    case 2:
                    {
                        int numReviews=0;
                        cout << "Informe a quantidade de reviews a serem comprimidas: " << endl;
                        cin >> numReviews;
                        dadosParaDescompressao dados;
                        string destinoDescompressao;
                        string auxConcatena="";
                        Timer timer("Huffman");
                        timer.codificaNAleatorios(&auxConcatena, numReviews,&dados);
                        escreverBinarioHuffman(dados.dadosComprimidos);
                        cout << "Dados comprimidos com sucesso!"<<endl;
                        timer.imprimeCodigosHuffmanAlt(&dados);
                        float taxaCompressao=0.0;
                        taxaCompressao = timer.calcTaxaCompressao(auxConcatena, dados);
                        timer.descomprimir(&destinoDescompressao,&dados);
                        binDescomprimir(destinoDescompressao);
                        cout<<"Arquivo reviewsOrig.bin com o resultado da descompresao criado."<< endl;
                        break;
                    }
                    default:
                    {
                        cout << "Opcao invalida!" << endl;
                        break;
                    }
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
