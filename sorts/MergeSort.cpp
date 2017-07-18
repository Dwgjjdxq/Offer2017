#include <stdio.h>

/*�鲢����ǰ��׼������ָ�뺯��������һ��ָ�������ָ��*/
int * MergeSort(int * array, int length);
/*�ݹ�鲢*/
void MergeSort(int * array, int left, int right);
/*��������left~mid��mid+1~right���������кϲ�*/
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
	/*�ϲ�������Ԫ�ص�tmp��ʱ������ȥ*/
	int first = left, second = mid + 1, index = 0;
	while (first <= mid && second <= right) {
		if (array[first] <= array[second])
			tmp[index++] = array[first++];
		else
			tmp[index++] = array[second++];
	}//while

	/*����ʣ��Ԫ��*/
	while (first <= mid) tmp[index++] = array[first++];
	while (second <= right) tmp[index++] = array[second++];

	/*����ʱ�������ݿ�����ԭ����*/
	for (int i = left; i <= right; ++i) array[i] = tmp[i - left];

	/*ɾ����ʱ�ռ�*/
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