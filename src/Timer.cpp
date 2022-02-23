#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <sstream>

#include "Timer.h"
#include "ArvoreB.h"
#include "Leitura.h"
#include "ordenacao.h"
#include "Parametros.h"

#define STRINGVAZIA ""


Timer::Timer(std::string legenda)
        : m_legenda(move(legenda)), m_tempoInicio(std::chrono::high_resolution_clock::now()), m_swaps(0),
          m_comparacoes(0)
{
}

Timer::~Timer()
{
    Stop();
    double ms = m_duracao * 0.001;
    std::cout << m_legenda << ": " << m_duracao << "us (" << ms << "ms)\n";
}

void Timer::Stop()
{
    auto fimTempo = std::chrono::high_resolution_clock::now();
    auto inicio = std::chrono::time_point_cast<std::chrono::microseconds>(m_tempoInicio).time_since_epoch().count();
    auto fim = std::chrono::time_point_cast<std::chrono::microseconds>(fimTempo).time_since_epoch().count();

    m_duracao = fim - inicio;
}

void Timer::acrecentaSwaps()
{
    ++m_swaps;
}

void Timer::acrecentaComparacoes()
{
    ++m_comparacoes;
}

void Timer::zeraMedicoes()
{
    m_comparacoes = 0;
    m_swaps = 0;
}

void Timer::benchHeapSort(int trials, const string &saidaPath)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in), saidaTxt
            ("./" + saidaPath, ios::app | ios::out);
    if ((arquivoBinario.fail() || inputFile.fail() || saidaTxt.fail()))
    {
        cerr << "[ERROR] arquivo nao pode ser aberto na funcao benchHeapSort()\n";
        assert(false);
    }
    int montanteSwaps = 0, montanteComparacoes = 0;
    double montanteTempo = 0.0;
    string linha;
    vector<Review> reviews;
    while (getline(inputFile, linha))
    {
        saidaTxt << "\t *** \t" << linha << "\t *** \n";
        for (int i = 0; i < trials; ++i)
        {
            int size = atoi(linha.c_str());
            inicializaVetorAleatorio(reviews, size);
            ostringstream msg;
            msg << "HeapSort, trial " << i;
            {
                Timer cronometro(msg.str());
                heapSort(reviews, reviews.size(), this);
                cronometro.Stop();
                montanteTempo += cronometro.m_duracao;
                saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                        m_duracao * 0.001 << "ms)\n";
            }
            montanteComparacoes += this->m_comparacoes;
            montanteSwaps += this->m_swaps;
            saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
                     endl;
            zeraMedicoes();
        }
        this->Stop();
        saidaTxt << "\nresumo algoritmo HeapSort para size = " << reviews.size() << endl;
        saidaTxt << "\tnumero de trials:" << trials << endl;
        saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
        saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
        saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 << "ms)";
        saidaTxt << "\t\nTEMPO MEDIO: " << this->m_legenda << ": " << (montanteTempo / trials) << "us (" << (montanteTempo * 0.001) / trials
                 << "ms)\n";
        saidaTxt << endl << endl << endl;
        zeraMedicoes();
    }
}

void Timer::ModuloTesteHeapSort(int trials, const string &saidaPath)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary),
            saidaTxt("./" + saidaPath, ios::app | ios::out);
    if ((arquivoBinario.fail() || saidaTxt.fail()))
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
        assert(false);
    }
    int montanteSwaps = 0, montanteComparacoes = 0;
    double montanteTempo = 0.0;

    vector<Review> reviews(100);
    for (int i = 0; i < trials; ++i)
    {
        inicializaVetorAleatorio(reviews, reviews.size());
        ostringstream msg;
        msg << "HeapSort, trial " << i;
        {
            Timer cronometro(msg.str());
            heapSort(reviews, reviews.size(), this);
            cronometro.Stop();
            montanteTempo += cronometro.m_duracao;
            saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                    m_duracao * 0.001 << "ms)\n";
        }
        montanteComparacoes += this->m_comparacoes;
        montanteSwaps += this->m_swaps;
        saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
                 endl;
        zeraMedicoes();
        escreverSaidaTxt(saidaTxt, reviews);
    }
    this->Stop();
    saidaTxt << "\nresumo algoritmo HeapSort para size = " << reviews.size() << endl;
    saidaTxt << "\tnumero de trials:" << trials << endl;
    saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
    saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
    saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
             "ms)\n";
    saidaTxt << "\tTEMPO MEDIO: " << this->m_legenda << ": " << (montanteTempo / trials) << "us (" << (montanteTempo * 0.001) / trials
        << "ms)\n";
    saidaTxt << endl << endl << endl;
    zeraMedicoes();
}

