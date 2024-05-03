#pragma once

//冒泡排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//稳定的排序方法
template<typename T>
void BubbleSort(T* a, int n, bool compare(const T&, const T&));

//冒泡排序，无需多言
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