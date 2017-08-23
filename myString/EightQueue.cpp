#include <stdio.h>
static int cnt = 0;

/*暂时不能使用该函数*/
void swap(int &a, int &b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

void Print(int ColumnIndex[], int QueueSize) {
	printf("%d: ", cnt);
	for (int row = 0; row < QueueSize; ++row) {
		printf("%d\t", ColumnIndex[row]);
	}
	printf("\n");
}

bool check(int ColumnIndex[], int QueueSize){
	for (int row = 0; row < QueueSize; ++row) {
		for (int col = row + 1; col < QueueSize; ++col) {
			if (row - col == ColumnIndex[row] - ColumnIndex[col]
				|| col - row == ColumnIndex[row] - ColumnIndex[col])
				return false;
		}//for-col
	}//for-row
	return true;
}

void PermutationQueue(int ColumnIndex[], int QueueSize, int row) {
	if (row == QueueSize) {
		if (check(ColumnIndex, QueueSize)) {
			++cnt;
			Print(ColumnIndex, QueueSize);
		}//if
	}//if
	else {
		for (int i = row; i < QueueSize; ++i) {
			int temp = ColumnIndex[i];
			ColumnIndex[i] = ColumnIndex[row];
			ColumnIndex[row] = temp;
			PermutationQueue(ColumnIndex, QueueSize, row + 1);

			temp = ColumnIndex[i];
			ColumnIndex[i] = ColumnIndex[row];
			ColumnIndex[row] = temp;
		}//for
	}//else
}

void Queue() {
	const int QueueSize = 8;
	int ColumnIndex[QueueSize]; // index表示row, value表示col
	
	// 初始化构建一维数组，数组中第i个数字表示位于第i行的皇后的列号。
	for (int row = 0; row < QueueSize; ++row) {
		ColumnIndex[row] = row;
	}

	// 对一维数组进行排列组合，计算出所有的情况。
	int row = 0;
	PermutationQueue(ColumnIndex, QueueSize, row);
}

int main() {
	Queue();
	
	return 0;
}