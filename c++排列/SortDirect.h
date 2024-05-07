#pragma once
//直接插入排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//稳定的排序方法
template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump = 1);

//将后面的数据插入到前面有序数组中合适的位置，需要挪到数组元素
//这里jump是因为希尔排序也用到了，直接排序的时候jump就是1
template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump)
{
	T compare_num = a[1];
	int j;
	//我们从第0个开始存储，没有哨兵位，所以直接从第1个开始，因为开始只有一个元素，其就是有序的跳过，从1开始
	for (int i = jump; i < n; i += jump)
	{
		compare_num = a[i];
		//反正从1开始-1也是匹配0，没有问题还能避免要多匹配一次自身
		for (j = i - jump; compare(a[j], compare_num) && j >= 0; j -= jump)
			a[j + jump] = a[j];
		a[j + jump] = compare_num;
	}
}