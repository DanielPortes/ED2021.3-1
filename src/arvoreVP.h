#include <iostream>
#include "noVP.h"
//#include "struct.h"
#include <time.h>
#include "leitura.h"
#include"parametros.h"
#include <cassert>
#define A 1000000
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
                if(linkAux->info->id > x->id)
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
                    if(vo->info->id != raiz->info->id)
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
                    if(vo->info->id != raiz->info->id)
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
                    if(vo->info->id != raiz->info->id)
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
                    if(vo->info->id != raiz->info->id)
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

    elementoArvore buscar(string x,int *comparacoes,bool *conseguiu)
    {
        noVP* aux = GetRaiz();
        *comparacoes = *comparacoes + 1;
        elementoArvore nulo;
        if(aux == NULL)
        {
            *conseguiu=false;
            return nulo;
        }
        while(aux)
        {   
            *comparacoes = *comparacoes + 1;
            if(x == aux->info->id)
            {
                *conseguiu=true;
                return *aux->info;
            }
            else if(x < aux->info->id)
            {
                aux = aux->esq;
            }
            else
            {
                aux = aux->dir;
            }
        }
        *conseguiu=false;
        return nulo;
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
void inicializaVetorAleatorioArvore(vector<elementoArvore> &elemento, int size)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
    if (!arquivoBinario.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao inicializaVetor()";
        assert(false);
    }
    int aux=0;
    Review aux2;
    for (int j = 0; j < size; j++)
    {
        elemento.resize(size);
        aux=retonaNumeroAleatorio(0, reviews_totais);
        aux2 =retornaReviewEspecifica(aux, arquivoBinario);
        elemento[j].id = aux2.review_id;
        elemento[j].posicaoBinario=j;
    }
}



void benchmarkArvoreVP(){
    vector<elementoArvore> elementos;
    inicializaVetorAleatorioArvore(elementos,A); //inicializando vetor de elementos
    int comparacoes=0;
    int comparacoesBusca=0;
    int entrada=0;
    bool conseguiu=false;
    elementoArvore aux;
    string id;
    arvoreVP arvore;
    for (int i = 0; i <A;i++){  //inserção
        if(i==0){
            cout<<elementos[i].id<<endl;
        }
        arvore.inserir(&elementos[i],&comparacoes);
    }
    cout <<"inserção concluida,com numero de comapracoes igua a:"<<comparacoes<<endl;

    while(true){ //busca 
        cout<<"deseja procurar uma id?  1-sim || 2-nao"<<endl;
        cin>>entrada;
        if(entrada==1){
            comparacoesBusca=0;
            cout<<"digite a id desejada"<<endl;
            cin>>id;
            aux=arvore.buscar(id,&comparacoesBusca,&conseguiu);
            if(conseguiu){
                cout<<"elemento presente na arvore,realizando acesso a disco para recuperar todas as informacoes:"<<endl;
                fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
                if (!arquivoBinario.is_open())
                {
                    cerr << "ERRO: arquivo nao pode ser aberto na funcao inicializaVetor()";
                    assert(false);
                }
                cout<<endl<<"elemento encontrado com numero de comparacoes igual a :"<<comparacoesBusca<<endl;
                imprimeReviewEspecifica(aux.posicaoBinario,arquivoBinario);
            }
            else{
                cout<<"id nao encontrada"<<endl;
                cout<<comparacoesBusca<<endl;
            }

        }
        else{
            return;
        }
    }
}


