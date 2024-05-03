#pragma once
//直接选择排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//不稳定的排序方法
//时间复杂度相较于冒泡排序快
template<typename T>
void SelectSort(T* a, int n, bool compare(const T&, const T&));

//相当于冒泡排序，只不过不是每次两个都交互而变成了每趟只交换一次
template<typename T>
void SelectSort(T* a, int n, bool compare(const T&, const T&))
{
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		k = i;
		for (int j = i + 1; j < n; j++)
			if (compare(a[k], a[j])) k = j;
		if (k != i)
		{
			T tmp = a[k];
			a[k] = a[i];
			a[i] = tmp;
		}
	}
}