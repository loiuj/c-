#pragma once
#include <iostream>
using namespace std;
#include <string>


//ֱ�Ӳ�������
//ʱ�临�Ӷ�o(n^2)
//�ռ临�Ӷ�o(1)
//�ȶ������򷽷�
template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump = 1);


//�۰��������
//ʱ�临�Ӷ�o(n^2)
//�ռ临�Ӷ�o(1)
//�ȶ������򷽷�
//�����ٶȱ�ֱ�ӿ죬�ƶ��ٶȲ��ı䣬ƽ������ֱ�Ӳ���
template<typename T>
void BInsertSort(T* a, int n, bool compare(const T&, const T&));

//ϣ������
//ʱ�临�Ӷ�o(n^1.25)~o(1.6n^1.25)
//�ռ临�Ӷ�o(1)
//���ȶ������򷽷�
//dlta ������������ӣ�tλdlta�ĳ���
//ע�⣺��������һ����������Ϊ1
template<typename T>
void ShellSort(T* a, int length, bool compare(const T&, const T&), int* dlta, const int t);

//ð������
//ʱ�临�Ӷ�o(n^2)
//�ռ临�Ӷ�o(1)
//�ȶ������򷽷�
template<typename T>
void BubbleSort(T* a, int n, bool compare(const T&, const T&));

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

//ֱ����ת����
//ʱ�临�Ӷ�o(n^2)
//�ռ临�Ӷ�o(1)
//���ȶ������򷽷�
//ʱ�临�Ӷ������ð�������
template<typename T>
void SelectSort(T* a, int n, bool compare(const T&, const T&));

//������
//ʱ�临�Ӷ�o(nlogn)
//�ռ临�Ӷ�o(1)
//���ȶ�������ʽ�����Լ�¼�����޹أ������ڽϴ���ļ�
template<typename T>
void HeapSort(T* a, int n, bool compare(const T&, const T&));

//�鲢����
//ʱ�临�Ӷ�o(nlogn)
//�ռ临�Ӷ�o(n)
//�ȶ��������㷨
//������ȶ��Ļ�������compare�ıȽ�
template<typename T>
T* MergeSort(T* a, int n, bool compare(const T&, const T&));

//��������ݲ�ͬ��������Ҫ���е��������Բ�����

