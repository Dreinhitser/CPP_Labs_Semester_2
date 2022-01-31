#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

//17 вариант

struct Node
{
	int data = 0;
	struct Node* previous = nullptr;
	struct Node* next = nullptr;
};

void push(Node*& root, int data)
{
	if (root)
	{
		Node* newRoot = new Node;
		
		newRoot->data = data;
		newRoot->next = root;

		root->previous = newRoot;
		root = newRoot;
	}
	else
	{
		root = new Node;
		root->data = data;
	}
}

void deleteLast(Node*& root)
{
	if (!root->next)
	{
		delete root;
		root = nullptr;
	}
	else if (root)
	{
		Node* node = root;

		while (node->next)
		{
			node = node->next;
		}

		node->previous->next = nullptr;
		delete node;
	}
}

Node* find(Node* root, int dataFinding)
{
	if (root)
	{
		while (root->data != dataFinding && root->next)
		{
			root = root->next;
		}

		if (root->data == dataFinding)
			return root;
		else
			return nullptr;
	}
	else
	{
		return nullptr;
	}
}

void print(Node* root)
{
	while (root)
	{
		std::cout << root->data << std::endl;
		root = root->next;
	}
}

void generateDataset(std::string filename, const int maxLines)
{
	std::ofstream output(filename);

	if (output.is_open())
	{
		std::srand(static_cast<unsigned>(std::time(nullptr)));

		const int numbersInLine = 5;

		for (int lines = 0; lines < maxLines; lines++)
		{
			for (int i = 0; i < numbersInLine; i++)
			{
				output << rand() % 100 << " ";
			}
			output << std::endl;
		}

		output.close();
	}
	else
	{
		std::cerr << "Error: (generateDataset) file not created" << std::endl;
	}
}

int main()
{
	const std::string filename = "in.txt";
	const int maxLines = 2;

	generateDataset(filename, maxLines);

	std::ifstream input(filename);

	if (input.is_open())
	{
		Node* root = nullptr;

		int number;

		while (input >> number)
		{
			push(root, number);
		}

		int operation;
		bool exitProgram = false;
		int value;

		while (true)
		{
			std::cout << "1. Add element" << std::endl;
			std::cout << "2. Remove last element" << std::endl;
			std::cout << "3. find element" << std::endl;
			std::cout << "4. print elements" << std::endl;
			std::cout << "5. exit" << std::endl;
			std::cout << "Enter operation (1, 2, 3, 4, 5): ";

			std::cin >> operation;

			switch (operation)
			{
			case 1:
				std::cout << "Enter element value: ";
				std::cin >> value;
				push(root, value);
				break;
			case 2:
				deleteLast(root);
				break;
			case 3:
				std::cout << "Enter element value: ";
				std::cin >> value;
				std::cout << "Pointer: " << find(root, value) << std::endl;
				break;
			case 4:
				print(root);
				break;
			case 5:
				exitProgram = true;
				break;
			default:
				std::cout << "Undefined operation. Try again" << std::endl;
				break;
			}

			if (exitProgram)
				break;
		}
	}
	else
	{
		std::cerr << "Error: input file not opened";
	}

	return 0;
}
