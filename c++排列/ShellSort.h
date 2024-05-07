#pragma once
#include "SortDirect.h"
//希尔排序
//时间复杂度o(n^1.25)~o(1.6n^1.25)
//空间复杂度o(1)
//不稳定的排序方法
//dlta 排序的序列因子，t位dlta的长度
//注意：传入的最后一个增量必须为1
template<typename T>
void ShellSort(T* a, int length, bool compare(const T&, const T&), int* dlta, const int t);

//应该不怎么用，不好掌握运算时间
//就是分块来排序，然后越有规律直接排序就可以越快，因为插入排序越有序越快，希尔就是先让他尽可能有序然后再进行排序
template<typename T>
void ShellSort(T* a, int length, bool compare(const T&, const T&), int* dlta, const int t)
{
	//按照步长先进行排序
	for (int k = 0; k < t; k++)
	{
		//改版，主要懒得写，0-dlta[k]中排序相当于整个排序了
		for (int i = 0; i < dlta[k]; i++)
		{
			SortDirect(a, length, compare, dlta[k]);
		}
	}
}