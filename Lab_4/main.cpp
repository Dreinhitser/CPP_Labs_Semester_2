#include <iostream>

//Вариант 1
//Бинарное дерево
//Обратный обход

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};

void addNode(Node*& root, int data)
{
	//Есл корень нулевой, то создаем элемент по адресу root
	if (root == nullptr)
	{
		root = new Node;

		root->data = data;
		root->parent = nullptr;
		root->left = nullptr;
		root->right = nullptr;
	}
	//Если корень ненулевой, то ищем место для создания нового элемента
	else
	{
		//node - создаваемый узел
		Node* node = root;
		//prevNode - родитель создаваемого узла
		Node* prevNode = nullptr;

		//Спускаемся по дереву, пока не попадем в "нулевой" элемент
		do
		{
			prevNode = node;

			if (data < node->data)
				node = node->left;
			else
				node = node->right;
		} while (node != nullptr);

		node = new Node;

		//В зависимости от того, в какой дочерний элемент prevNode'а мы спустились,
		//заполняем prevNode ссылку на новый элемент
		if (data < prevNode->data)
			prevNode->left = node;
		else
			prevNode->right = node;

		//Заполняем поля нового элемента
		node->parent = prevNode;
		node->left = nullptr;
		node->right = nullptr;
		node->data = data;
	}
}

Node* find(Node* root, int data)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else if (root->data == data)
	{
		return root;
	}
	else
	{
		while (root != nullptr && root->data != data)
		{
			if (data < root->data)
				root = root->left;
			else
				root = root->right;
		}

		return root;
	}
}

void deleteNode(Node* root, Node* nodeToDeleted)
{
	Node* parent = nodeToDeleted->parent;

	if (nodeToDeleted->left == nullptr && nodeToDeleted->right == nullptr)
	{
		if (parent->left == nodeToDeleted)
			parent->left = nullptr;
		else
			parent->right = nullptr;

		delete nodeToDeleted;
	}
	else if (nodeToDeleted->left != nullptr && nodeToDeleted->right == nullptr)
	{
		if (parent->left == nodeToDeleted)
			parent->left = nodeToDeleted->left;
		else
			parent->right = nodeToDeleted->left;

		nodeToDeleted->left->parent = parent;
	}
	else if (nodeToDeleted->left == nullptr && nodeToDeleted->right != nullptr)
	{
		if (parent->left == nodeToDeleted)
			parent->left = nodeToDeleted->right;
		else
			parent->right = nodeToDeleted->right;

		nodeToDeleted->right->parent = parent;
	}
	//Если удаляемый узел имеет оба дочерних элемента
	else
	{
		//Удаляемый узел нужно заменить одним из узлов его правого поддерева,
		//у которых нет левого дочернего узла
		Node* node = nodeToDeleted->right;
		
		//Находим узел для замены
		while (node->left != nullptr)
		{
			node = node->left;
		}

		//Меняем ссылки так, как будто найденного узла нет.
		//Т.е. родитель будет ссылаться на дочерний элемент, минуя найденный
		if (node->right != nullptr)
		{
			node->right->parent = node->parent;
			node->parent->left = node->right;
		}

		//Заменяем удаляемый элемент найденным
		node->left = nodeToDeleted->left;
		node->right = nodeToDeleted->right;
		node->left->parent = node;
		node->right->parent = node;
		node->parent = parent;

		if (parent->left == nodeToDeleted)
			parent->left = node;
		else
			parent->right = node;

		delete nodeToDeleted;
	}

	nodeToDeleted = nullptr;
}

void deleteTree(Node*& root)
{
	if (root != nullptr)
	{
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;

		root = nullptr;
	}
}

void print(Node* root)
{
	if (root != nullptr)
	{
		print(root->left);
		print(root->right);
		std::cout << root->data << std::endl;
	}
}

int main()
{

	return 0;
}