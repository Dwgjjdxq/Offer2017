// quicksort
#if 0
#include <iostream>
#include <cstdlib>
#include <stack>
#include <ctime>

using namespace std;

/*���ֺ���*/
int Partition(int *A, int left, int right);

/*�ݹ�ʵ��*/
void QuickSort1(int *A, int left, int right);

/*�ǵݹ�ʵ��*/
void QuickSort(int *A, int left, int right);

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

/*���ֲ���---δ�Ż��汾*/
int Partition(int *A, int low, int high) {

	int pivot = A[low];			// ����ǰ���еĵ�һ��Ԫ����Ϊ����ֵ���Ա���л���

	while (low < high) {

		while (low < high && pivot <= A[high]) --high;

		A[low] = A[high];		// ��������ֵС��Ԫ���ƶ������

		while (low < high && pivot >= A[low]) ++low;

		A[high] = A[low];		// ��������ֵ���Ԫ���ƶ����Ҷ�

	}

	A[low] = pivot;				// 

	return low;
}

/*���ֲ���---�Ż�����Ľ���������*/

int Partition1(int *A, int low, int high) {

	int pivot = A[low];

	while (low < high) {

		while (low < high && A[high] >= pivot) --high;

		swap(A[low], A[high]);

		while (low < high && A[low] <= pivot) ++low;

		swap(A[low], A[high]);
	}
	return low;
}

int *QuickSort(int *A, int n) {
	if (A == NULL || n <= 0) {
		return A;
	}
	QuickSort1(A, 0, n - 1);
	return A;
}

/*��������ĵݹ�ʵ��*/
void QuickSort1(int *A, int left, int right) {
	if (left < right) {
		int pivotpos = Partition(A, left, right);
		QuickSort1(A, left, pivotpos - 1);
		QuickSort1(A, pivotpos + 1, right);
	}
}

/*��������ķǵݹ�ʵ��*/
void QuickSort2(int *A, int left, int right) {

}

