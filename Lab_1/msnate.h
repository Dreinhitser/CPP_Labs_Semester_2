#ifndef MSNATE_H
#define MSNATE_H

#include "constants.h"
#include <cmath>
#include <vector>

double function(double x);

std::vector<std::pair<double, double>> generateSegmentsTable();

std::vector<double> halfDivision
(
	const std::vector<std::pair<double, double>>& segmentsTable,
	int* iterations = nullptr
);

std::vector<double> chord
(
	std::vector<std::pair<double, double>>& segmentsTable,
	int* iterations = nullptr
);

#endif // !MSNATE_H
