#pragma once


#include<iostream>
#include "Leitura.h"

using namespace std;
struct elementoArvore{
    string id;
    int posicaoBinario;
};
struct noVP {
    elementoArvore *info;
    noVP* esq = NULL;
    noVP* dir = NULL;
    noVP* pai = NULL;
    string cor;
};
