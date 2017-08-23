#include <stdio.h>
static int cnt = 0;

/*��ʱ����ʹ�øú���*/
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
	int ColumnIndex[QueueSize]; // index��ʾrow, value��ʾcol
	
	// ��ʼ������һά���飬�����е�i�����ֱ�ʾλ�ڵ�i�еĻʺ���кš�
	for (int row = 0; row < QueueSize; ++row) {
		ColumnIndex[row] = row;
	}

	// ��һά�������������ϣ���������е������
	int row = 0;
	PermutationQueue(ColumnIndex, QueueSize, row);
}

int main() {
	Queue();
	
	return 0;
}