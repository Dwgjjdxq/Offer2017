#include <stdio.h>

int * quickSort(int *array, int length);				// 指针函数， 划分快排
void quickSort(int *array, int left, int right);		// 递归实现
int partition(int *array, int left, int right);			// 划分区间， 得到每趟排序后的划分元素最终放置的位置
void printArray(int *array, int length);				// 打印数组

/*优化swap交换函数*/
void swap(int &a, int &b) {
	a ^= b;
	b ^= a;
	a ^= b;
}

// 返回指向该数组首地址，对该数组准备进行划分
int * quickSort(int *array, int length) {
	if (array == NULL || length < 1)
		return array;
	quickSort(array, 0, length - 1);
	return array;
}

// 找到中间元素的位置之后，将数组一分为二，递归进行排序
void quickSort(int *array, int left, int right) {
	if (left < right) {
		int pos = partition(array, left, right);
		quickSort(array, left, pos - 1);
		quickSort(array, pos + 1, right);
	}
}

/*-----------------采用循环，减少一次递归，缩减堆栈深度，提高整体性能---------------*/
void quickSortLoop(int *arr, int left, int right) {
	int pos = 0;
	while (left < right) {
		pos = partitionOptim(arr, left, right);
		quickSortLoop(arr, left, pos - 1);
		left = pos + 1;
	}
}
/*-----------------------------------------------------------------------------*/

// 再次优化，将后半个递归过程换成迭代，减少栈的使用
const int maxLengthInsertSort = 7;
void quickSortOptimi(int * array, int left, int right) {
	int pivot = 0;
	if ((right - left) > maxLengthInsertSort)
	{
		while (left < right) {
			pivot = partition(array, left, right);
			quickSortOptimi(array, left, pivot - 1);
			left = pivot + 1; // 将递归换成迭代，上步递归结束后,left不再用,效果等同于quickSortOptimi(array, pivot + 1, right);
		}
	}
	/*当元素少于某个数值时，用直接插入排序算法效率更优*/
	/*else InsertSort(array);*/ 
}

// 找到划分的位置，并将该元素放在划分位置，左边都比该元素小， 右边都比该元素大
int partition(int *array, int left, int right) {
	int pivot = array[left];

	while (left < right) {
		while (left < right && array[right] >= pivot) --right;	// 比较，符合要求就移动
		array[left] = array[right];								// 存在异常则交换
		while (left < right && array[left] <= pivot) ++left;
		array[right] = array[left];
	}//while
	array[left] = pivot;
	return left;
}

/*------------------------三数取中法优化partition的选取------------------------*/
int partitionOptim(int *array, int left, int right) {

	int mid = (left + right) >> 1;

	if (array[left] > array[right])		/*比较左右，保证左边较小*/
		swap(array[left], array[right]);
	if (array[mid] > array[right])		/*比较中右，保证中间较小*/
		swap(array[mid], array[right]);
	if (array[mid] > array[left])		/*比较中左，保证坐标较小*/
		swap(array[mid], array[left]);

	/*此方法比随机选取的效率要高，而且具有可靠性；当数据量很大时，可考虑九数取中法优化partition*/
	int pivot = array[left];

	while (left < right) {
		while (left < right && array[right] >= pivot) --right;
		array[left] = array[right];
		while (left < right && array[left] <= pivot) ++left;
		array[right] = array[left];
	}
	array[left] = pivot;
	return left;
}
/*------------------------------------------------------------------------------*/

/*------------------------利用栈：非递归quicksort-------------------------------------*/
#include <stack>
void quickSortNonRecursive(int *arr, int left, int right) {
	std::stack<int> sta;
	
	if (left < right) {
		int pos = partitionOptim(arr, left, right);
		if (left < pos - 1) {
			sta.push(left);
			sta.push(pos - 1);
		}
		if (pos + 1 < right) {
			sta.push(pos + 1);
			sta.push(right);
		}
		/*利用栈来保存每一个待排序子串的首尾元素下标，下一次while循环时取出这个范围，对这段子序列进行partition操作*/
		while (!sta.empty()) {
			int q = sta.top();
			sta.pop();
			int p = sta.top();
			sta.pop();
			pos = partitionOptim(arr, p, q);
			if (p < pos - 1) {
				sta.push(p);
				sta.push(pos - 1);
			}
			if (pos + 1 < q) {
				sta.push(pos + 1);
				sta.push(q);
			}
		}//while
	}//if
}
/*-----------------------------------------------------------------------------------*/
void printArray(int * array, int length) {
	int index = 0;
	printf("array: \n");
	for (; index < length; ++index) {
		printf(" %d,", *(array + index));
	}
	printf("\n\n");
}

int main() {
	int array[] = { 4, 2, 6, 3, 4, 8, 9, 3 };
	int len = sizeof(array) / sizeof(array[0]);

	printArray(array, len);
	int * ret = quickSort(array, len);
	printArray(ret, len);
	return 0;
}