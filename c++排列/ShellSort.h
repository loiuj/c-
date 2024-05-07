#pragma once
#include "SortDirect.h"
//ϣ������
//ʱ�临�Ӷ�o(n^1.25)~o(1.6n^1.25)
//�ռ临�Ӷ�o(1)
//���ȶ������򷽷�
//dlta ������������ӣ�tλdlta�ĳ���
//ע�⣺��������һ����������Ϊ1
template<typename T>
void ShellSort(T* a, int length, bool compare(const T&, const T&), int* dlta, const int t);

//Ӧ�ò���ô�ã�������������ʱ��
//���Ƿֿ�������Ȼ��Խ�й���ֱ������Ϳ���Խ�죬��Ϊ��������Խ����Խ�죬ϣ����������������������Ȼ���ٽ�������
template<typename T>
void ShellSort(T* a, int length, bool compare(const T&, const T&), int* dlta, const int t)
{
	//���ղ����Ƚ�������
	for (int k = 0; k < t; k++)
	{
		//�İ棬��Ҫ����д��0-dlta[k]�������൱������������
		for (int i = 0; i < dlta[k]; i++)
		{
			SortDirect(a, length, compare, dlta[k]);
		}
	}
}