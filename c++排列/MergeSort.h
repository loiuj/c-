#pragma once
//归并排序
//时间复杂度o(nlogn)
//空间复杂度o(n)
//稳定的排序算法
//如果想稳定的话得设置compare的比较
template<typename T>
T* MergeSort(T* a, int n, bool compare(const T&, const T&));

//普通的两个有序数组合并一个有序数组
//归并是对两个已经有序的数组进行排序，我们需要开辟一个数组用来存储结果，我们先比较两个数组第一个元素，假设是从小到大，那么谁小谁为第一个，然后那个数组指向第二元素
//因为两个数组已经有序，那么两个数组第一个元素中最小的那个肯定是整体中最小的那个，然后取完的可以理解为挪到了之前开辟的数组，也就是存储结果的数组中，然后再比较两个数组第一个元素
template<typename T>
void MergeArrangeSort(T* array, int start, int a_len, int b_len, T* tmp, bool compare(const T&, const T&))
{
	int p1 = start + a_len - 1, p2 = start + b_len - 1;
	int tail = p2;
	while (p1 >= start || p2 >= start + a_len) {
		if (p1 == start - 1) {
			tmp[tail--] = array[p2--];
		}
		else if (p2 == start + a_len - 1) {
			tmp[tail--] = array[p1--];
		}
		else if (compare(array[p1], array[p2])) {
			tmp[tail--] = array[p1--];
		}
		else {
			tmp[tail--] = array[p2--];
		}
	}
}


template<typename T>
T* MergeSort(T* a, int n, bool compare(const T&, const T&))
{

	for (int j = 1; j < n; j *= 2)
	{
		T* tmp = new T[n];
		int i;
		for (i = 0; i < n; i += 2 * j)
		{
			//三目运算是为了多余的也能放在新数组里面
			MergeArrangeSort(a, i, i + j < n ? j : n - i, i + 2 * j < n ? 2 * j : n - i, tmp, compare);
		}
		a = tmp;
	}
	return a;
}