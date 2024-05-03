#pragma once
//ֱ��ѡ������
//ʱ�临�Ӷ�o(n^2)
//�ռ临�Ӷ�o(1)
//���ȶ������򷽷�
//ʱ�临�Ӷ������ð�������
template<typename T>
void SelectSort(T* a, int n, bool compare(const T&, const T&));

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