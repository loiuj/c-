#pragma once
//�鲢����
//ʱ�临�Ӷ�o(nlogn)
//�ռ临�Ӷ�o(n)
//�ȶ��������㷨
//������ȶ��Ļ�������compare�ıȽ�
template<typename T>
T* MergeSort(T* a, int n, bool compare(const T&, const T&));

//��ͨ��������������ϲ�һ����������
//�鲢�Ƕ������Ѿ�����������������������Ҫ����һ�����������洢����������ȱȽ����������һ��Ԫ�أ������Ǵ�С������ô˭С˭Ϊ��һ����Ȼ���Ǹ�����ָ��ڶ�Ԫ��
//��Ϊ���������Ѿ�������ô���������һ��Ԫ������С���Ǹ��϶�����������С���Ǹ���Ȼ��ȡ��Ŀ������ΪŲ����֮ǰ���ٵ����飬Ҳ���Ǵ洢����������У�Ȼ���ٱȽ����������һ��Ԫ��
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