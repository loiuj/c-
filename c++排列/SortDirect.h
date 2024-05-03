#pragma once
//直接插入排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//稳定的排序方法
template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump = 1);

template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump)
{
	T compare_num = a[1];
	int j;
	//我们从第0个开始存储，没有哨兵位，所以直接从第1个开始
	for (int i = jump; i < n; i += jump)
	{
		compare_num = a[i];
		if (compare(a[i - jump], compare_num))
		{
			//设置i-1防止第一次匹配的时候会与自己匹配
			for (j = i - jump; compare(a[j], compare_num) && j >= 0; j -= jump)
				a[j + jump] = a[j];
			a[j + jump] = compare_num;
		}
	}
}