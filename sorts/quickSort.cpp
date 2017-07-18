#include <stdio.h>

int * quickSort(int *array, int length);				// 指针函数， 划分快排
void quickSort(int *array, int left, int right);		// 递归实现
int partition(int *array, int left, int right);			// 划分区间， 得到每趟排序后的划分元素最终放置的位置
void printArray(int *array, int length);				// 打印数组

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