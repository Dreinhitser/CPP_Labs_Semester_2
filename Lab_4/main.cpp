#include <iostream>

//������� 1
//�������� ������
//�������� �����

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};

void addNode(Node*& root, int data)
{
	//��� ������ �������, �� ������� ������� �� ������ root
	if (root == nullptr)
	{
		root = new Node;

		root->data = data;
		root->parent = nullptr;
		root->left = nullptr;
		root->right = nullptr;
	}
	//���� ������ ���������, �� ���� ����� ��� �������� ������ ��������
	else
	{
		//node - ����������� ����
		Node* node = root;
		//prevNode - �������� ������������ ����
		Node* prevNode = nullptr;

		//���������� �� ������, ���� �� ������� � "�������" �������
		do
		{
			prevNode = node;

			if (data < node->data)
				node = node->left;
			else
				node = node->right;
		} while (node != nullptr);

		node = new Node;

		//� ����������� �� ����, � ����� �������� ������� prevNode'� �� ����������,
		//��������� prevNode ������ �� ����� �������
		if (data < prevNode->data)
			prevNode->left = node;
		else
			prevNode->right = node;

		//��������� ���� ������ ��������
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
	//���� ��������� ���� ����� ��� �������� ��������
	else
	{
		//��������� ���� ����� �������� ����� �� ����� ��� ������� ���������,
		//� ������� ��� ������ ��������� ����
		Node* node = nodeToDeleted->right;
		
		//������� ���� ��� ������
		while (node->left != nullptr)
		{
			node = node->left;
		}

		//������ ������ ���, ��� ����� ���������� ���� ���.
		//�.�. �������� ����� ��������� �� �������� �������, ����� ���������
		if (node->right != nullptr)
		{
			node->right->parent = node->parent;
			node->parent->left = node->right;
		}

		//�������� ��������� ������� ���������
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