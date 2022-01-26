#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "dataset.h"

int main()
{
	const int minLines = 8;
	const int maxLines = 4096;
	const int step = 2;

	std::ofstream output("table.txt");

	if (output.is_open())
	{
		output << "Lines	T(e)	T(1)	T(2)	T(e)/T(1)	T(e)/T(2)" <<
			std::endl;

		double tE;
		double t1;
		double t2;
		const std::string outFilename = "out.txt";

		for (int lines = minLines; lines <= maxLines; lines *= step)
		{
			generateDataset(outFilename, lines);
			tE = sortDataset(outFilename);
			t1 = lines * lines;
			t2 = lines * std::log2(lines);

			output << lines << "\t" << tE << "\t" << t1 << "\t" << t2 <<
				"\t" << tE / t1 << "\t" << tE / t2 << std::endl;
		}

		output.close();
	}

	return 0;
}