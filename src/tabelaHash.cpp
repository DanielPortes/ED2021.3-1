#include <iostream>
#include <cmath>
#include <fstream>
#include <cassert>

#include "tabelaHash.h"
#include "Leitura.h"
#include "Parametros.h"
#include "ordenacao.h"

using namespace std;

int constexpr PRIME1 = 151;
int constexpr PRIME2 = 157;

tabelaHash::tabelaHash(int tam)
        : m_tam{tam}, m_insertionsFails{}, m_colisoes{}
{
	vetor = new vector<pair<string, int>>;
	vetor->resize(tam);

    for (int i = 0; i < tam; i++)
    {
        vetor->at(i).first= {};
        vetor->at(i).second = {};
    }
}

tabelaHash::~tabelaHash()
{
	delete vetor;
}

int tabelaHash::hashfunction(string str, int prime, int tam)
{
	long hash = 0;
	const int lengthStr = str.length();

	for (int i = 0; i < lengthStr; i++)
	{
		hash += (long)pow(prime, lengthStr - (i + 1)) * str[i];
		if (prime == PRIME1)
		{
			hash = hash % tam;
		}
		else
		{
			hash = 1 + (hash % tam);
		}
	}
	return (int)hash;
}

int tabelaHash::hash(const string &str, int i)
{
	const int hash_a = hashfunction(str, PRIME1, m_tam);
	const int hash_b = hashfunction(str, PRIME2, m_tam - 3);
	return (hash_a + (i * (hash_b))) % m_tam;
}

void tabelaHash::insertion(const string &key)
{
    for (int i = 0; i < m_tam; i++)
    {
        unsigned long index = hash(key, i);

        if (vetor->at(index).first.empty() || vetor->at(index).first == key) // ou a vaga esta disponivel ou a chave eh identica
        {
            vetor->at(index).first = key;
            vetor->at(index).second++;
            return;
        } else
        {
            m_colisoes++;
        }
	}
    cerr << "\n[WARNING] fail in insertion one element, key: " << key << "\n";
    m_insertionsFails++;
}

void imprimeNMaisFrequentes(vector<pair<string, int>>& vetor, int nPrimeiros)
{
	cout << endl;
	for (int i = 0; i < nPrimeiros && vetor.size(); ++i)
	{
		cout << vetor[i].first << " - frequencia: " << vetor[i].second << endl;
	}
}

void escreveNMaisFrequentes(vector<pair<string, int>> &vetor, int nPrimeiros, const string &saidaPath)
{
    fstream saida("./" + saidaPath, ios::out | ios::app);
    if (!saida.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao escreveNMaisFrequentes()";
        assert(false);
    }
    saida << "Impressao dos versions mais frequentes\n";
    for (int i = 0; i < nPrimeiros && i < vetor.size(); ++i)
    {
		saida << vetor[i].first << " - frequencia: " << vetor[i].second << endl;
	}
}

vector<pair<string, int>> tabelaHash::retornaApenasElementosPreenchidosVetor()
{
	vector<pair<string, int>> temp;
	for (int i = 0; i < vetor->size(); ++i)
	{
		if (!vetor->at(i).first.empty())
		{
			temp.push_back(vetor->at(i));
		}
	}
	return temp;
}

void tabelaHash::escreveTabelaHash() // util para visualizar distribuicao
{
	fstream saidaTxt("./teste.txt", ios::app | ios::out);
	if (!saidaTxt.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao escreveTabelaHash()";
		assert(false);
	}
	for (int i = 0; i < vetor->size(); ++i)
	{
		saidaTxt << vetor->at(i).first << " : " << vetor->at(i).second << ",\t";
		if (!((i + 1) % 10))
		{
			saidaTxt << endl;
		}
	}
	saidaTxt << "\nNUMERO DE COLISOES TOTAIS: " << m_colisoes << "\n";
}

/*
 * A funcao cria uma tabela e retorna um vetor dos elementos adicionados para ordenacao
 */
vector<pair<string, int>> testaTabelaHash(int hashSize)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
	if (!arquivoBinario.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao desempenhoHash()";
		assert(false);
	}
	tabelaHash tabela(hashSize * 1.3f);
	string app_version;
	for (int i = 0; i < hashSize; i++)
    {
        app_version = retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario).app_version;
        // nenhuma review sem app version sera adicionada
        if (app_version.empty())
        {
            --i;
            continue;
        }
        tabela.insertion(app_version);
    }

	cout << "\nDeseja escrever a distribuicao da tabela e apps mais frequentes no arquivo teste.txt ? [s/n] ";
	char input = '\0';
	cin >> input;
	switch (input)
	{
	case 's':
		{
			tabela.escreveTabelaHash();
			break;
		}
	default:
		break;
	}

	vector<pair<string, int>> populares = tabela.retornaApenasElementosPreenchidosVetor();
	quickSortHash(populares, 0, populares.size() - 1);

	return populares;
}
