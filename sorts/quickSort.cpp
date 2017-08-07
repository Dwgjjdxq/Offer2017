#include <stdio.h>

int * quickSort(int *array, int length);				// ָ�뺯���� ���ֿ���
void quickSort(int *array, int left, int right);		// �ݹ�ʵ��
int partition(int *array, int left, int right);			// �������䣬 �õ�ÿ�������Ļ���Ԫ�����շ��õ�λ��
void printArray(int *array, int length);				// ��ӡ����

/*�Ż�swap��������*/
void swap(int &a, int &b) {
	a ^= b;
	b ^= a;
	a ^= b;
}

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

/*-----------------����ѭ��������һ�εݹ飬������ջ��ȣ������������---------------*/
void quickSortLoop(int *arr, int left, int right) {
	int pos = 0;
	while (left < right) {
		pos = partitionOptim(arr, left, right);
		quickSortLoop(arr, left, pos - 1);
		left = pos + 1;
	}
}
/*-----------------------------------------------------------------------------*/

// �ٴ��Ż����������ݹ���̻��ɵ���������ջ��ʹ��
const int maxLengthInsertSort = 7;
void quickSortOptimi(int * array, int left, int right) {
	int pivot = 0;
	if ((right - left) > maxLengthInsertSort)
	{
		while (left < right) {
			pivot = partition(array, left, right);
			quickSortOptimi(array, left, pivot - 1);
			left = pivot + 1; // ���ݹ黻�ɵ������ϲ��ݹ������,left������,Ч����ͬ��quickSortOptimi(array, pivot + 1, right);
		}
	}
	/*��Ԫ������ĳ����ֵʱ����ֱ�Ӳ��������㷨Ч�ʸ���*/
	/*else InsertSort(array);*/ 
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

/*------------------------����ȡ�з��Ż�partition��ѡȡ------------------------*/
int partitionOptim(int *array, int left, int right) {

	int mid = (left + right) >> 1;

	if (array[left] > array[right])		/*�Ƚ����ң���֤��߽�С*/
		swap(array[left], array[right]);
	if (array[mid] > array[right])		/*�Ƚ����ң���֤�м��С*/
		swap(array[mid], array[right]);
	if (array[mid] > array[left])		/*�Ƚ����󣬱�֤�����С*/
		swap(array[mid], array[left]);

	/*�˷��������ѡȡ��Ч��Ҫ�ߣ����Ҿ��пɿ��ԣ����������ܴ�ʱ���ɿ��Ǿ���ȡ�з��Ż�partition*/
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

/*------------------------����ջ���ǵݹ�quicksort-------------------------------------*/
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
		/*����ջ������ÿһ���������Ӵ�����βԪ���±꣬��һ��whileѭ��ʱȡ�������Χ������������н���partition����*/
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