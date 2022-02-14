#pragma once

#include <iostream>
#include "noVP.h"
#include "Leitura.h"
#include"Parametros.h"
#include <cassert>

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


