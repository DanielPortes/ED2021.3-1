#ifndef LEITURA_H
#define LEITURA_H

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

struct desempenho
{
    string nome_algoritimo;           // Nome do algoritmo (Nome)
    int numComparacoes;               // Guarda a quantidade de comparacoes feitas em cada uma das repeticoes        
    int numTrocas;                    // Guarda a quantidade de trocas feitas em cada uma das repeticoes    
    double tempo;                        // Guarda o tempo de execucao            
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



#endif // !LEITURA_H
