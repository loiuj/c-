#pragma once
//��������
//ʱ�临�Ӷ�o(nlog2��n)
//�ռ临�Ӷ�o(logn)
//���ȶ������򷽷���������Ȼ����
//��ƽ�������ٶȿ�������������������������������
//ע�⣺1.���������ʺ��Ѿ�����ļ�¼����Ȼ�����
//	   2.�����high���ǳ��ȣ����Ƕ�Ӧ������
//	   3.�����compare��ȷ��==Ҳ����true������Ῠ��
template<typename T>
void QSort(T* a, int low, int high, bool compare(const T&, const T&));

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