#include "ArvoreB.h"

#include <cassert>
#include "iostream"

#include "Parametros.h"

#include "Timer.h"

No::No(int ordem, bool folha)
{
	this->m = ordem;
	this->t = ordem / 2;
	this->folha = folha;

	chaves.resize(m - 1, {string(), 0});
	// this->chaves = new pair<string, int>[m - 1];
	filhos = new No*[m];

	n = 0;
}

void No::imprimir()
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (!folha)
		{
			filhos[i]->imprimir();
		}
		cout << " " << chaves[i].first << " " << chaves[i].second << "\n";
	}
	cout << endl; // todo: checar ordem

	if (!folha)
	{
		filhos[i]->imprimir();
	}
}

void No::inserir(pair<string, int> chave, Timer* timer)
{
	int i = n - 1;
	timer->acrecentaComparacoes();
	if (folha)
	{
		while (i >= 0 && chaves[i].first > chave.first)
		{
			timer->acrecentaComparacoes();
			chaves[i + 1] = chaves[i];
			i--;
		}

		chaves[i + 1] = chave;
		n = n + 1;
	}
	else
	{
		while (i >= 0 && chaves[i].first > chave.first)
		{
			timer->acrecentaComparacoes();
			i--;
		}
		timer->acrecentaComparacoes();
		if (filhos[i + 1]->n == m - 1)
		{
			dividirFilho(i + 1, filhos[i + 1], timer);
			timer->acrecentaComparacoes();
			if (chaves[i + 1].first < chave.first)
			{
				i++;
			}
		}
		filhos[i + 1]->inserir(chave, timer);
	}
}

void ArvoreB::liberaNo(No* no)
{
	if (!no->folha)
	{
		for (int i = 0; i <= no->n; ++i)
		{
			liberaNo(no->filhos[i]);
		}
	}

	delete[] no->filhos;
	// delete no->chaves;
	delete no;
}

ArvoreB::~ArvoreB()
{
	liberaNo(this->raiz);
}

void No::dividirFilho(int i, No* p, Timer* timer)
{
	No* z = new No(p->m, p->folha);
	z->n = t - 1;

	timer->acrecentaComparacoes();
	if (!p->folha)
	{
		for (int j = 0; j < t; j++)
		{
			timer->acrecentaComparacoes();
			z->filhos[j] = p->filhos[j + t];
		}
	}

	for (int j = 0; j < t - 1; j++)
	{
		timer->acrecentaComparacoes();
		z->chaves[j] = p->chaves[j + t];
	}

	p->n = t - 1;
	for (int j = n; j >= i + 1; j--)
	{
		timer->acrecentaComparacoes();
		filhos[j + 1] = filhos[j];
	}

	filhos[i + 1] = z;

	for (int j = n - 1; j >= i; j--)
	{
		timer->acrecentaComparacoes();
		chaves[j + 1] = chaves[j];
	}

	chaves[i] = p->chaves[t - 1];
	n = n + 1;
}

No* No::procurar(const string& chave, Timer* timer)
{
	int i = 0;
	while (i < n && chave > chaves[i].first)
	{
		timer->acrecentaComparacoes();
		i++;
	}
	timer->acrecentaComparacoes();
	if (chaves[i].first == chave)
	{
		return this;
	}
	timer->acrecentaComparacoes();
	if (folha)
	{
		return nullptr;
	}

	return filhos[i]->procurar(chave, timer);
}

ArvoreB::ArvoreB(int ordem)
{
	if (ordem <= 1)
	{
		cerr << "\nB-TREE criada com ordem menor ou igual a 1\n";
		exit(313213);
	}
	raiz = nullptr;
	t = ordem / 2;
	m = ordem;
}

void ArvoreB::imprimir()
{
	if (raiz != nullptr)
	{
		raiz->imprimir();
	}
	cout << endl;
}

No* ArvoreB::procurar(const string& chave, Timer* timer)
{
	timer->acrecentaComparacoes();
	return (raiz == nullptr) ? nullptr : raiz->procurar(chave, timer);
}

void ArvoreB::inserir(pair<string, int> chave, Timer* timer)
{
	timer->acrecentaComparacoes();
	if (raiz == nullptr)
	{
		raiz = new No(m, true);
		raiz->chaves[0] = chave;
		raiz->n = 1;
	}
	else
	{
		// no cheio
		timer->acrecentaComparacoes();
		if (raiz->n == m - 1)
		{
			No* pRaiz = new No(m, false);

			pRaiz->filhos[0] = raiz;

			pRaiz->dividirFilho(0, raiz, timer);

			// Raiz tem dois filhos,decidir onde vai ser inserido
			int i = 0;
			timer->acrecentaComparacoes();
			if (pRaiz->chaves[0].first < chave.first)
			{
				i++;
			}
			pRaiz->filhos[i]->inserir(chave, timer);

			// Mudar raiz
			raiz = pRaiz;
		}
		else
		{
			raiz->inserir(chave, timer);
		}
	}
}

/*
funcao exigida para o relatorio,
*/
void ArvoreB::popularArvoreAleatoriamente(Timer* timer, int tam)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::binary | ios::in);
	if (arquivoBinario.fail())
	{
		cerr << "[ERROR] arquivo nao pode ser aberto na funcao popularArvoreAleatoriamente\n";
		assert(false);
	}
	for (int i = 0; i < tam; ++i)
	{
		int rank = retonaNumeroAleatorio(0, reviews_totais);
		auto review = retornaReviewEspecifica(rank, arquivoBinario);
		auto chave = make_pair(review.review_id, rank * TAMANHO_MAX_STRUCT);
		this->inserir(chave, timer);
	}
}
