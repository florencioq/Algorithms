#include "stdafx.h"
#include "time.h"
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <string>
#include <windows.h>
#include <vector>
#include <iterator>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm> 
using namespace std;

unsigned menor=1000;

int main() {
	for (int f = 0; f < 10000; f++) {
		std::map<int, std::vector<int>> graph_container;
		string line;
		ifstream myfile("c:/kargerMinCut.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				//cout << line << '\n';
				stringstream stream(line);

				std::vector<int> values;
				int n;
				while (stream >> n){
					values.push_back(n);
				}

				//Remover o primeiro elemento do vetor Values
				int key = values[0];
				std::vector<int>::iterator iti = values.begin();
				values.erase(iti);

				graph_container[key] = values;

				//for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it)
				//	std::cout << *it << std::endl;
			}
			myfile.close();
			Sleep(1 / 100);
			srand(time(NULL));
			while (graph_container.size() > 2) {

				// Seleciona um vertex randomicamante
				//cout << "Tamanho mapa: " << graph_container.size() << endl;

				auto itr = graph_container.begin();
				std::advance(itr, rand() % graph_container.size());
				int rvertex = itr->first;

				//cout << "Primeiro Vertex: " << rvertex << endl;

				// Selecionar um item do set randomicamente
				//cout << "Tamanho vetor: " << graph_container[rvertex].size() << endl;
				int r_el_set = rand() % graph_container[rvertex].size();
				//cout << "Elemento Vertex: " << r_el_set << endl;

				// Pegando o segundo Vertex
				std::vector<int>::iterator it = graph_container[rvertex].begin();
				std::advance(it, r_el_set);
				int second_vertex = *it;
				//cout << "Segundo Vertex: " << second_vertex << endl;

				// Inserindo os elementos do segundo vertex no primeiro vertex
				graph_container[rvertex].insert(graph_container[rvertex].end(), graph_container[second_vertex].begin(), graph_container[second_vertex].end());

				// Apagar o segundo vertex
				graph_container.erase(second_vertex);

				// Remover referências circulares
				for (std::vector<int>::iterator itv = graph_container[rvertex].begin(); itv != graph_container[rvertex].end();)
				{
					if ((*itv == second_vertex) || (*itv == rvertex)) {
						itv = graph_container[rvertex].erase(itv);
					}
					else  ++itv;
				}

				// Substituir o segundo vertex em todos os lugares
				for (std::map<int, std::vector<int>>::iterator it = graph_container.begin(); it != graph_container.end(); it++) {
					// iterator->first = key
					// iterator->second = value
					// Repeat if you also want to iterate through the second map.
					// cout << it->first << endl;
					for (std::vector<int>::iterator itv = it->second.begin(); itv != it->second.end(); ++itv)
					{
						// cout << *itv << " ";
						if (*itv == second_vertex) {
							*itv = rvertex;
						}
					}
				}
			}
		}
		else cout << "Unable to open file";
		if (graph_container.begin()->second.size() < menor) {
			menor = graph_container.begin()->second.size();
			cout << "Menor: " << menor << endl;
		}
	}
	system("pause");
	return 0;
}

