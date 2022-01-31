#include "dataset.h"

//Создает файл с maxLines количеством строк, в которых 3 случайных символа
void generateDataset(const std::string filename, const int maxLines)
{
	std::ofstream output(filename);

	if (output.is_open())
	{
		//Настраиваем seed для rand
		std::srand(static_cast<unsigned>(std::time(nullptr)));

		// 'A' = 65, 'Z' = 90, 90 - 65 = 25 + 1
		const int startSymbol = 65;
		// 'Z' = 90
		const int endSymbol = 90;
		const int different = endSymbol - startSymbol + 1;

		for (int line = 0; line < maxLines; line++)
		{
			output << static_cast<char>(std::rand() % different + startSymbol);
			output << static_cast<char>(std::rand() % different + startSymbol);
			output << static_cast<char>(std::rand() % different + startSymbol);
			output << std::endl;
		}

		output.close();
	}
	else
	{
		std::cerr << "Error: (generateDataset) output file not created";
	}
}

//Создает файл, который содержит данные файла filename в отсортированном по убыванию виде
int sortDataset(const std::string filename)
{
	int iterations = 0;

	std::ifstream input(filename);

	if (input.is_open())
	{
		//В векторе будем хранить символы из входного файла
		std::vector<char> symbols;
		char symbol;
		
		//Считываем символы в вектор
		while (input)
		{
			input >> symbol;
			symbols.push_back(symbol);
		}

		input.close();
		
		//Сортируем вектор по убыванию
		for (int i = 0; i < symbols.size() - 1; i++)
		{
			for (int j = i + 1; j < symbols.size(); j++)
			{
				if (symbols[i] < symbols[j])
				{
					char temp = symbols[i];
					symbols[i] = symbols[j];
					symbols[j] = temp;

					iterations++;
				}
			}
		}

		//Генерируем название выходного файла. input.txt --> input.sort.txt
		// ".txt"
		const int countExtensionSymbols = 4;
		std::string outFilename = filename;
		outFilename.insert(outFilename.length() - countExtensionSymbols,
			".sort");

		std::ofstream output(outFilename);

		//Записываем в выходной файл отсортированный массив
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
