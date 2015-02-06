#include "stdafx.h"
#include "time.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> 
using namespace std;

#define DEBUG 0
#define RANDOM 0
#define MOSTRA_ANTES 0
#define MOSTRA_DEPOIS 0

vector<int> quicksort(vector<int>& vec, int esquerda, int direita);
void printvec(vector<int>& vec, int esquerda, int direita);

unsigned comparacoes = 0;

int _tmain(int argc, _TCHAR* argv[])
{

#if RANDOM == 1
	std::vector<int> v;
	unsigned n, r;
	cout << "Tamanho do vetor: ";
	cin >> n;

	srand(time(NULL));
	for (unsigned i = 0; i < n; i++)
	{
		v.push_back(n);
		r = rand() % n;
		v[i] = r;
	}
#else
	//  std::ifstream is("IntegerArray.txt");
	std::ifstream is("QuickSort.txt");
	/// std::ifstream is("c:/100.txt");
	std::istream_iterator<int> start(is), end;
	std::vector<int> v(start, end);
	std::cout << "Read " << v.size() << " numbers" << std::endl;
	system("pause");

#endif // RANDOM == 1

#if MOSTRA_ANTES == 1
	printvec(v,0,v.size()-1);
#endif // MOSTRA_ANTES==1
	
	clock_t tStart = clock();
	comparacoes += v.size() - 1;

	v = quicksort(v, 0, v.size() - 1);

#if MOSTRA_DEPOIS == 1
	printvec(v, 0, v.size() - 1);
#endif // MOSTRA_DEPOIS == 1

	cout << "Comparacoes: " << comparacoes << endl;
	printf("Tempo: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}

vector<int> quicksort(vector<int>& vec, int esquerda, int direita)
{
	// se o tamanho for 1 nao faz nada
	if (esquerda == direita) return vec;

	int pivo, i, j, proximo=0, primeiro, ultimo, meio;

	primeiro = esquerda;
	ultimo = direita;

	// Escolhendo o elemento central
	if ((direita - esquerda + 1) % 2 == 0) {  // par
		meio = esquerda + (direita - esquerda - 1) / 2;
	}
	else {  // impar
		meio = esquerda + (direita - esquerda) / 2;
	}
	
	// Escolhendo a mediana entre o primeiro, ultimo e central
	if ((vec[primeiro] >= vec[ultimo]) && (vec[primeiro] <= vec[meio])) {
		pivo = primeiro;
	}
	if ((vec[primeiro] >= vec[meio]) && (vec[primeiro] <= vec[ultimo])) {
		pivo = primeiro;
	}
	if ((vec[ultimo] >= vec[primeiro]) && (vec[ultimo] <= vec[meio])) {
		pivo = ultimo;
	}
	if ((vec[ultimo] >= vec[meio]) && (vec[ultimo] <= vec[primeiro])) {
		pivo = ultimo;
	}
	if ((vec[meio] >= vec[primeiro]) && (vec[meio] <= vec[ultimo])) {
		pivo = meio;
	}
	if ((vec[meio] >= vec[ultimo]) && (vec[meio] <= vec[primeiro])) {
		pivo = meio;
	}

#if DEBUG == 1
	cout << "Antes: ";
	printvec(vec, esquerda, direita);
	cout << "pivo: " << vec[pivo] << endl;
#endif // 0


	//Troca o pivo com o primeiro
	int aux = vec[esquerda];
	vec[esquerda] = vec[pivo];
	vec[pivo] = aux;
	pivo = esquerda;

	//o i ficara na frente do ultimo elemento menor que o pivo
	i = pivo + 1;
	j = i;

	// Avança pelos menores que o pivo
	while ((i <= direita) && (vec[i] <= vec[pivo])) {
		i++;
		//cout << "i " << vec[i] << endl;
		if (j<direita) j++;
		//cout << "j " << vec[j] << endl;
	}

	// Agora começam os maiores
	while (j < direita) {

		// Avança pelos maiores
		while ((vec[j] > vec[pivo]) && (j < direita)) {
			j++;
			//cout << "j " << vec[j] << endl;
		}

		// chegamos noutro menor. Troca e avança.
		while ((vec[j] <= vec[pivo]) && (j < direita)) {
			int aux = vec[i];
			vec[i] = vec[j];
			vec[j] = aux;
			j++;
			i++;
		}

		// se o j chegou no final, nao incrementa mais ele.
		if ((vec[j] <= vec[pivo]) && (j == direita)) {
			int aux = vec[i];
			vec[i] = vec[j];
			vec[j] = aux;
			i++;
		}
	}

	// Troca o pivo pelo último menor
	if (i > pivo + 1) {
		int aux = vec[pivo];
		vec[pivo] = vec[i - 1];
		vec[i - 1] = aux;
		pivo = i - 1;
		i--;
	}

#if DEBUG==1
	cout << "depois: ";
	printvec(vec, esquerda, direita);
	cout << "Compare: " << comparacoes << endl;
#endif // DEBUG==1


	// Chamadas recursivas
	if (pivo > esquerda) {
		comparacoes += pivo - 1 - esquerda;
		vec = quicksort(vec, esquerda, pivo - 1);
	}

	if (pivo < direita) {
		comparacoes += j - (pivo + 1);
		vec = quicksort(vec, pivo + 1, j);
	}

	return vec;
}

void printvec(vector<int>& vec, int esquerda, int direita)
{
	for (int i = esquerda; i<=direita; i++)
		std::cout << vec[i] << ' ';
	cout << endl;
}