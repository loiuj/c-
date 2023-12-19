#pragma once
#include <iostream>
using namespace std;
#include <string>


//直接插入排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//稳定的排序方法
template<typename T>
void SortDirect(T* a, int n, bool compare(const T&, const T&), int jump = 1);


//折半插入排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//稳定的排序方法
//查找速度比直接快，移动速度不改变，平均优于直接插入
template<typename T>
void BInsertSort(T* a, int n, bool compare(const T&, const T&));

//希尔排序
//时间复杂度o(n^1.25)~o(1.6n^1.25)
//空间复杂度o(1)
//不稳定的排序方法
//dlta 排序的序列因子，t位dlta的长度
//注意：传入的最后一个增量必须为1
template<typename T>
void ShellSort(T* a, int length, bool compare(const T&, const T&), int* dlta, const int t);

//冒泡排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//稳定的排序方法
template<typename T>
void BubbleSort(T* a, int n, bool compare(const T&, const T&));

//快速排序
//时间复杂度o(nlog2底n)
//空间复杂度o(logn)
//不稳定的排序方法，不是自然排序
//在平均计算速度看，快拍是我们讨论所有排序中最快的
//注意：1.快速排序不适合已经有序的记录，不然会很慢
//	   2.传入的high不是长度，而是对应的索引
//	   3.传入的compare中确保==也返回true，不会会卡死
template<typename T>
void QSort(T* a, int low, int high, bool compare(const T&, const T&));

//直接旋转排序
//时间复杂度o(n^2)
//空间复杂度o(1)
//不稳定的排序方法
//时间复杂度相较于冒泡排序快
template<typename T>
void SelectSort(T* a, int n, bool compare(const T&, const T&));

//堆排序
//时间复杂度o(nlogn)
//空间复杂度o(1)
//不稳定的排序方式，但对记录次序无关，适用于较大的文件
template<typename T>
void HeapSort(T* a, int n, bool compare(const T&, const T&));

//归并排序
//时间复杂度o(nlogn)
//空间复杂度o(n)
//稳定的排序算法
//如果想稳定的话得设置compare的比较
template<typename T>
T* MergeSort(T* a, int n, bool compare(const T&, const T&));

//基排序根据不同的数据需要进行调整，所以不举例

