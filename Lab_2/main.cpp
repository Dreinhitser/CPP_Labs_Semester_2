#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "dataset.h"

//17 вариант

int main()
{
	const int minLines = 8;
	const int maxLines = 4096;
	const int step = 2;

	std::ofstream output("table.txt");

	if (output.is_open())
	{
		output << "Lines\t  T(e)\t   T(1)\t  T(2)\t T(e)/T(1)\t T(e)/T(2)" <<
			std::endl;

		long long tE;
		long long t1;
		double t2;
		const std::string outFilename = "out.txt";

		for (int lines = minLines; lines <= maxLines; lines *= step)
		{
			generateDataset(outFilename, lines);
			tE = sortDataset(outFilename);
			t1 = lines * lines;
			t2 = lines * std::log2(lines);

			// +- красивый вывод таблицы
			output.setf(std::ios::fixed);
			output << std::setprecision(3);

			output << std::setw(5) << lines << " " << std::setw(8) <<
				tE << " " << std::setw(8) << t1 << " " << std::setw(6) <<
				static_cast<long long>(t2) << " " << std::setw(11) <<
				static_cast<double>(tE) / t1 << "  " << std::setw(4) <<
				"  " << tE / t2 << std::endl;
		}

		output.close();
	}
	else
	{
		std::cerr << "Error: table file not created";
	}

	return 0;
}
