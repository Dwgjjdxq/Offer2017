// quicksort
#if 0
#include <iostream>
#include <cstdlib>
#include <stack>
#include <ctime>

using namespace std;

/*划分函数*/
int Partition(int *A, int left, int right);

/*递归实现*/
void QuickSort1(int *A, int left, int right);

/*非递归实现*/
void QuickSort(int *A, int left, int right);

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

/*划分操作---未优化版本*/
int Partition(int *A, int low, int high) {

	int pivot = A[low];			// 将当前表中的第一个元素设为枢轴值，对表进行划分

	while (low < high) {

		while (low < high && pivot <= A[high]) --high;

		A[low] = A[high];		// 将比轴枢值小的元素移动到左端

		while (low < high && pivot >= A[low]) ++low;

		A[high] = A[low];		// 将比轴枢值大的元素移动到右端

	}

	A[low] = pivot;				// 

	return low;
}

/*划分操作---优化多余的交换操作）*/

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

/*快速排序的递归实现*/
void QuickSort1(int *A, int left, int right) {
	if (left < right) {
		int pivotpos = Partition(A, left, right);
		QuickSort1(A, left, pivotpos - 1);
		QuickSort1(A, pivotpos + 1, right);
	}
}

/*快速排序的非递归实现*/
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

/*划分总入口*/
int *MergeSort(int *A, int n);

/*递归归并排序*/
void MergeSort(int *A, int left, int right);

/*合并子序列*/
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

/*将排序后的left~mid与mid+1~right两个子序列合并*/
void Merge(int *A, int left, int mid, int right) {

	int *tmp = new int[right - left + 1];
	/*合并排序后的元素到tmp临时数组*/
	int lhs = left, rhs = mid + 1, k = 0;
	while (lhs <= mid && rhs <= right) {
		if (A[lhs] <= A[rhs])
			tmp[k++] = A[lhs++];
		else
			tmp[k++] = A[rhs++];
	}// while

	/*直接拷贝剩余元素*/
	while (lhs <= mid){
		tmp[k++] = A[lhs++];
	}//while

	while (rhs <= right) {
		tmp[k++] = A[rhs++];
	}//while

	/*拷贝临时数组数据到原数组*/
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

	cout << "排序前：" << endl;

	for (int j = 0; j < N; ++j) {
		cout << array[j] << " ";
	}
	MergeSort(array, N);

	cout << endl << "排序后：" << endl;

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

/*大数下沉 T(n) = O(n^2) S(n)=O(1) 稳定*/
int *BubbleSort(int *A, int n) {
	if (n <= 0)
		return A;

	/*进行n-1趟冒泡*/
	for (int i = 0; i < n; ++i) {
		/*每次冒泡针对头到n - i - 1尾比较工作*/
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

/*大数下沉的优化*/
int *BubbleSortDev(int *A, int n) {

	if (n <= 0)
		return A;
	bool flag = true;						/*flag用来作为标记*/
	for (int i = 0; i < n && flag; ++i) {	/*若flag为false则退出循环*/

		flag = false;						/*初始flag为false*/
		for (int j = 0; j < n - i - 1; ++j) {

			if (A[j] > A[j + 1]) {
				int tmp = A[j + 1];
				A[j + 1] = A[j];
				A[j] = tmp;
				flag = true;			/*如果有数据交换，则flag为trues*/
			}//if
		}//for
	}//for
	return A;
}

/*小数上升*/
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

/*小数上升优化*/
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

/*直接插入排序*/
#if 0
#include <iostream>
#include <cstdlib>

using namespace std;

/*直接插入排序*/
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

/*选择排序算法*/
#if 0
#include <iostream>
#include <cstdlib>
using namespace std;

int *SelectionSort(int *A, int n) {

	if (n < 0 || A == NULL)
		return A;

	/*进行n-1趟选择，每次都从后面的n-i个中选出最小的，放到i + 1位置*/
	for (int i = 0; i < n - 1; ++i) {

		/*每次选择，找到i到n - 1处最小元素位置，放在i位置*/
		int minPos = i;
		for (int j = i + 1; j < n; ++j) {
			if (A[j] < A[minPos]) {
				minPos = j;
			}//if
		}//for

		/*将最小元素放在此趟选择的首位*/
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

/*堆排序函数*/
void HeapSort(int *array);
/*建立大顶堆函数*/
void BuildMaxHeap(int *array);
/*调整为大顶堆函数*/
void MaxHeapify(int *array, int n);
/*返回堆的数据个数*/
int HeapSize;

void HeapSort(int *array) {

	BuildMaxHeap(array);

	/*提取最大值，并重新调整堆顺序*/
	for (int i = N - 1; i >= 0; --i) {						// 数组下标是从0到N-1
		int t = array[i];
		array[i] = array[0];
		array[0] = t;
		HeapSize -= 1;										// 重点注意
		MaxHeapify(array, 1);								// 在堆中，堆顶元素下标从1开始!!!!!
	}
}

void BuildMaxHeap(int *array) {
	HeapSize = N;
	for (int i = N / 2; i >= 1; --i) {						// 注意i的取值，堆的高度从 1 到 N/2
		MaxHeapify(array, i);
	}
}

// 堆的下标从 1 到 N
void MaxHeapify(int *array, int temp) {
	int largest;											// 以temp为顶点的子树的堆顶
	int l = temp * 2;										// 求以temp为顶点的子树左儿子
	int r = temp * 2 + 1;									// 求以temp为顶点的子树右儿子

	if (l <= HeapSize && array[l - 1] > array[temp - 1])	// 首先判断左儿子是否存在，即l <= HeapSize
		largest = l;
	else
		largest = temp;
	// 此时最大已经换成了 largest-1 这个位置的值
	if (r <= HeapSize && array[r - 1] > array[largest - 1])	// 首先判断右儿子是否存在，即r <= HeapSize
		largest = r;

	if (largest != temp) {
		int t = array[largest - 1];
		array[largest - 1] = array[temp - 1];
		array[temp - 1] = t;
		MaxHeapify(array, largest);	// 调整为大顶堆
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
	// 声明一个带排序数组
	int array[N];

	// 设置随机化种子，避免每次产生相同的随机数
	srand(time(0));

	for (int i = 0; i < N; ++i) {
		array[i] = rand() % 101; // 数组赋值使用随机函数产生0-100之间的随机数
	}

	cout << "排序前：" << endl;
	for (int j = 0; j < N; ++j) {
		cout << array[j] << " ";
	}
	cout << endl << "排序后：" << endl;
	// 调用堆排序函数对该数组进行排序
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
	cout << "排序前：" << endl;
	for (int i = 0; i < N; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	cout << "排序后：" << endl;
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
			array[j + d] = tmp;		// 因为for循环的后面j已经减掉了d，则此时需要重新加上去，即可达到交换目的
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
	cout << "排序前：" << endl;
	for (int i = 0; i < 10; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	cout << "排序后：" << endl;
	shellsort(array, 10);
	for (int i = 0; i < 10; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	system("pause");
}

#endif