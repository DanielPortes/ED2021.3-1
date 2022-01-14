#pragma once


#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Review
{
    string review_id;
    string review_text;
    int upvotes;
    string app_version;
    string posted_date;
};

struct Review;

void lerArquivoCSV(const string &pathCSV, vector<Review> &reviews);

int retonaNumeroAleatorio(int min, int max);

void imprimeReviewEspecifica(int pos, fstream &entradaBinaria);

void imprimeReviewEspecifica(const Review &review);

Review retornaReviewEspecifica(int indice, fstream &arquivoBinario);

void moduloTeste();

void escreverSaidaBinaria(vector<Review> &reviews);

void escreverSaidaTxt(fstream &saidaTxt, vector<Review> &reviews);

void inicializaVetorAleatorio(vector<Review> &reviews, int size);

void inicializaVetorAleatorio(vector<Review> *reviews, int size);
