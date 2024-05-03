#pragma once
//������
//ʱ�临�Ӷ�o(nlogn)
//�ռ临�Ӷ�o(1)
//���ȶ�������ʽ�����Լ�¼�����޹أ������ڽϴ���ļ�
template<typename T>
void HeapSort(T* a, int n, bool compare(const T&, const T&));

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