#include <iostream>
#include "noVP.h"
//#include "struct.h"

class arvoreVP
{
private:
    noVP* raiz;
public:
    arvoreVP() : raiz(NULL) {}
    noVP* GetRaiz()
    {
        return raiz;
    }
    void inserir(elementoArvore *x,int *comparacoes)
    {
        *comparacoes = *comparacoes + 1;
        if(raiz == NULL)
        {
            raiz = new noVP();
            raiz->info = x;
            raiz->pai = NULL;
            raiz->cor = "PRETO";
        }
        else
        {
            noVP *linkAux = GetRaiz();
            noVP* noAux = new noVP();
            noAux->info = x;
            while(linkAux != NULL)
            {
                *comparacoes = *comparacoes + 1;
                if(linkAux->info->posicaoBinario->review_id > x->posicaoBinario->review_id)
                {
                    if(linkAux->esq == NULL)
                    {
                        linkAux->esq = noAux;
                        noAux->cor = "VERMELHO";
                        noAux->pai = linkAux;
                        break;
                    }
                    else
                    {
                        linkAux = linkAux->esq;
                    }
                }
                else
                {
                    if(linkAux->dir == NULL)
                    {
                        linkAux->dir = noAux;
                        noAux->cor = "VERMELHO";
                        noAux->pai = linkAux;
                        break;
                    }
                    else
                    {
                        linkAux = linkAux->dir;
                    }
                }
            }
            insereAux(noAux,comparacoes);
        }
    }

    void insereAux(noVP* z,int *comparacoes)
    {
        while(z->pai->cor == "VERMELHO")
        {
            noVP* vo = z->pai->pai;
            noVP* tio = GetRaiz();
            *comparacoes = *comparacoes + 1;
            if(z->pai == vo->esq)
            {
                 *comparacoes = *comparacoes + 1;
                if(vo->dir)
                {
                    tio = vo->dir;
                }
                 *comparacoes = *comparacoes + 1;
                if(tio->cor == "VERMELHO")
                {
                    z->pai->cor = "PRETO";
                    tio->cor = "PRETO";
                    vo->cor = "VERMELHO";
                    if(vo->info->posicaoBinario->review_id != raiz->info->posicaoBinario->review_id)
                    {
                        z = vo;
                    }
                    else
                    {
                        break;
                    }
                }
                else if(z == vo->esq->dir)
                {
                    rotacaoEsquerda(z->pai);
                }
                else
                {
                    z->pai->cor = "PRETO";
                    vo->cor = "VERMELHO";
                    rotacaoDireita(vo);
                    *comparacoes = *comparacoes + 1;
                    if(vo->info->posicaoBinario->review_id != raiz->info->posicaoBinario->review_id)
                    {
                        z = vo;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                if(vo->esq)
                {
                    tio = vo->esq;
                }
                if(tio->cor == "VERMELHO")
                {
                    z->pai->cor = "PRETO";
                    tio->cor = "PRETO";
                    vo->cor = "VERMELHO";
                    *comparacoes = *comparacoes + 1;
                    if(vo->info->posicaoBinario->review_id != raiz->info->posicaoBinario->review_id)
                    {
                        z = vo;
                    }
                    else
                    {
                        break;
                    }
                }
                else if(z == vo->dir->esq)
                {
                    rotacaoDireita(z->pai);
                }
                else
                {
                    z->pai->cor = "PRETO";
                    vo->cor = "VERMELHO";
                    rotacaoEsquerda(vo);
                    *comparacoes = *comparacoes + 1;
                    if(vo->info->posicaoBinario->review_id != raiz->info->posicaoBinario->review_id)
                    {
                        z = vo;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        raiz->cor = "PRETO";
    }

    noVP* buscar(string x,int *comparacoes)
    {
        noVP* aux = GetRaiz();
        *comparacoes = *comparacoes + 1;

        if(aux == NULL)
        {
            return NULL;
        }
        while(aux)
        {   
            *comparacoes = *comparacoes + 1;
            if(x == aux->info->posicaoBinario->review_id)
            {
                return aux;
            }
            else if(x < aux->info->posicaoBinario->review_id)
            {
                aux = aux->esq;
            }
            else
            {
                aux = aux->dir;
            }
        }
        return NULL;
    }

    void rotacaoEsquerda(noVP* x)
    {
        noVP* aux = new noVP();
        if(x->dir->esq)
        {
            aux->dir = x->dir->esq;
        }
        aux->esq = x->esq;
        aux->info = x->info;
        aux->cor = x->cor;
        x->info = x->dir->info;
        x->esq = aux;
        if(aux->esq)
        {
            aux->esq->pai = aux;
        }
        if(aux->dir)
        {
            aux->dir->pai = aux;
        }
        aux->pai = x;

        if(x->dir->dir)
        {
            x->dir = x->dir->dir;
        }
        else
        {
            x->dir = NULL;
        }

        if(x->dir)
        {
            x->dir->pai = x;
        }
    }

    void rotacaoDireita(noVP* x)
    {
        noVP* aux = new noVP();
        if(x->esq->dir)
        {
            aux->esq = x->esq->dir;
        }
        aux->dir = x->dir;
        aux->info = x->info;
        aux->cor = x->cor;
        x->info = x->esq->info;
        x->cor = x->esq->cor;
        x->dir = aux;
        if(aux->esq)
        {
            aux->esq->pai = aux;
        }
        if(aux->dir)
        {
            aux->dir->pai = aux;
        }
        aux->pai = x;
        if(x->esq->esq)
        {
            x->esq = x->esq->esq;
        }
        else
        {
            x->esq = NULL;
        }
        if(x->esq)
        {
            x->esq->pai = x;
        }
    }
};
