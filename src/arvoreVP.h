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
    arvoreVP();
    noVP* GetRaiz();
    
    void inserir(elementoArvore *x,int *comparacoes);
    

    void insereAux(noVP* z,int *comparacoes);
    
    elementoArvore buscar(string x,int *comparacoes,bool *conseguiu);
    

    void rotacaoEsquerda(noVP* x);
   

    void rotacaoDireita(noVP* x);
    
};


