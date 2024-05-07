#pragma once

//冒泡排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//稳定的排序方法
template<typename T>
void BubbleSort(T* a, int n, bool compare(const T&, const T&));

//冒泡排序，从后往前(或从前往后)两两比较相邻元素的值，若为逆序，则交换它们，直到序列比较完。称这样过程为“一趟”冒泡排序。
//也就是把每趟要的数字推到前面，比如从大到小，那么就把最小的带到最后
template<typename T>
void BubbleSort(T* a, int n, bool compare(const T&, const T&))
{
	bool flag = true;
	for (int i = n - 1; i > 0 && flag; i--)
	{
		flag = false;
		for (int j = 0; j < i; j++)
		{
			if (compare(a[j], a[j + 1]))
			{
				T tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				flag = true;
			}
		}
	}
}