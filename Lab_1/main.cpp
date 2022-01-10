#include <iostream>
#include <cmath>
#include <vector>

//17 �������
double function(double x)
{
	return x * x - log(4 * x);
}

//������ ������� ��������� ������� ��������� x � function(x),
//��� ���� ������� ������ �� �������� (x, function(x)),
//� ������� function(x) ����� �������������� ���� �� ����������
//�� ��������� � ������� function(x)
void generateValueTable(std::vector<std::pair<double, double>>& segmentsTable,
	const double minValueX, const double maxValueX, const double stepX)
{
	std::vector<std::pair<double, double>> valueTable;

	for (double x = minValueX; x <= maxValueX; x += stepX)
	{
		valueTable.push_back(std::make_pair(x, function(x)));
	}

	//true ���������� +; false ���������� -
	bool prevSign;

	std::vector<std::pair<double, double>>::iterator it = valueTable.begin();

	//��������� ������ ���� �������� � ������� ��������
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

	generateValueTable(segmentsTable, minValueX, maxValueX, stepX);

	return 0;
}