int main() {
	int A[] = { 5, 1, 9, 3, 7, 4, 8, 6, 2 };

	// sizeof(A[0]) = 4, sizeof(A) = 4 * n

	const int n = sizeof(A) / sizeof(A[0]);

	QuickSort(A, n);

	for (int i = 0; i < 9; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
#endif

// MergeSort
#if 0
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

/*���������*/
int *MergeSort(int *A, int n);

/*�ݹ�鲢����*/
void MergeSort(int *A, int left, int right);

/*�ϲ�������*/
void Merge(int *A, int left, int mid, int right);

int *MergeSort(int *A, int n) {
	if (A == NULL || n <= 0)
		return A;
	MergeSort(A, 0, n - 1);
	return A;
}

void MergeSort(int *A, int left, int right) {
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	MergeSort(A, left, mid);
	MergeSort(A, mid + 1, right);
	Merge(A, left, mid, right);
}

/*��������left~mid��mid+1~right���������кϲ�*/
void Merge(int *A, int left, int mid, int right) {

	int *tmp = new int[right - left + 1];
	/*�ϲ�������Ԫ�ص�tmp��ʱ����*/
	int lhs = left, rhs = mid + 1, k = 0;
	while (lhs <= mid && rhs <= right) {
		if (A[lhs] <= A[rhs])
			tmp[k++] = A[lhs++];
		else
			tmp[k++] = A[rhs++];
	}// while

	/*ֱ�ӿ���ʣ��Ԫ��*/
	while (lhs <= mid){
		tmp[k++] = A[lhs++];
	}//while

	while (rhs <= right) {
		tmp[k++] = A[rhs++];
	}//while

	/*������ʱ�������ݵ�ԭ����*/
	for (int i = left; i <= right; ++i) {
		A[i] = tmp[i - left];
	}//for

	delete[]tmp;
}

int main() {

	const int N = 10;
	int array[N];
	srand(time(0));
	for (int i = 0; i < N; ++i) {
		array[i] = rand() % 101;
	}

	cout << "����ǰ��" << endl;

	for (int j = 0; j < N; ++j) {
		cout << array[j] << " ";
	}
	MergeSort(array, N);

	cout << endl << "�����" << endl;

	for (int i = 0; i < N; ++i)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}
#endif

// BubbleSort
#if 0
#include <iostream>
#include <cstdlib>

using namespace std;

/*�����³� T(n) = O(n^2) S(n)=O(1) �ȶ�*/
int *BubbleSort(int *A, int n) {
	if (n <= 0)
		return A;

	/*����n-1��ð��*/
	for (int i = 0; i < n; ++i) {
		/*ÿ��ð�����ͷ��n - i - 1β�ȽϹ���*/
		for (int j = 0; j < n - i - 1; ++j) {

			if (A[j] > A[j + 1]) {
				int tmp = A[j + 1];
				A[j + 1] = A[j];
				A[j] = tmp;
			}//if
		}//for
	}//for
	return A;
}

/*�����³����Ż�*/
int *BubbleSortDev(int *A, int n) {

	if (n <= 0)
		return A;
	bool flag = true;						/*flag������Ϊ���*/
	for (int i = 0; i < n && flag; ++i) {	/*��flagΪfalse���˳�ѭ��*/

		flag = false;						/*��ʼflagΪfalse*/
		for (int j = 0; j < n - i - 1; ++j) {

			if (A[j] > A[j + 1]) {
				int tmp = A[j + 1];
				A[j + 1] = A[j];
				A[j] = tmp;
				flag = true;			/*��������ݽ�������flagΪtrues*/
			}//if
		}//for
	}//for
	return A;
}

/*С������*/
int *BubbleSortSmall(int *A, int n) {
	if (n <= 0)
		return A;

	for (int i = 0; i < n - 1; ++i) {

		for (int j = n - 1; j > i; --j) {

			if (A[j] < A[j - 1]) {
				int tmp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = tmp;

			}//if
		}//for
	}//for
	return A;
}

/*С�������Ż�*/
int *BubbleSortSmallDev(int *A, int n) {
	if (n <= 0)
		return A;

	bool flag = true;
	for (int i = 0; i < n - 1 && flag; ++i) {

		flag = false;
		for (int j = n - 1; j > i; --j) {

			if (A[j] < A[j - 1]) {
				int tmp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = tmp;
				flag = true;
			}//if
		}//for
	}//for
}

int main() {
	int A[] = { 2, 1, 4, 9, 7, 3, 8, 6 };
	//BubbleSort(A, 8);
	//BubbleSortDev(A, 8);
	//BubbleSortSmall(A, 8);
	BubbleSortSmallDev(A, 8);


	for (int i = 0; i < 8; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}

#endif

/*ֱ�Ӳ�������*/
#if 0
#include <iostream>
#include <cstdlib>

using namespace std;

/*ֱ�Ӳ�������*/
int *IntertionSort(int *A, int n) {
	if (A == NULL || n <= 0)
		return A;

	for (int i = 1; i < n; ++i) {

		int tmp = A[i];
		int j = i - 1;
		for (; j >= 0; --j) {
			if (A[j] > tmp)
				A[j + 1] = A[j];
			else
				break;
		}
		A[j + 1] = tmp;
	}
	return A;
}

int main() {
	int A[] = { 1, 2, 3, 5, 2, 3 };
	IntertionSort(A, 6);

	for (int i = 0; i < 6; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}


#endif

/*ѡ�������㷨*/
#if 0
#include <iostream>
#include <cstdlib>
using namespace std;

int *SelectionSort(int *A, int n) {

	if (n < 0 || A == NULL)
		return A;

	/*����n-1��ѡ��ÿ�ζ��Ӻ����n-i����ѡ����С�ģ��ŵ�i + 1λ��*/
	for (int i = 0; i < n - 1; ++i) {

		/*ÿ��ѡ���ҵ�i��n - 1����СԪ��λ�ã�����iλ��*/
		int minPos = i;
		for (int j = i + 1; j < n; ++j) {
			if (A[j] < A[minPos]) {
				minPos = j;
			}//if
		}//for

		/*����СԪ�ط��ڴ���ѡ�����λ*/
		int tmp = A[minPos];
		A[minPos] = A[i];
		A[i] = tmp;
	}//for
	return A;
}

int main() {
	int A[] = { 2, 1, 4, 2, 7, 5, 3, 8 };
	SelectionSort(A, 8);

	for (int i = 0; i < 8; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;

	return 0;
}
#endif

// HeapSort
#if 0
#include <iostream>
#include <cstdlib>
#include <time.h>
#define N 10
using namespace std;

/*��������*/
void HeapSort(int *array);
/*�����󶥶Ѻ���*/
void BuildMaxHeap(int *array);
/*����Ϊ�󶥶Ѻ���*/
void MaxHeapify(int *array, int n);
/*���ضѵ����ݸ���*/
int HeapSize;

void HeapSort(int *array) {

	BuildMaxHeap(array);

	/*��ȡ���ֵ�������µ�����˳��*/
	for (int i = N - 1; i >= 0; --i) {						// �����±��Ǵ�0��N-1
		int t = array[i];
		array[i] = array[0];
		array[0] = t;
		HeapSize -= 1;										// �ص�ע��
		MaxHeapify(array, 1);								// �ڶ��У��Ѷ�Ԫ���±��1��ʼ!!!!!
	}
}

void BuildMaxHeap(int *array) {
	HeapSize = N;
	for (int i = N / 2; i >= 1; --i) {						// ע��i��ȡֵ���ѵĸ߶ȴ� 1 �� N/2
		MaxHeapify(array, i);
	}
}

// �ѵ��±�� 1 �� N
void MaxHeapify(int *array, int temp) {
	int largest;											// ��tempΪ����������ĶѶ�
	int l = temp * 2;										// ����tempΪ��������������
	int r = temp * 2 + 1;									// ����tempΪ����������Ҷ���

	if (l <= HeapSize && array[l - 1] > array[temp - 1])	// �����ж�������Ƿ���ڣ���l <= HeapSize
		largest = l;
	else
		largest = temp;
	// ��ʱ����Ѿ������� largest-1 ���λ�õ�ֵ
	if (r <= HeapSize && array[r - 1] > array[largest - 1])	// �����ж��Ҷ����Ƿ���ڣ���r <= HeapSize
		largest = r;

	if (largest != temp) {
		int t = array[largest - 1];
		array[largest - 1] = array[temp - 1];
		array[temp - 1] = t;
		MaxHeapify(array, largest);	// ����Ϊ�󶥶�
	}
}

void HeapAdjust(int *array, int idx, int n);
void HeapSort2(int *array, int n);

void HeapSort2(int *A, int n) {
	if (n <= 0)
		return;

	for (int i = (n - 1) / 2; i >= 0; --i) {
		HeapAdjust(A, i, n - 1);
	}

	for (int i = n - 1; i > 0; --i) {
		int tmp = A[0];
		A[0] = A[i];
		A[i] = tmp;

		HeapAdjust(A, 0, i - 1);
	}
}

void HeapAdjust(int *A, int idx, int n) {
	int tmp = A[idx];
	for (int j = 2 * idx + 1; j < n; j = 2 * j + 1) {
		if (j < n - 1 && A[j] < A[j + 1]) {
			++j;
		}

		if (tmp >= A[j])
			break;
		A[idx] = A[j];
		idx = j;
	}
	A[idx] = tmp;
}

int main() {
	// ����һ������������
	int array[N];

	// ������������ӣ�����ÿ�β�����ͬ�������
	srand(time(0));

	for (int i = 0; i < N; ++i) {
		array[i] = rand() % 101; // ���鸳ֵʹ�������������0-100֮��������
	}

	cout << "����ǰ��" << endl;
	for (int j = 0; j < N; ++j) {
		cout << array[j] << " ";
	}
	cout << endl << "�����" << endl;
	// ���ö��������Ը������������
	HeapSort(array);
	for (int k = 0; k < N; ++k) {
		cout << array[k] << " ";
	}
	cout << endl;

	system("pause");

	srand(time(0));

	for (int i = 0; i < N; ++i) {
		array[i] = rand() % 101;
	}
	cout << "����ǰ��" << endl;
	for (int i = 0; i < N; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	cout << "�����" << endl;
	HeapSort2(array, N);
	for (int i = 0; i < N; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}

#endif

// Shell Sort
#if 1
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void shellsort(int *array, int n) {
	if (n < 0)
		return;
	int d = n;
	while (d > 1) {
		d = (d + 1) / 2;
		for (int i = d; i < n; ++i) {

			int tmp = array[i];
			int j = i - d;
			for (; j >= 0; j -= d)  {
				if (array[j] > tmp)
					array[j + d] = array[j];
				else
					break;
			}//for
			array[j + d] = tmp;		// ��Ϊforѭ���ĺ���j�Ѿ�������d�����ʱ��Ҫ���¼���ȥ�����ɴﵽ����Ŀ��
		}//for
	}//while
}

int main() {


	/*
	srand(time(0));
	int array[10];

	for (int i = 0; i < 10; ++i) {
	array[i] = rand() % 101;
	}
	*/
	int array[] = { 3, 9, 1, 5, 8, 3, 7, 4, 6, 2 };
	cout << "����ǰ��" << endl;
	for (int i = 0; i < 10; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	cout << "�����" << endl;
	shellsort(array, 10);
	for (int i = 0; i < 10; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	system("pause");
}

#endif