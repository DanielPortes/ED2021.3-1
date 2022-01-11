#include <string.h>
#include<iostream>
#include "leitura.h"

using namespace std;

struct noVP {
    elementoArvore *info;
    noVP* esq = NULL;
    noVP* dir = NULL;
    noVP* pai = NULL;
    string cor;
};
struct elementoArvore{
    string id;
    Review *posicaoBinario;
};
