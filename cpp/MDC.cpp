// MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned m;
	unsigned n;
	unsigned r;

	cout << "Máximo Divisor Comum" << endl;
	cout << "--------------------" << endl;
	cout << "Enter m: ";
	cin >> m;
	cout << "Enter n: ";
	cin >> n;

	while (n % m != 0) {
		r = n % m;
		n = m;
		m = r;
	}
	cout << endl << "MDC=" << m << endl;
	system("pause");
}

