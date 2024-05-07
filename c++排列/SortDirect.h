#pragma once
//ֱ�Ӳ�������
//ʱ�临�Ӷ�o(n^2)
//�ռ临�Ӷ�o(1)
//�ȶ������򷽷�
template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump = 1);

//����������ݲ��뵽ǰ�����������к��ʵ�λ�ã���ҪŲ������Ԫ��
//����jump����Ϊϣ������Ҳ�õ��ˣ�ֱ�������ʱ��jump����1
template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump)
{
	T compare_num = a[1];
	int j;
	//���Ǵӵ�0����ʼ�洢��û���ڱ�λ������ֱ�Ӵӵ�1����ʼ����Ϊ��ʼֻ��һ��Ԫ�أ�������������������1��ʼ
	for (int i = jump; i < n; i += jump)
	{
		compare_num = a[i];
		//������1��ʼ-1Ҳ��ƥ��0��û�����⻹�ܱ���Ҫ��ƥ��һ������
		for (j = i - jump; compare(a[j], compare_num) && j >= 0; j -= jump)
			a[j + jump] = a[j];
		a[j + jump] = compare_num;
	}
}