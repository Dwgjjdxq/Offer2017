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
	int ColumnIndex[QueueSize]; // index��ʾrow, value��ʾcol
	
	// ��ʼ������һά���飬�����е�i�����ֱ�ʾλ�ڵ�i�еĻʺ���кš�
	for (int row = 0; row < QueueSize; ++row) {
		ColumnIndex[row] = row;
	}

	// ��һά�������������ϣ���������е������
	int index = 0;
	PermutationQueue(ColumnIndex, QueueSize, index);
}

int main() {
	Queue();
	
	return 0;
}