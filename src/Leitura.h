#pragma once


#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;
struct NoHF
{
    char ch;
    int freq;
    NoHF *esq, *dir;
};
struct comp
{
    bool operator()(const NoHF* l, const NoHF* r) const
    {
        return l->freq > r->freq;
    }
};
struct Review
{
    string review_id;
    string review_text;
    int upvotes;
    string app_version;
    string posted_date;
};
struct dadosParaDescompressao
{
    NoHF *raiz;
    string dadosComprimidos;
    string caracteres[255],codigos[255];
    int numeroDeCaracteres;
};

struct Review;
streampos inline tamanhoArquivo(fstream& arq);
void lerArquivoCSV(const string &pathCSV, vector<Review> &reviews);

int retonaNumeroAleatorio(int min, int max);

void imprimeReviewEspecifica(int pos, fstream &entradaBinaria);

void imprimeReviewEspecifica(const Review &review);

Review retornaReviewEspecifica(int indice, fstream &arquivoBinario);

void moduloTeste();

void escreverSaidaBinaria(vector<Review> &reviews);

void escreverBinarioHuffman(string dadosComprimidos);

void binDescomprimir(string destinoDescompressao);

void escreverSaidaTxt(fstream &saidaTxt, vector<Review> &reviews);

void inicializaVetorAleatorio(vector<Review> &reviews, int size);

void inicializaVetorAleatorio(vector<Review> *reviews, int size);
