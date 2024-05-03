#include <iomanip>

#include "红黑树.h"
#include <time.h>
#include <random>

//测试添加
void Test01()
{
	RBTree* tree = new RBTree();
	int count = 0;
	system("color f0");
	while (true)
	{
		scta(0xf0);
		cout << "输入插入的数值" << ":";
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

//测试删除
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
		cout << "输入插入的删除key" << ":";
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

//奇奇怪怪错误的测试
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
	cout << "***1 插入  2删除   其他退出 ***" << endl;
	cout << "*******************************" << endl;
}

//正常调试，能插入和删除
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
		cout << "输入操作的数值" << ":";
		cin >> opertaion;
		int input_num = 0;
		switch (opertaion)
		{
		case 1:
			cout << "输入插入的key" << ":";
			cin >> input_num;
			tree->push(input_num);
			break;
		case 2:
			cout << "输入删除的key" << ":";
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