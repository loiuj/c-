#include "sort_type.h"

template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump)
{
	T compare_num = a[1];
	int j;
	//���Ǵӵ�0����ʼ�洢��û���ڱ�λ������ֱ�Ӵӵ�1����ʼ
	for (int i = jump; i < n; i += jump)
	{
		compare_num = a[i];
		if (compare(a[i - jump], compare_num))
		{
			//����i-1��ֹ��һ��ƥ���ʱ������Լ�ƥ��
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

//Ӧ�ò���ô�ã�������������ʱ��
//���Ƿֿ�������Ȼ��Խ�й���ֱ������Ϳ���Խ��
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

//ð�������������
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
	//Ϊ�˲�ռ��̫��ռ�
	T compare_num = a[low];
	while (low < high)
	{
		//��Ϊlow�ĵط��ȱ�����ռ����,���Դ�high��ʼ
		while (low < high && compare(a[high], compare_num)) high--;
		a[low] = a[high];
		while (low < high && compare(compare_num, a[low])) low++;
		a[high] = a[low];
	}
	a[low] = compare_num;
	return low;
}

//��С�ڵķ���ǰ�棬���ڵķ��ں���
template<typename T>
void QSort(T* a, int low, int high, bool compare(const T&, const T&))
{
	//��������������ÿ��ֻ��һ�������Բ�����ֱ���˳�
	if (low < high)
	{
		//�����м�ֵ�ٽ��зֿ�����
		const int pivotal = Parition(a, low, high, compare);
		QSort(a, low, pivotal - 1, compare);
		QSort(a, pivotal + 1, high, compare);
	}
}

//�൱��ð������ֻ��������ÿ�������������������ÿ��ֻ����һ��
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

//��֪R[s..m]�м�¼�Ĺؼ��ֳ�R[s]�������ѵĶ��壬����������R[s]�Ĺؼ���,ʹR[s..m]��Ϊһ�������
//s,m��Ϊ������Ӧ���±�
template<typename T>
void HeapAdjust(T* a, int s, int m, bool compare(const T&, const T&))
{
	//���㷨�ɿ�Ϊ��ȫ�����������������򸸽ڵ㶼���ӽڵ�Ҫ��
	T rc = a[s];
	//��ǰ�ڵ����������2������������ӵ���������ȫ������������
	//����������0Ϊ��һ������������Ӧ���ǳ���2��1
	for (int j = s * 2 + 1; j <= m; j = 2 * j + 1)//��Ϊj���Ե���m����jΪ�Ǹ��ڵ㣬��ʱҲҪ��������s�ĸ�ֵ����
	{
		if (j < m&& compare(a[j + 1], a[j]))++j;//j����С��m,��Ȼj+1�ᱨ��,&&ȷ��ǰ�汨���˺���Ͳ���ִ�У����Բ��õ���
		if (compare(rc, a[j]))break;//���ϵ��ڿ�������һ�Σ���Ϊ�˿��Դ����compare���ÿ��ǵ��ڷ���true��������ÿ��������һ����ȣ��к�����ûʲô���Ӧ��
		a[s] = a[j];
		s = j;
	}
	a[s] = rc;
}

//��Խ�����ⲿ������
template<typename T>
void HeapSort(T* a, const int n, bool compare(const T&, const T&))
{
	int index = n - 1;//����ÿ��n��Ҫ��һ����index����
	for (int i = (index - 1) / 2; i >= 0; i--)//����Ҳ������(n/2)-1��ֻ������index��д����
	{
		HeapAdjust(a, i, index, compare);
	}
	//��Ϊ������sС���ѣ���ô��һ��һ������С�ģ����԰����ŵ����Ȼ��ʣ�µ��ٵ�������Ϊ���һ�����˵�һ��
	for (int i = n - 1; i > 0; i--)
	{
		T tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;
		HeapAdjust(a, 0, i - 1, compare);
	}
}

//��ͨ��������������ϲ�һ����������
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
			//��Ŀ������Ϊ�˶����Ҳ�ܷ�������������
			MergeArrangeSort(a, i, i + j < n ? j : n - i, i + 2 * j < n ? 2 * j : n - i, tmp, compare);
		}
		a = tmp;
	}
	return a;
}

