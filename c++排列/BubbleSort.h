#pragma once

//ð������
//ʱ�临�Ӷ�o(n^2)
//�ռ临�Ӷ�o(1)
//�ȶ������򷽷�
template<typename T>
void BubbleSort(T* a, int n, bool compare(const T&, const T&));

//ð�����򣬴Ӻ���ǰ(���ǰ����)�����Ƚ�����Ԫ�ص�ֵ����Ϊ�����򽻻����ǣ�ֱ�����бȽ��ꡣ����������Ϊ��һ�ˡ�ð������
//Ҳ���ǰ�ÿ��Ҫ�������Ƶ�ǰ�棬����Ӵ�С����ô�Ͱ���С�Ĵ������
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