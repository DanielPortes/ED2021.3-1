#include <vector>
#include <algorithm>
#include <iostream>

#include "ordenacao.h"
#include "Leitura.h"
#include "Timer.h"

void heapSort(std::vector<Review>& reviews, int n, Timer* timer)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		timer->acrecentaSwaps();
		heapify(reviews, n, i, timer);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		swap(reviews[0], reviews[i]);
		heapify(reviews, i, 0, timer);
	}
}

void heapify(vector<Review>& reviews, int n, int i, Timer* timer)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	timer->acrecentaComparacoes();
	if (left < n && reviews[left].upvotes > reviews[largest].upvotes)
	{
		largest = left;
	}
	timer->acrecentaComparacoes();
	if (right < n && reviews[right].upvotes > reviews[largest].upvotes)
	{
		largest = right;
	}
	timer->acrecentaComparacoes();
	if (largest != i)
	{
		swap(reviews[i], reviews[largest]);
		timer->acrecentaSwaps();
		heapify(reviews, n, largest, timer);
	}
}


pair<int, int> partition(vector<Review> &vet, size_t inicio, size_t fim, Timer *timer)
{
    int mid = inicio;
    int pivot = vet[fim].upvotes;

    while (mid <= fim)
    {
        if (vet[mid].upvotes < pivot)
        {
            swap(vet[inicio], vet[mid]);
            ++inicio, ++mid;
        }
        else if (vet[mid].upvotes > pivot)
        {
            swap(vet[mid], vet[fim]);
            --fim;
        }
        else
        {
            ++mid;
        }
    }

    return make_pair(inicio - 1, mid);
}

void quickSort(vector<Review>& vet, size_t inicio, size_t fim, Timer* timer)
{
    if (inicio >= fim)
    {
        return;
    }

    if (inicio - fim == 1)
    {
        if (vet[inicio].upvotes < vet[fim].upvotes)
        {
            swap(vet[inicio], vet[fim]);
        }
        return;
    }

    pair<int, int> pivot = partition(vet, inicio, fim, nullptr);

    quickSort(vet, inicio, pivot.first, nullptr);

    quickSort(vet, pivot.second, fim, nullptr);
}

void quickSortHash(vector<pair<string, int>>& vetor, int inicio, int fim)
{
	if (inicio < fim)
	{
		int pivo = quickSortHashAux(vetor, inicio, fim);
		quickSortHash(vetor, inicio, pivo - 1);
		quickSortHash(vetor, pivo + 1, fim);
	}
}

int quickSortHashAux(vector<pair<string, int>>& vet, int inicio, int fim)
{
	int pivo = vet[fim].second;

	int i = (inicio - 1);

	for (int j = inicio; j <= fim - 1; j++)
	{
		if (vet[j].second >= pivo)
		{
			i++;
			swap(vet[i], vet[j]);
		}
	}
	swap(vet[i + 1], vet[fim]);
	return (i + 1);
}

int nextGap(int gap)
{
	gap = int(gap / 1.3);

	if (gap < 1)
	{
		return 1;
	}

	return gap;
}

void combSort(std::vector<Review>& reviews, int n, Timer* timer)
{
	int gap = n;

	while (gap != 1)
	{
		timer->acrecentaComparacoes(); // while
		timer->acrecentaComparacoes(); // next gap
		gap = nextGap(gap);

		for (int i = 0; i < n - gap; i++)
		{
			timer->acrecentaComparacoes();
			if (reviews[i].upvotes > reviews[i + gap].upvotes)
			{
				swap(reviews[i], reviews[i + gap]);
				timer->acrecentaSwaps();
			}
		}
	}
}
