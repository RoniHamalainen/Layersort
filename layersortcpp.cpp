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

list lsort(list sortme)
{	
	int minium = GetMinium(sortme);
	int maxium = GetMaxium(sortme);

	int xlength = sortme.size();
	int ylength = maxium - minium + 1;

	int difference = minium - 1;

	// create reference list
	list referenceList(ylength);
	for (int y = 0; y < ylength; y++)
		referenceList.at(y) = y;

	// create reference map
	std::map<int, int> referenceMap;
	for (int y = 0; y < ylength; y++)
		referenceMap[referenceList.at(y)] = minium + y;

	// create matrix
	matrix m(ylength, list(xlength));
	for (int y = 0; y < ylength; y++)
	{
		list row(xlength, 0);
		for (int x = 0; x < xlength; x++)
			if (sortme.at(x) >= referenceMap[y])
				row.at(x) = 1;
		m.at(y) = row;
	}

	// push to right
	matrix mr(ylength, list(xlength));
	for (int y = 0; y < ylength; y++)
	{
		int rowsum = 0;
		for (int item : m.at(y))
			rowsum += item;

		// create row reversed
		int rowend = xlength - 1;
		list reversedRow(xlength);
		for (int i = rowend; i != rowend - rowsum; i--)
			reversedRow.at(i) = 1;
		mr.at(y) = reversedRow;
	}

	// calculate column sums
	list sorted(xlength);
	for (int x = 0; x < xlength; x++)
		for (int y = 0; y < ylength; y++)
			sorted.at(x) += mr.at(y).at(x);

	// calculate actual values
	for (auto i = sorted.begin(); i != sorted.end(); ++i)
		*i += difference;

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
