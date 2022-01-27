#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

void generateDataset(const std::string filename, const int maxLines);

int sortDataset(const std::string filename);

#endif // !DATASET_H