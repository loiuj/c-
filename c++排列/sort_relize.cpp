#include "sort_type.h"

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


template<typename T>
void BInsertSort(T* a, int n, bool compare(const T&, const T&))
{
	T compare_num = a[0];
	int low, high, mid;
	for (int i = 1; i < n; i++)
	{
		compare_num = a[i];
		low = 0;
		high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (compare(a[mid], compare_num))high = mid - 1;
			else low = mid + 1;
		}
		int j;
		for (j = i - 1; j > high; j--)a[j + 1] = a[j];
		a[j + 1] = compare_num;
	}
}

//应该不怎么用，不好掌握运算时间
//就是分块来排序，然后越有规律直接排序就可以越快
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


template<typename T>
int Parition(T* a, int low, int high, bool compare(const T&, const T&))
{
	//为了不占用太多空间
	T compare_num = a[low];
	while (low < high)
	{
		//因为low的地方先被用来占用了,所以从high开始
		while (low < high && compare(a[high], compare_num)) high--;
		a[low] = a[high];
		while (low < high && compare(compare_num, a[low])) low++;
		a[high] = a[low];
	}
	a[low] = compare_num;
	return low;
}

//将小于的放在前面，大于的放在后面
template<typename T>
void QSort(T* a, int low, int high, bool compare(const T&, const T&))
{
	//如果不满足则代表每块只有一个，所以不用排直接退出
	if (low < high)
	{
		//返回中间值再进行分块排序
		const int pivotal = Parition(a, low, high, compare);
		QSort(a, low, pivotal - 1, compare);
		QSort(a, pivotal + 1, high, compare);
	}
}

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

//已知R[s..m]中记录的关键字除R[s]外均满足堆的定义，本函数调整R[s]的关键字,使R[s..m]成为一个大根堆
//s,m都为索引对应的下标
template<typename T>
void HeapAdjust(T* a, int s, int m, bool compare(const T&, const T&))
{
	//此算法可看为完全二叉树，如果大跟堆则父节点都比子节点要大
	T rc = a[s];
	//当前节点的索引乘以2，就是其的左孩子的索引，完全二叉树的性质
	//由于我们以0为第一个，所以索引应该是乘以2加1
	for (int j = s * 2 + 1; j <= m; j = 2 * j + 1)//因为j可以等于m代表j为那个节点，此时也要进行下面s的赋值操作
	{
		if (j < m&& compare(a[j + 1], a[j]))++j;//j必须小于m,不然j+1会报错,&&确定前面报错了后面就不会执行，所以不用担心
		if (compare(rc, a[j]))break;//加上等于可以少走一次，但为了可以传入的compare不用考虑等于返回true，但这样每次能少算一次相等，中和下来没什么损耗应该
		a[s] = a[j];
		s = j;
	}
	a[s] = rc;
}

//相对较难理解部分做法
template<typename T>
void HeapSort(T* a, const int n, bool compare(const T&, const T&))
{
	int index = n - 1;//下面每次n都要减一就用index存了
	for (int i = (index - 1) / 2; i >= 0; i--)//这里也可以用(n/2)-1，只是用了index就写他吧
	{
		HeapAdjust(a, i, index, compare);
	}
	//因为假设是s小根堆，那么第一个一定是最小的，所以把他放到最后，然后剩下的再调整，因为最后一个到了第一个
	for (int i = n - 1; i > 0; i--)
	{
		T tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;
		HeapAdjust(a, 0, i - 1, compare);
	}
}

//普通的两个有序数组合并一个有序数组
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

