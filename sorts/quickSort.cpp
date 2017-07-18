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