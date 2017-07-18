#include <stdio.h>

/*归并排序前期准备，用指针函数，返回一个指向数组的指针*/
int * MergeSort(int * array, int length);
/*递归归并*/
void MergeSort(int * array, int left, int right);
/*将排序后的left~mid与mid+1~right两个子序列合并*/
void Merge(int * array, int left, int mid, int right);

int *MergeSort(int * array, int length) {
	if (array == NULL || length < 1)
		return array;
	MergeSort(array, 0, length - 1);
	return array;
}

void MergeSort(int * array, int left, int right) {
	if (left < right) {
		int mid = (left + right) >> 1;
		MergeSort(array, left, mid);
		MergeSort(array, mid + 1, right);

		Merge(array, left, mid, right);
	}
}

void Merge(int * array, int left, int mid, int right) {
	int * tmp = new int[right - left + 1];
	/*合并排序后的元素到tmp临时数组中去*/
	int first = left, second = mid + 1, index = 0;
	while (first <= mid && second <= right) {
		if (array[first] <= array[second])
			tmp[index++] = array[first++];
		else
			tmp[index++] = array[second++];
	}//while

	/*拷贝剩余元素*/
	while (first <= mid) tmp[index++] = array[first++];
	while (second <= right) tmp[index++] = array[second++];

	/*将临时数组数据拷贝到原数组*/
	for (int i = left; i <= right; ++i) array[i] = tmp[i - left];

	/*删除临时空间*/
	delete[]tmp;
}

void printArray(int * array, int length) {
	printf("array: \n");
	for (int index = 0; index < length; ++index)
		printf(" %d", *(array + index));
	printf("\n\n");
}

int main() {
	int array[] = { 4, 2, 5, 6, 2, 3, 9, 0, 5 };
	int length = sizeof(array) / sizeof(array[0]);
	printArray(array, length);
	int * ret = MergeSort(array, length);
	printArray(ret, length);
	return 0;
}