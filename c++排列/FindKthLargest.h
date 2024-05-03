#pragma once
#include <cstdlib>
#include <ctime>

///�㷨��Ϊ���ҵ��������������k�������
/// \brief ����ѡ���㷨
/// \param numb �������������
/// \param k Ҫ�ҵڼ����
/// \param length ����ĳ���
/// \return ��Ӧ������
///	������ʵ���Ӷ���O(2n)���������Կ���O(n)
int FindKthLargest(int* numb, int k, int length);

//�� numb[left] Ϊ��׼������һ�˻��ֲ���������Ԫ�� numb[left] ���ڵ��±�
int Partition(int* numb, int left, int right) {
	int i = left, j = right;
	//�� numb[left] Ϊ��׼
	const int benchmark = numb[left];
	while (i < j) {
		//��������ɨ�裬�ҵ�һ��С�� benchmark ��Ԫ�� numb[j]
		while (i < j && benchmark <= numb[j]) {
			j--;
		}
		numb[i] = numb[j];
		//��������ɨ�裬�ҵ�һ������ benchmark ��Ԫ�� numb[i]
		while (i < j && numb[i] <= benchmark) {
			i++;
		}
		numb[j] = numb[i];
	}
	numb[i] = benchmark;
	return i;
}

//��ȡ�ڲ������һ������ͬʱ�������ڵ�һλ
int RandomPartition(int* numb, int left, int right) {
	// random.nextInt(int num): �������һ�� [0, num) �ڵ�����
	int i = rand() % (right - left + 1) + left;
	int tmp = numb[i];
	numb[i] = numb[left];
	numb[left] = tmp;
	return Partition(numb, left, right);
}


//���ȡ��һ��������Ϊ�жϣ���Ϊ�����飬Ȼ�������ֵһ�������С�����ģ��ұ��Ǵ������ģ�����������index���������index����ôҪ�ҵĵ�index��ľ�������������Ǿͷ������
//ѡ��һ��������Ϊ��׼���п��ţ������������ڵ�λ�ô���k����ô˵���϶�����ߣ����С�ھ����ұߣ��Ͷ������п��žͺ���
int quickSelect(int* nums, int left, int right, int index) {
	srand((unsigned)time(NULL));

	int q = RandomPartition(nums, left, right);
	if (q == index) {
		//��ǰ���ֵ��±� q ���� index����˵����λ��ֲ������Ѿ��ҵ��˵� k �����Ԫ�أ����±�Ϊ q��ֱ�ӷ��� nums[q] ����
		return nums[q];
	}//����Ϳ��Կ��������Ӷ�Ϊ����һ��ΪO(n)���������Ķ�����С�ģ���ô��ҪO(n^2)��
	else {
		/*
			��ǰ���ֵ��±� q ������ index:
			(1) ��� q < index����ô��˵���� k �����Ԫ���������䣬��ʱ�ݹ�������
			(2) ��� q > index����ô��˵���� k �����Ԫ���������䣬��ʱ�ݹ�������
		*/
		if (q < index) {
			return quickSelect(nums, q + 1, right, index);
		}
		else {
			return quickSelect(nums, left, q - 1, index);
		}
	}
}

int FindKthLargest(int* numb, int k, int length) {
	//�� K �����Ԫ����ʵ��������������Ԫ�� numb[numb.length - k]
	return quickSelect(numb, 0, length - 1, length - k);
}