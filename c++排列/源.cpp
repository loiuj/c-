// ReSharper disable All
#include <iostream>
using namespace std;
#include <string.h>
#include "sort_relize.cpp"
#include "compare.h"
// ReSharper disable once CppParameterMayBeConst
void PrintList(const int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
}

class Person
{
public:
	Person(string name, const int age) :name_(move(name)), age_(age)
	{
	}

	Person()
	{
		name_ = "\0";
		age_ = 0;
	}

	void Print() const
	{
		cout << "姓名： " << name_ << "\t年龄：" << age_ << endl;
	}
	int GetAge() const
	{
		return age_;
	}
	string GetName()
	{
		return name_;
	}

	void operator=(Person& p)
	{
		name_ = p.name_;
		age_ = p.age_;
	}



private:
	string name_;
	int age_;
};
bool Compare(const Person& p1, const Person& p2)
{
	return p1.GetAge() <= p2.GetAge();
}

int num[10] = { 3,5,10,16,7,32,83,23,54,29 };
Person persons[5] = { Person("张三",10),Person("李四",50),Person("王五",30),Person("小明",4),Person("小王",12) };

void SortInsertText()
{
	//测试分割排序，为了希尔排序而改装
	SortDirect(num, 10, Compare, 3);
	SortDirect(persons, 5, Compare);
	for (int i = 0; i < 5; i++)
	{
		persons[i].Print();
	}
	PrintList(num, 10);
}

void BInsertSortText()
{
	BInsertSort(num, 10, Compare);
	SortDirect(persons, 5, Compare);
	for (int i = 0; i < 5; i++)
	{
		persons[i].Print();
	}
	PrintList(num, 10);
}

void ShellSortText()
{
	int dlta[] = { 5,3,1 };
	ShellSort<int>(num, 10, Compare, dlta, 3);
	ShellSort<Person>(persons, 5, Compare, dlta, 3);
	for (int i = 0; i < 5; i++)
	{
		persons[i].Print();
	}
	PrintList(num, 10);
}

void BubbleSortText()
{
	BubbleSort(num, 10, Compare);
	BubbleSort(persons, 5, Compare);
	for (int i = 0; i < 5; i++)
	{
		persons[i].Print();
	}
	PrintList(num, 10);
}

void QSortText()
{
	QSort(num, 0, 9, Compare);
	QSort(persons, 0, 5, Compare);
	for (int i = 0; i < 5; i++)
	{
		persons[i].Print();
	}
	PrintList(num, 10);
}

void SelectSortText()
{
	SelectSort(num, 10, Compare);
	SelectSort(persons, 5, Compare);
	for (int i = 0; i < 5; i++)
	{
		persons[i].Print();
	}
	PrintList(num, 10);
}


void HeapSortText()
{
	HeapSort(num, 10, Compare);
	HeapSort(persons, 5, Compare);
	for (int i = 0; i < 5; i++)
	{
		persons[i].Print();
	}
	PrintList(num, 10);
}

void MergeSortText()
{
	int* t;
	t = MergeSort(num, 10,Compare);
	Person* person = MergeSort(persons, 5, Compare);
	PrintList(t, 10);
	for (int i = 0; i < 5; i++)
	{
		person[i].Print();
	}
}

//int main()
//{
//	//SortInsertText();
//	//BInsertSortText();
//	//ShellSortText();
//	//BubbleSortText();
//	//QSortText();
//	//SelectSortText();
//	//HeapSortText();
//	MergeSortText();
//	return 0;
//}