void Timer::ModuloTesteQuickSort(int trials, const string &saidaPath)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary),
            saidaTxt("./" + saidaPath, ios::app | ios::out);
    if ((arquivoBinario.fail() || saidaTxt.fail()))
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
        assert(false);
    }
    int montanteSwaps = 0, montanteComparacoes = 0;
    double montanteTempo = 0.0;

    vector<Review> reviews(100);
    for (int i = 0; i < trials; ++i)
    {
        inicializaVetorAleatorio(reviews, reviews.size());
        ostringstream msg;
        msg << "QuickSort, trial " << i;
        {
            Timer cronometro(msg.str());
            quickSort(reviews, 0, reviews.size() - 1, this);
            cronometro.Stop();
            montanteTempo += cronometro.m_duracao;

            saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                    m_duracao * 0.001 << "ms)\n";
        }
        montanteComparacoes += this->m_comparacoes;
        montanteSwaps += this->m_swaps;
        saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
                 endl;
        zeraMedicoes();
        escreverSaidaTxt(saidaTxt, reviews);
    }
    this->Stop();
    saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
    saidaTxt << "\tnumero de trials:" << trials << endl;
    saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
    saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
    saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
             "ms)\n";
    saidaTxt << "\tTEMPO MEDIO: " << this->m_legenda << ": " << (montanteTempo / trials) << "us (" << (montanteTempo * 0.001) / trials
        << "ms)\n";
    saidaTxt << endl << endl << endl;
    zeraMedicoes();
}

void Timer::ModuloTesteCombSort(int trials, const string &saidaPath)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary),
            saidaTxt("./" + saidaPath, ios::app | ios::out);
    if ((arquivoBinario.fail() || saidaTxt.fail()))
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
        assert(false);
    }
    int montanteSwaps = 0, montanteComparacoes = 0;
    double montanteTempo = 0.0;

    vector<Review> reviews(100);
    for (int i = 0; i < trials; ++i)
    {
        inicializaVetorAleatorio(reviews, reviews.size());
        ostringstream msg;
        msg << "CombSort, trial " << i;
        {
            Timer cronometro(msg.str());
            combSort(reviews, reviews.size(), this);
            cronometro.Stop();
            montanteTempo += cronometro.m_duracao;

            saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                    m_duracao * 0.001 << "ms)\n";
        }
        montanteComparacoes += this->m_comparacoes;
        montanteSwaps += this->m_swaps;
        saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
                 endl;
        zeraMedicoes();
        escreverSaidaTxt(saidaTxt, reviews);
    }
    this->Stop();
    saidaTxt << "\nresumo algoritmo CombSort para size = " << reviews.size() << endl;
    saidaTxt << "\tnumero de trials:" << trials << endl;
    saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
    saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
    saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
             "ms)";
    saidaTxt << "\t\nTEMPO MEDIO: " << this->m_legenda << ": " << (montanteTempo / trials) << "us (" << (montanteTempo * 0.001) / trials
        << "ms)\n";
    saidaTxt << endl << endl << endl;
    zeraMedicoes();
}

void Timer::benchQuickSort(int trials, const string &saidaPath)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in), saidaTxt
            ("./" + saidaPath, ios::app | ios::out);
    if ((arquivoBinario.fail() || inputFile.fail() || saidaTxt.fail()))
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
        assert(false);
    }

    int montanteSwaps = 0, montanteComparacoes = 0;
    double montanteTempo = 0.0;

    string linha;
    vector<Review> reviews;
    while (getline(inputFile, linha))
    {
        saidaTxt << "\t *** \t" << linha << "\t *** \n";
        for (int i = 0; i < trials; ++i)
        {
            int newSize = atoi(linha.c_str());
            inicializaVetorAleatorio(reviews, newSize);
            ostringstream msg;
            msg << "QuickSort, trial " << i;
            {
                Timer cronometro(msg.str());
                quickSort(reviews, 0, reviews.size() - 1, this);
                cronometro.Stop();
                montanteTempo += cronometro.m_duracao;

                saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                        m_duracao * 0.001 << "ms)\n";
            }
            montanteComparacoes += this->m_comparacoes;
            montanteSwaps += this->m_swaps;
            saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
                     endl;
            zeraMedicoes();
        }
        this->Stop();
        saidaTxt << "\nresumo algoritmo QuickSort para size = " << reviews.size() << endl;
        saidaTxt << "\tnumero de trials:" << trials << endl;
        saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
        saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
        saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001
                 <<
                 "ms)\n";
        saidaTxt << "\tTEMPO MEDIO: " << this->m_legenda << ": " << (montanteTempo / trials) << "us (" << (montanteTempo * 0.001) / trials
            << "ms)\n";
        saidaTxt << endl << endl << endl;
        zeraMedicoes();
    }
}

