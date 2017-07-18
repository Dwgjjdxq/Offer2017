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