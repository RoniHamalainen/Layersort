#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <random>
#include <functional>
#include <sstream>

typedef std::vector<int> list;
typedef std::vector<list> matrix;

int GetMaxium(list sortme)
{
	int maxium = sortme.at(0);
	for (unsigned int i = 0; i < sortme.size(); i++)
	{
		int currentValue = sortme.at(i);
		if (currentValue > maxium)
			maxium = currentValue;
	}
	return maxium;
}

int GetMinium(list sortme)
{
	int minium = sortme.at(0);
	for (unsigned int i = 0; i < sortme.size(); i++)
	{
		int currentValue = sortme.at(i);
		if (currentValue < minium)
			minium = currentValue;
	}
	return minium;
}

list ColumnSums(matrix m)
{
	const int ylength = m.size();
	const int xlength = m.at(0).size();
	list columnSums(xlength);
	list::iterator listIterator;

	for (int x = 0; x < xlength; x++)
	{
		int columnSum = 0;
		for (int y = 0; y < ylength; y++)
			columnSum += m.at(y).at(x);
		columnSums.at(x) = columnSum;
	}
	return columnSums;
}

list lsort(list sortme)
{	
	const int minium = GetMinium(sortme);
	const int maxium = GetMaxium(sortme);

	const int xlength = sortme.size();
	const int ylength = maxium - minium + 1;

	const int offset = std::abs(minium);

	// create list of integers + offset
	list offsetList(xlength);
	for (int x = 0; x < xlength; x++)
		offsetList.at(x) = sortme.at(x) + offset;

	// create column matrix
	matrix m(xlength, list(ylength));
	for (int i = 0; i < xlength; i++)
	{
		int value = offsetList.at(i);
		list row(ylength, 0);
		for (int j = 0; j < value; j++)
			row.at(j) = 1;
		m.at(i) = row;
	}

	// get column sums
	list columnSums = ColumnSums(m);

	// create pushed matrix
	matrix pm(ylength, list(xlength));
	for (int y = 0; y < ylength; y++)
	{
		list row(xlength, 0);
		int sum = columnSums.at(y);

		// start at right
		int istart = xlength - 1;
		for (; sum != 0; sum--)
		{
			row.at(istart) = 1;
			istart--;
		}

		pm.at(y) = row;
	}

	// calculate column sums
	list sorted = ColumnSums(pm);

	// calculate actual values
	for (auto i = sorted.begin(); i != sorted.end(); ++i)
		*i -= offset;

	return sorted;
}

int main(unsigned int argc, char* argv[])
{	
	if (argc == 0)
	{
		std::cout << "Error! No arguments\n";
	}
	else if (argc == 1)
	{
		std::cout << "Error! Too few arguments\n";
	}
	else if (argc == 2)
	{
		std::cout << "Only one argument\n";
		std::cout << argv[1] << "\n";
	}
	else
	{
		// list with length of n arguments - program name
		list sortme(argc - 1);

		// iterate every command line argument except program name
		for (unsigned int i = 1; i < argc; i++)
		{
			// convert command line argument to integer
			std::istringstream ss(argv[i]);
			int x;
			if (!(ss >> x))
				std::cerr << "Invalid number " << argv[i] << "\n";

			sortme.at(i - 1) = x;
		}

		// layer sort - algorithm
		list sorted = lsort(sortme);

		// print out sorted list
		std::cout << "Sorted:\n";
		for (auto i = sorted.begin(); i != sorted.end(); ++i)
			std::cout << *i << " ";
		std::cout << "\n";
	}

	// wait for user input before closing the application
	char c;
	std::cin >> c;
	
	return 0;
}

// 20:01
// 25.11.2016
// Algorithm finally works

// 11.59
// 07.12.2016
// Overall fixing
// added GetMaxium and GetMinium functions