void Timer::benchCombSort(int trials, const string &saidaPath)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in), saidaTxt
            ("./" + saidaPath, ios::app | ios::out);
    if ((arquivoBinario.fail() || inputFile.fail() || saidaTxt.fail()))
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
        assert(false);
    }

    int montanteSwaps = 0, montanteComparacoes = 0;
    double montanteTempo = 0.0;

    string linha;
    vector<Review> reviews;
    while (getline(inputFile, linha))
    {
        saidaTxt << "\t *** \t" << linha << "\t *** \n";
        for (int i = 0; i < trials; ++i)
        {
            int size = atoi(linha.c_str());
            inicializaVetorAleatorio(reviews, size);
            ostringstream msg;
            msg << "CombSort, trial " << i;
            {
                Timer cronometro(msg.str());
                combSort(reviews, reviews.size(), this);
                cronometro.Stop();
                montanteTempo += cronometro.m_duracao;

                saidaTxt << "\tTEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                        m_duracao * 0.001 << "ms)\n";
            }
            montanteComparacoes += this->m_comparacoes;
            montanteSwaps += this->m_swaps;
            saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes <<
                     endl;
            zeraMedicoes();
        }
        this->Stop();
        saidaTxt << "\nresumo algoritmo CombSort para size = " << reviews.size() << endl;
        saidaTxt << "\tnumero de trials:" << trials << endl;
        saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
        saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
        saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001
                 <<
                 "ms)\n";
        saidaTxt << "\tTEMPO MEDIO: " << this->m_legenda << ": " << (montanteTempo / trials) << "us (" << (montanteTempo * 0.001) / trials
            << "ms)\n";
        saidaTxt << endl << endl << endl;
        zeraMedicoes();
    }
}

void Timer::benchBTree(int trials, int ordem, const string &saidaPath)
{
    fstream saidaTxt("./" + saidaPath, ios::app | ios::out),
            arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
    unsigned int montanteComparacoesInsercao = 0;
    unsigned int montanteComparacoesBusca = 0;
    unsigned int montanteTempoInsercao = 0;
    unsigned int montanteTempoBusca = 0;
    double montanteTempo = 0.0;

    int qtd = 1'000'000;
    for (int i = 0; i < trials; ++i)
    {
        ArvoreB arvoreB(ordem);
        ostringstream msg;
        msg << "Insercao benchBTree, trial " << i;
        {
            Timer cronometro(msg.str());
            arvoreB.popularArvoreAleatoriamente(&cronometro, qtd);
            cronometro.Stop();
            montanteTempo += cronometro.m_duracao;

            saidaTxt << "TEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                    m_duracao * 0.001 << "ms)\n";
            montanteComparacoesInsercao += cronometro.m_comparacoes;
            montanteTempoInsercao += cronometro.m_duracao;
            saidaTxt << "\tbreve resumo: comparacoes insercao = " << cronometro.m_comparacoes << endl;
        }
        msg.str(string());
        msg << "\tbusca BTree, trial " << i;
        Timer cronometro(msg.str());
        for (int i = 0; i < 100; ++i) // busca
        {
            buscaAleatoriaBTree(arquivoBinario, &arvoreB, &cronometro);
        }
        cronometro.Stop();
        saidaTxt << "\tbreve resumo: comparacoes busca = " << cronometro.m_comparacoes << endl;
        saidaTxt << "TEMPO: " << cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.
                m_duracao * 0.001 << "ms)\n\n";
        montanteComparacoesBusca += cronometro.m_comparacoes;
        montanteTempoBusca += cronometro.m_duracao;

        cronometro.zeraMedicoes();
    }
    this->Stop();
    saidaTxt << "\nresumo algoritmo B Tree para size = " << qtd; // todo: numero magico
    saidaTxt << "\nresumo algoritmo B Tree para ordem = " << ordem << endl; // todo: numero magico
    saidaTxt << "\tnumero de trials:" << trials << endl;
    saidaTxt << "\tnumero de comparacoes medias insercao:" << montanteComparacoesInsercao / trials << endl;
    saidaTxt << "\tnumero de comparacoes medias busca:" << montanteComparacoesBusca / trials << endl;
    saidaTxt << "\ttempo medio de insercao:" << montanteTempoInsercao / trials * 0.001 << " ms\n";
    saidaTxt << "\ttempo medio de busca:" << montanteTempoBusca / trials * 0.001 << " ms\n";
    saidaTxt << "\tTEMPO TOTAL: " << this->m_legenda << ": " << this->m_duracao << "us (" << this->m_duracao * 0.001 <<
             "ms)\n" << endl << endl << endl;
    saidaTxt << "\t\nTEMPO MEDIO: " << this->m_legenda << ": " << (montanteTempo / trials) << "us (" << (montanteTempo * 0.001) / trials
        << "ms)\n";
    zeraMedicoes();
}

