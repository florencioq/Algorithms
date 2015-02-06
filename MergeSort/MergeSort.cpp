// MergeSort.cpp : Defines the entry point for the console application.
//

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

vector<int> mymerge(vector<int> &vec, const vector<int>& left, const vector<int>& right);
vector<int> merge_sort(vector<int>& vec);

unsigned contaInversoes = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	cout << "Enter size of vector: ";
	cin >> n;

	srand(time(NULL));

	for (i = 0; i < n; i++)
	{
	v.push_back(n);
	r = rand() % 100000;
	v[i] = r;
	}
	*/

	std::ifstream is("IntegerArray.txt");
//	std::ifstream is("QuickSort.txt");
	std::istream_iterator<int> start(is), end;
	std::vector<int> v(start, end);
	std::cout << "Read " << v.size() << " numbers" << std::endl;
	system("pause");

	/* for (int i = 0; i<v.size(); i++)
	std::cout << v[i] << ' '; */
	cout << endl;

	clock_t tStart = clock();

	v = merge_sort(v);

	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	/* for (int i = 0; i < v.size(); i++)
	std::cout << v[i] << ' '; */
	cout << endl;
	cout << "Inversões: " << contaInversoes << endl;

	system("pause");
	return 0;
}

//! \brief Performs a recursive merge sort on the given vector
//! \param vec The vector to be sorted using the merge sort
//! \return The sorted resultant vector after merge sort is
//! complete.
vector<int> merge_sort(vector<int>& vec)
{
	// Termination condition: List is completely sorted if it
	// only contains a single element.
	if (vec.size() == 1)
	{
		return vec;
	}

	// Determine the location of the middle element in the vector
	std::vector<int>::iterator middle = vec.begin() + (vec.size() / 2);

	vector<int> left(vec.begin(), middle);
	vector<int> right(middle, vec.end());

	// Perform a merge sort on the two smaller vectors
	left = merge_sort(left);
	right = merge_sort(right);

	return mymerge(vec, left, right);
}

//! \brief Merges two sorted vectors into one sorted vector
//! \param left A sorted vector of integers
//! \param right A sorted vector of integers
//! \return A sorted vector that is the result of merging two sorted
//! vectors.
vector<int> mymerge(vector<int> &vec, const vector<int>& left, const vector<int>& right)
{
	// Fill the resultant vector with sorted results from both vectors
	vector<int> result;
	unsigned left_it = 0, right_it = 0;

	while (left_it < left.size() && right_it < right.size())
	{
		// If the left value is smaller than the right it goes next
		// into the resultant vector
		if (left[left_it] <= right[right_it])
		{
			result.push_back(left[left_it]);
			left_it++;
		}
		else
		{
			result.push_back(right[right_it]);
			right_it++;
			contaInversoes += (left.size() - left_it);
			/* cout << contaInversoes << endl; */

		}
	}

	// Push the remaining data from both vectors onto the resultant
	while (left_it < left.size())
	{
		result.push_back(left[left_it]);
		left_it++;
	}

	while (right_it < right.size())
	{
		result.push_back(right[right_it]);
		right_it++;
	}
	//show merge process..
	//int i;
	//for (i = 0; i<result.size(); i++)
	//{
	//	cout << result[i] << " ";
	//}
	// break each line for display purposes..
	//cout << "***********" << endl;

	//take a source vector and parse the result to it. then return it.  
	vec = result;
	return vec;
}
