#include "ArvoreB.h"

void No::imprimir()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!folha)
        {
            filhos[i]->imprimir();
        }
        cout << " " << chaves[i].first << " " << chaves[i].second;
    }

    if (!folha)
    {
        filhos[i]->imprimir();
    }
}

void No::inserir(pair<string, int> chave)
{
    int i = n - 1;

    if (folha)
    {
        while (i >= 0 && chaves[i].second > chave.second)
        {
            chaves[i + 1] = chaves[i];
            i--;
        }

        chaves[i + 1] = chave;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && chaves[i] > chave)
            i--;

        if (filhos[i + 1]->n == 2 * t - 1)
        {
            dividirFilho(i + 1, filhos[i + 1]);

            if (chaves[i + 1] < chave)
            {
                i++;
            }
        }
        filhos[i + 1]->inserir(chave);
    }
}

No::No(int t, bool folha)
{
    this->t = t;
    this->folha = folha;

    chaves.resize(2 * t - 1);
    filhos = new No *[2 * t];

    n = 0;
}

void No::dividirFilho(int i, No *p)
{
    No *z = new No(p->t, p->folha);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        z->chaves[j] = p->chaves[j + t];
    }

    if (!p->folha)
    {
        for (int j = 0; j < t; j++)
        {
            z->filhos[j] = p->filhos[j + t];
        }
    }

    p->n = t - 1;
    for (int j = n; j >= i + 1; j--)
    {
        filhos[j + 1] = filhos[j];
    }

    filhos[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
    {
        chaves[j + 1] = chaves[j];
    }

    chaves[i] = p->chaves[t - 1];
    n = n + 1;
}

No *No::procurar(pair<string, int> chave)
{
    int i = 0;
    while (i < n && chave.second > chaves[i].second)
    {
        i++;
    }

    if (chaves[i] == chave)
    {
        return this;
    }

    if (folha)
    {
        return nullptr;
    }

    return filhos[i]->procurar(chave);
}

ArvoreB::ArvoreB(int elemento)
{
    raiz = nullptr;
    t = elemento;
}

void ArvoreB::imprimir()
{
    if (raiz != nullptr)
    {
        raiz->imprimir();
    }
    cout << endl;
}

No *ArvoreB::procurar(pair<string, int> chave)
{
    return (raiz == nullptr) ? nullptr : raiz->procurar(chave);
}

void ArvoreB::inserir(pair<string, int> chave)
{
    if (raiz == nullptr)
    {
        raiz = new No(t, true);
        raiz->chaves[0] = chave;
        raiz->n = 1;
    }
    else
    {
        // Raiz cheia ,arvore cresce em altura
        if (raiz->n == 2 * t - 1)
        {
            //Alocar memória para nova raiz;
            No *pRaiz = new No(t, false);

            // Raiz velha e filha da nova raiz
            pRaiz->filhos[0] = raiz;

            // Dividir a raiz
            pRaiz->dividirFilho(0, raiz);

            // Raiz tem dois filhos,decidir onde vai ser inserido
            int i = 0;
            if (pRaiz->chaves[0].second < chave.second)
            {
                i++;
            }
            pRaiz->filhos[i]->inserir(chave);

            // Mudar raiz
            raiz = pRaiz;
        }
        else
        {
            raiz->inserir(chave);
        }
    }
}