void Timer::buscaAleatoriaBTree(fstream &arquivoBinario, ArvoreB *arvore, Timer *timer)
{
    if (arquivoBinario.fail())
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao buscaAleatoriaBTree()";
        assert(false);
    }
    int rank = retonaNumeroAleatorio(0, reviews_totais);

    Review review = retornaReviewEspecifica(rank, arquivoBinario);

    auto resultado = arvore->procurar(review.review_id, timer);
}

//////////////////Huffman///////////

NoHF *Timer::getNoHF(char ch, int freq, NoHF *esq, NoHF *dir)
{
    NoHF *NoHFF = new NoHF();
    NoHFF->ch = ch;
    NoHFF->freq = freq;
    NoHFF->esq = esq;
    NoHFF->dir = dir;
    return NoHFF;
}

bool Timer::verificaFolha(NoHF *raiz)
{
    return raiz->esq == nullptr && raiz->dir == nullptr;
}

void Timer::codificar(NoHF *raiz, string str, unordered_map<char, string> &mapaHuffman)
{
    if (raiz == nullptr)
    {
        return;
    }
    if (verificaFolha(raiz))
    {
        mapaHuffman[raiz->ch] = (str != STRINGVAZIA) ? str : "1";
    }
    codificar(raiz->esq, str + "0", mapaHuffman);
    codificar(raiz->dir, str + "1", mapaHuffman);
}

void Timer::codificaHuffman(string text, dadosParaDescompressao *dados)
{
    int i = 0;
    if (text == STRINGVAZIA)
    {
        return;
    }
    //mapa de frequencia
    unordered_map<char, int> freq;
    //preenchendo mapa
    for (char ch: text)
    {
        freq[ch]++;
    }
    //cria��o da arvore e codificando mapa de huffman
    priority_queue<NoHF *, vector<NoHF *>, comp> filaPrioridade; //processa elemento max, ordem decrescente, pilha
    for (auto pair: freq)
    {
        filaPrioridade.push(getNoHF(pair.first, pair.second, nullptr, nullptr)); //add elementos topo pilha
    }
    while (filaPrioridade.size() != 1) //pega os nós de menor freq e add nó com a soma dos dois
    {
        NoHF *esq = filaPrioridade.top();
        filaPrioridade.pop(); //remove topo pilha
        NoHF *dir = filaPrioridade.top();
        filaPrioridade.pop();
        int auxSoma = esq->freq + dir->freq;
        filaPrioridade.push(getNoHF('\0', auxSoma, esq, dir));
    }
    NoHF *raiz = filaPrioridade.top();
    unordered_map<char, string> mapaHuffman;
    codificar(raiz, STRINGVAZIA, mapaHuffman);
    //preenchendo struct com dados para futura descompress�o
    for (char ch: text)
    {
        dados->dadosComprimidos += mapaHuffman[ch];
    }
    dados->raiz = raiz;
    for (auto pair: mapaHuffman)
    {
        dados->caracteres[i] = pair.first;
        dados->codigos[i] = pair.second;
        i++;
    }
    dados->numeroDeCaracteres = i + 1;
    //dados->mapaHuffman=mapaHuffman;
}

