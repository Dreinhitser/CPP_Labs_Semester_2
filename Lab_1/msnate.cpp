#include "msnate.h"

double function(double x)
{
	return x * x - log(4 * x);
}

std::vector<std::pair<double, double>> generateSegmentsTable()
{
	using namespace constants;

	std::vector<std::pair<double, double>> valueTable;

	for (double x = xMinValue; x <= xMaxValue; x += xStep)
	{
		valueTable.push_back(std::make_pair(x, function(x)));
	}

	std::vector<std::pair<double, double>> segmentsTable;
	std::vector<std::pair<double, double>>::iterator it = valueTable.begin();
	double previousX = it->first;

	//true is +; false is -
	bool previousValueSign = it->second >= 0 ? true : false;
	it++;

	while (it != valueTable.end())
	{
		if ((it->second >= 0 && !previousValueSign) ||
			(it->second < 0 && previousValueSign))
		{
			segmentsTable.push_back(std::make_pair(previousX, it->first));
			previousX = it->first;
			previousValueSign = it->second >= 0 ? true : false;
		}

		it++;
	}

	return segmentsTable;
}

std::vector<double> halfDivision
(
	const std::vector<std::pair<double, double>>& segmentsTable,
	int* iterations
)
{
	std::vector<double> roots;
	int iterationsCount = 0;

	if (segmentsTable.size())
	{
		double firstX;
		double secondX;
		double averageX;

		double firstXFunctionValue;
		double secondXFunctionValue;
		double averageXFunctionValue;

		for (const auto& it : segmentsTable)
		{
			firstX = it.first;
			secondX = it.second;
			averageX = (firstX + secondX) / 2;

			firstXFunctionValue = function(firstX);
			secondXFunctionValue = function(secondX);
			averageXFunctionValue = function(averageX);

			while (abs(averageXFunctionValue) >= constants::eps)
			{
				if ((firstXFunctionValue >= 0 && averageXFunctionValue < 0) ||
					(firstXFunctionValue < 0 && averageXFunctionValue >= 0))
				{
					secondX = averageX;
					secondXFunctionValue = averageXFunctionValue;
				}
				else
				{
					firstX = averageX;
					firstXFunctionValue = averageXFunctionValue;
				}

				averageX = (firstX + secondX) / 2;
				averageXFunctionValue = function(averageX);

				iterationsCount++;
			}

			roots.push_back(averageX);
		}		
	}

	if (iterations)
		*iterations = iterationsCount;

	return roots;
}

std::vector<double> chord
(
	std::vector<std::pair<double, double>>& segmentsTable,
	int* iterations
)
{
	std::vector<double> roots;
	int iterationsCount = 0;

	if (segmentsTable.size())
	{
		double firstX;
		double secondX;
		double crossX;

		double firstXFunctionValue;
		double secondXFunctionValue;
		double crossXFunctionValue;

		for (const auto& it : segmentsTable)
		{
			firstX = it.first;
			secondX = it.second;
			
			firstXFunctionValue = function(firstX);
			secondXFunctionValue = function(secondX);

			crossX = (firstX * secondXFunctionValue -
				secondX * firstXFunctionValue) /
				(secondXFunctionValue - firstXFunctionValue);
			crossXFunctionValue = function(crossX);

			while (abs(crossXFunctionValue) >= constants::eps)
			{
				if ((firstXFunctionValue >= 0 && crossXFunctionValue < 0) ||
					(firstXFunctionValue < 0 && crossXFunctionValue >= 0))
				{
					secondX = crossX;
					secondXFunctionValue = crossXFunctionValue;
				}
				else
				{
					firstX = crossX;
					firstXFunctionValue = crossXFunctionValue;
				}

				crossX = (firstX * secondXFunctionValue -
					secondX * firstXFunctionValue) /
					(secondXFunctionValue - firstXFunctionValue);
				crossXFunctionValue = function(crossX);

				iterationsCount++;
			}

			roots.push_back(crossX);
		}
	}

	if (iterations)
		*iterations = iterationsCount;

	return roots;
}