#include <stdio.h>

int * quickSort(int *array, int length);				// ָ�뺯���� ���ֿ���
void quickSort(int *array, int left, int right);		// �ݹ�ʵ��
int partition(int *array, int left, int right);			// �������䣬 �õ�ÿ�������Ļ���Ԫ�����շ��õ�λ��
void printArray(int *array, int length);				// ��ӡ����

// ����ָ��������׵�ַ���Ը�����׼�����л���
int * quickSort(int *array, int length) {
	if (array == NULL || length < 1)
		return array;
	quickSort(array, 0, length - 1);
	return array;
}

// �ҵ��м�Ԫ�ص�λ��֮�󣬽�����һ��Ϊ�����ݹ��������
void quickSort(int *array, int left, int right) {
	if (left < right) {
		int pos = partition(array, left, right);
		quickSort(array, left, pos - 1);
		quickSort(array, pos + 1, right);
	}
}

// �ҵ����ֵ�λ�ã�������Ԫ�ط��ڻ���λ�ã���߶��ȸ�Ԫ��С�� �ұ߶��ȸ�Ԫ�ش�
int partition(int *array, int left, int right) {
	int pivot = array[left];

	while (left < right) {
		while (left < right && array[right] >= pivot) --right;	// �Ƚϣ�����Ҫ����ƶ�
		array[left] = array[right];								// �����쳣�򽻻�
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