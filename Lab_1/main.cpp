#include <iostream>
#include <cmath>
#include <vector>

//17 вариант
double function(double x)
{
	return x * x - log(4 * x);
}

//Fill table values of x and function(x)
//in this case only those values x and function(x) are taken
//for which function(x) has the opposite sign
//compared to the previous function(x)
void generateSegmentsTable(std::vector<std::pair<double, double>>& segmentsTable,
	const double minValueX, const double maxValueX, const double stepX)
{
	std::vector<std::pair<double, double>> valueTable;

	for (double x = minValueX; x <= maxValueX; x += stepX)
	{
		valueTable.push_back(std::make_pair(x, function(x)));
	}

	//true is +; false is -
	bool prevSign;

	std::vector<std::pair<double, double>>::iterator it = valueTable.begin();

	//Transfer the first pair of values to the segment table
	segmentsTable.push_back(std::make_pair(it->first, it->second));
	prevSign = it->second >= 0 ? true : false;
	it++;

	while (it != valueTable.end())
	{
		if ((it->second >= 0 && !prevSign) || (it->second < 0 && prevSign))
		{
			segmentsTable.push_back(std::make_pair(it->first, it->second));
		}

		if (it->second >= 0)
			prevSign = true;
		else
			prevSign = false;

		it++;
	}

}

int main()
{
	const double minValueX = 0.05;
	const double maxValueX = 3.0;
	const double stepX = 0.05;

	std::vector<std::pair<double, double>> segmentsTable;

	generateSegmentsTable(segmentsTable, minValueX, maxValueX, stepX);

	return 0;
}