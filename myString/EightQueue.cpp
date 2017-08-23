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
	for (int index = 0; index < QueueSize; ++index) {
		printf("%d\t", ColumnIndex[index]);
	}
	printf("\n");
}

bool check(int ColumnIndex[], int QueueSize){
	for (int i = 0; i < QueueSize; ++i) {
		for (int j = i + 1; j < QueueSize; ++j) {
			if (i - j == ColumnIndex[i] - ColumnIndex[j]
				|| j - i == ColumnIndex[i] - ColumnIndex[j])
				return false;
		}//for-col
	}//for-row
	return true;
}

void PermutationQueue(int ColumnIndex[], int QueueSize, int index) {
	if (index == QueueSize) {
		if (check(ColumnIndex, QueueSize)) {
			++cnt;
			Print(ColumnIndex, QueueSize);
		}//if
	}//if
	else {
		for (int i = index; i < QueueSize; ++i) {
			int temp = ColumnIndex[i];
			ColumnIndex[i] = ColumnIndex[index];
			ColumnIndex[index] = temp;
			PermutationQueue(ColumnIndex, QueueSize, index + 1);

			temp = ColumnIndex[i];
			ColumnIndex[i] = ColumnIndex[index];
			ColumnIndex[index] = temp;
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
	int index = 0;
	PermutationQueue(ColumnIndex, QueueSize, index);
}

int main() {
	Queue();
	
	return 0;
}