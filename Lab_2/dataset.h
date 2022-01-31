#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

//Создает файл с maxLines количеством строк, в которых 3 случайных символа
void generateDataset(const std::string filename, const int maxLines);

//Создает файл, который содержит данные файла filename в отсортированном по убыванию виде
int sortDataset(const std::string filename);

#endif // !DATASET_H
