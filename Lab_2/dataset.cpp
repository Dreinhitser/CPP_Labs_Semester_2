#include "dataset.h"

void generateDataset(const std::string filename, const int maxLines)
{
	std::ofstream output(filename);

	if (output.is_open())
	{
		std::srand(static_cast<unsigned>(std::time(nullptr)));

		// 'A' = 65
		const int startSymbol = 25;
		// 'Z' = 90
		const int endSymbol = 90;
		const int different = endSymbol - startSymbol;

		for (int line = 0; line < maxLines; line++)
		{
			output << static_cast<char>(std::rand() % startSymbol + different);
			output << static_cast<char>(std::rand() % startSymbol + different);
			output << static_cast<char>(std::rand() % startSymbol + different);
			output << std::endl;
		}

		output.close();
	}
	else
	{
		std::cerr << "Error: (generateDataset) output file not created";
	}
}

int sortDataset(const std::string filename)
{
	int iterations = 0;

	std::ifstream input(filename);

	if (input.is_open())
	{
		std::vector<char> symbols;
		char symbol;

		while (input)
		{
			input >> symbol;
			symbols.push_back(symbol);
		}

		input.close();

		for (auto& it1 : symbols)
			for (auto& it2 : symbols)
				if (it1 < it2)
				{
					char temp = it1;
					it1 = it2;
					it2 = temp;

					iterations++;
				}

		// ".txt"
		const int countExtensionSymbols = 4;
		std::string outFilename = filename;
		outFilename.insert(outFilename.length() - countExtensionSymbols,
			".sort");

		std::ofstream output(outFilename);

		if (output.is_open())
		{
			for (auto& it : symbols)
				output << it << std::endl;

			output.close();
		}
		else
		{
			std::cerr << "Error: (sortDataset) output file not created";
		}
	}
	else
	{
		std::cerr << "Error: input file not created";
	}

	return iterations;
}
