#include <iomanip>

#include "�����.h"
#include <time.h>
#include <random>

//�������
void Test01()
{
	RBTree* tree = new RBTree();
	int count = 0;
	system("color f0");
	while (true)
	{
		scta(0xf0);
		cout << "����������ֵ" << ":";
		int input_num;
		cin >> input_num;
		tree->push(input_num);
		if (count > 2)
		{
			system("cls");
			count = 0;
		}
		tree->PrintRBNode(tree->getRoot());
		count++;
	}
}

//����ɾ��
void Test02()
{
	srand((unsigned int)time(NULL));
	RBTree* tree = new RBTree();
	int count = 0;
	for (int i = 1; i < 10; i++)
	{
		tree->push(i);
	}
	system("color f0");
	tree->remove(8);
	tree->remove(6);
	tree->remove(7);
	while (true)
	{
		scta(0xf0);
		tree->PrintRBNode(tree->getRoot());
		cout << "��������ɾ��key" << ":";
		int input_num;
		cin >> input_num;
		tree->remove(input_num);
		if (count > 2)
		{
			system("cls");
			count = 0;
		}
		count++;
	}
}

//����ִֹ���Ĳ���
void Test()
{
	srand((unsigned int)time(NULL));
	RBTree* tree = new RBTree();

	system("color f0");
	tree->push(6);
	tree->push(7);
	tree->PrintRBNode(tree->getRoot());
	tree->remove(6);
	tree->PrintRBNode(tree->getRoot());
	tree->remove(7);
	tree->PrintRBNode(tree->getRoot());
}

void PrintMenu()
{
	cout << "*******************************" << endl;
	cout << "***1 ����  2ɾ��   �����˳� ***" << endl;
	cout << "*******************************" << endl;
}

//�������ԣ��ܲ����ɾ��
void Test03()
{
	RBTree* tree = new RBTree();
	int opertaion = 1;
	system("color f0");
	while (opertaion)
	{
		scta(0xf0);
		system("cls");
		tree->PrintRBNode(tree->getRoot());

		PrintMenu();
		cout << "�����������ֵ" << ":";
		cin >> opertaion;
		int input_num = 0;
		switch (opertaion)
		{
		case 1:
			cout << "��������key" << ":";
			cin >> input_num;
			tree->push(input_num);
			break;
		case 2:
			cout << "����ɾ����key" << ":";
			cin >> input_num;
			tree->remove(input_num);
			break;
		default:
			opertaion = 0;
		}
	}
}

int main()
{
	//Test01();
	//Test02();
	//Test();
	Test03();
	return 0;
}