void Timer::codificaNAleatorios(string *auxConcatena, int n, dadosParaDescompressao *dados)
{
    fstream saidaAleatorios("aCodificar.txt", ios::trunc | ios::out);
    vector<Review> reviews;
    inicializaVetorAleatorio(&reviews, n);
    for (int i = 0; i < n; i++)
    {
        *auxConcatena += reviews[i].review_text;
    }
    codificaHuffman(*auxConcatena, dados);

    saidaAleatorios << *auxConcatena;

}

void Timer::imprimeCodigosHuffmanAlt(dadosParaDescompressao *dados)
{
    int i = 0;
    cout << endl << "Os codigos dos caracteres sao:" << endl;
    for (i = 0; i < dados->numeroDeCaracteres; i++)
    {
        cout << dados->caracteres[i] << "|" << dados->codigos[i] << endl;
    }
}

void Timer::descomprimir(string *texto, dadosParaDescompressao *dados)
{
    cout << "iniciando descompressao ..." << endl;
    string aux = STRINGVAZIA;
    *texto = STRINGVAZIA;
    for (int i = 0; i < dados->dadosComprimidos.size(); i++)
    {
        aux += dados->dadosComprimidos[i];
        for (int j = 0; j < dados->numeroDeCaracteres; j++)
        {
            if (aux == dados->codigos[j])
            {
                *texto += dados->caracteres[j];
                aux = STRINGVAZIA;
            }
        }
    }
    cout << "descompressao adaptada " << endl;
}

float Timer::calcTaxaCompressao(string auxConcatena, dadosParaDescompressao dados)
{
    int tamFrase = auxConcatena.length();
    int tamCompressao = 0;
    float taxaCompressao = 0.0;
    cout << "Dados a serem comprimidos: " << tamFrase << " caracteres" << endl;
    int numBits = dados.dadosComprimidos.length();
    if (numBits % 8 == 0)
    {
        tamCompressao = numBits / 8;
    }
    else
    {
        tamCompressao = 1 + numBits / 8;
    }
    cout << "Tamanho apos compressao: " << tamCompressao << endl;
    taxaCompressao = ((float) (tamFrase - tamCompressao) / tamFrase) * 100;
    cout << "Taxa coompressao: " << taxaCompressao << "%" << endl;
    return taxaCompressao;
}


// funcao que vai remontar a arvore e ler os dados do arquivo binario comprimido
void Timer::binDescomprimir(int n)
{
    fstream entradaComprimida("./reviewsComp.bin", ios::in | ios::binary), saidaDescomprimida(
            "./reviewsOrig.bin", ios::trunc | ios::out), aComprimir("aCodificar.txt", ios::in);
    dadosParaDescompressao dados;
    int i = 0;
    string text;
    while (getline(aComprimir, text))
    {}

    unordered_map<char, int> freq;
    //preenchendo mapa
    for (char ch: text)
    {
        freq[ch]++;
    }
    //criacao da arvore e codificando mapa de Huffman
    priority_queue<NoHF *, vector<NoHF *>, comp> filaPrioridade;
    for (auto pair: freq)
    {
        filaPrioridade.push(getNoHF(pair.first, pair.second, nullptr, nullptr));
    }
    while (filaPrioridade.size() != 1)
    {
        NoHF *esq = filaPrioridade.top();
        filaPrioridade.pop();
        NoHF *dir = filaPrioridade.top();
        filaPrioridade.pop();
        int auxSoma = esq->freq + dir->freq;
        filaPrioridade.push(getNoHF('\0', auxSoma, esq, dir));
    }

    NoHF *raiz = filaPrioridade.top();
    unordered_map<char, string> mapaHuffman;
    codificar(raiz, STRINGVAZIA, mapaHuffman);
    //preenchendo struct com dados para futura descompressao
    for (char ch: text)
    {
        dados.dadosComprimidos += mapaHuffman[ch];
    }
    dados.raiz = raiz;
    for (auto pair: mapaHuffman)
    {
        dados.caracteres[i] = pair.first;
        dados.codigos[i] = pair.second;
        i++;
    }
    dados.numeroDeCaracteres = i + 1;

    string aux;
    string texto;
    char c;
    for (int i = 0; i < dados.dadosComprimidos.size(); i++)
    {
        entradaComprimida.get(c);
        aux += c;
        for (int j = 0; j < dados.numeroDeCaracteres; j++)
        {
            if (aux == dados.codigos[j])
            {
                texto += dados.caracteres[j];
                aux = STRINGVAZIA;
            }
        }
    }
    saidaDescomprimida << texto;

}
