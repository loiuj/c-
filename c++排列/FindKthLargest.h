#pragma once
#include <cstdlib>
#include <ctime>

///算法是为了找到无序数组里面第k大的数据
/// \brief 快速选择算法
/// \param numb 输入的无序数组
/// \param k 要找第几大的
/// \param length 数组的长度
/// \return 对应的数字
///	这里其实复杂度是O(2n)，不过可以看做O(n)
int FindKthLargest(int* numb, int k, int length);

//以 numb[left] 为基准，进行一趟划分并返回最终元素 numb[left] 所在的下标
int Partition(int* numb, int left, int right) {
	int i = left, j = right;
	//以 numb[left] 为基准
	const int benchmark = numb[left];
	while (i < j) {
		//从右向左扫描，找到一个小于 benchmark 的元素 numb[j]
		while (i < j && benchmark <= numb[j]) {
			j--;
		}
		numb[i] = numb[j];
		//从左向右扫描，找到一个大于 benchmark 的元素 numb[i]
		while (i < j && numb[i] <= benchmark) {
			i++;
		}
		numb[j] = numb[i];
	}
	numb[i] = benchmark;
	return i;
}

//获取内部随机的一个数，同时把他放在第一位
int RandomPartition(int* numb, int left, int right) {
	// random.nextInt(int num): 随机返回一个 [0, num) 内的整数
	int i = rand() % (right - left + 1) + left;
	int tmp = numb[i];
	numb[i] = numb[left];
	numb[left] = tmp;
	return Partition(numb, left, right);
}


//随机取了一个数字作为判断，分为了两块，然后这个数值一定左边是小于他的，右边是大于他的，如果这个数的index就是输入的index，那么要找的第index大的就是他，如果不是就分情况找
//选择一个数以他为基准进行快排，如果这个数所在的位置大于k，那么说明肯定在左边，如果小于就在右边，就对他进行快排就好了
int quickSelect(int* nums, int left, int right, int index) {
	srand((unsigned)time(NULL));

	int q = RandomPartition(nums, left, right);
	if (q == index) {
		//当前划分的下标 q 等于 index，则说明这次划分操作后已经找到了第 k 个最大元素，其下标为 q，直接返回 nums[q] 即可
		return nums[q];
	}//这里就可以看出来复杂度为并不一定为O(n)如果随机到的都是最小的，那么就要O(n^2)了
	else {
		/*
			当前划分的下标 q 不等于 index:
			(1) 如果 q < index，那么则说明第 k 个最大元素在右区间，此时递归右区间
			(2) 如果 q > index，那么则说明第 k 个最大元素在左区间，此时递归左区间
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
	//第 K 个最大元素其实就是升序排序后的元素 numb[numb.length - k]
	return quickSelect(numb, 0, length - 1, length - k);
}