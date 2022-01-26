#include "msnate.h"
#include <iostream>
#include <vector>

int main()
{
	auto segmentsTable = generateSegmentsTable();

	for (auto& it : segmentsTable)
		std::cout << "(" << it.first << ";" << it.second << ")" << std::endl;
	std::cout << std::endl;

	int iterations = 0;
	auto roots = halfDivision(segmentsTable, &iterations);

	std::cout << "Half division method: " << std::endl;
	std::cout << "Iterations: " << iterations << std::endl;

	for (auto& it : roots)
		std::cout << "x: " << it << std::endl;

	std::cout << std::endl;

	roots = chord(segmentsTable, &iterations);

	std::cout << "Chord method: " << std::endl;
	std::cout << "Iterations: " << iterations << std::endl;

	for (auto& it : roots)
		std::cout << "x: " << it << std::endl;

	return 0;
}