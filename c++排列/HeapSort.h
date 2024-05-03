#pragma once
//堆排序
//时间复杂度o(nlogn)
//空间复杂度o(1)
//不稳定的排序方式，但对记录次序无关，适用于较大的文件
template<typename T>
void HeapSort(T* a, int n, bool compare(const T&, const T&));

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