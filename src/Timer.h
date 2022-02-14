#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

#include "Leitura.h"

using namespace std;
using namespace std::chrono;

class Timer
{
private:
    string m_legenda;
    time_point<high_resolution_clock> m_tempoInicio;
    long long m_duracao;
    unsigned long m_swaps;
    unsigned long m_comparacoes;

public:
    Timer(string legenda);

    ~Timer();

    void Stop();

    void acrecentaSwaps();

    void acrecentaComparacoes();

    void benchHeapSort(int trials, const string &saidaPath = "saida.txt");

    void benchQuickSort(int trials, const string &saidaPath = "saida.txt");

    void benchCombSort(int trials, const string &saidaPath = "saida.txt");

    void ModuloTesteHeapSort(int trials, const string &saidaPath = "teste.txt");

    void ModuloTesteQuickSort(int trials, const string &saidaPath = "teste.txt");

    void ModuloTesteCombSort(int trials, const string &saidaPath = "teste.txt");

    Timer(const Timer &) = delete;

    Timer &operator=(const Timer &) = delete;

private:
    void zeraMedicoes();
};

#endif
