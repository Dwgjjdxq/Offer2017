#include <iostream>
using namespace std;

void swap(int &a, int &b) {
	a ^= b;
	b ^= a;
	a ^= b;
}

/*
	��������
	1. ��ʵ������ "��ǰ���ڵ�" �� "�����ӽ�������Ľ��" �Ƚϣ�
	2. ��� "��ǰ���ڵ�" �������ģ���ô����Ҫ������ֱ��break��
	3. ���򣬽� "�����ֵ" ���ǵ� "��ǰ���ڵ�"��ͬʱ "�����ֵ" ��λ���ø� "��ǰ���ڵ�"
	   �� "��ǰ���ڵ�"����Ѱ��ȷ������λ�ã������� "�����ֵ" �������� "�����ӽ��" ȥ�Ƚϣ�

	   (����û����������һ�����Ӵ󣬾�����ȥ���Ǹ����ӵĺ���ȥ�Ƚϣ�ֱ���ҵ����������Ӷ����λ�ã�
	   ����û�к��ӵ�ʱ�򣬾ͽ�����Ȼ���ø����������λ��)��

	4. ѭ������ֱ������ "��ǰ���ڵ�" �����µ�λ�ñ����������ˣ�����û���ӽ���ˣ���ʱ�˳�ȥ
	   �� "��ǰ���ڵ�" ��ֵ�ŵ� "��ǰλ��"��

*/
void maxHeap(int *arr, int curPos, int length) {
	int temp = arr[curPos];
	int maxPos = (curPos << 1) + 1;	// ����curPos�����������

	/*�����ӽ�����ǽ�������temp�Ƚϣ�temp�Ѿ���ʱ���������ˣ�ֱ������temp��󣬻����Ѿ�û���ӽ��Ϊֹ*/
	for (; maxPos <= length; maxPos = 2 * maxPos + 1) {		/* maxPos = maxPos * 2 + 1,�����½����ӽ��ıȽ� */

		/*Ѱ�������ӽ��*/   // �˴�maxPos < length ���ܵ��ڣ�������ڣ���maxPos+1������
		if (maxPos < length && arr[maxPos] < arr[maxPos + 1])
			maxPos++;	// ����curPos���������

		/*������ڵ��ֵ�����ģ���ôֹͣ����*/
		if (temp >= arr[maxPos])	/*��ʾ�����ӽ����֮���û�е�ǰ���ڵ�󣬾��˳�ѭ��*/
			break;

		/*���ڵ㱻�����ӽ�㸲��*/
		arr[curPos] = arr[maxPos];

		/*ͬʱ��������ӽ��λ����Ϊ���ڵ���ܴ�ŵ�λ�ã�����Ѱ�Ҹ��ڵ����մ�ŵ�λ��*/
		curPos = maxPos;
	}

	/*��λ�þ��Ǹ��ڵ��ŵ�λ�ã��������*/
	arr[curPos] = temp;
}
void HeapSort(int arr[], int length) {
	if (arr == NULL || length <= 0)
		return;

	/*��һ���������齨��һ���󶥶ѣ������ڵ�������ӽڵ㶼��*/
	/*��Ԫ�ص��±��Ǵ�0��length - 1���*/
	/*��Ϊ�����Ķ���������ȫ��������˼��ʵ�ֵģ����ԣ��˴��� length/2 - 1 λ���Ǵ������ϣ����������һ����Ҷ�ӽ��*/
	for (int curPos = (length >> 1) - 1; curPos >= 0; --curPos) {
		maxHeap(arr, curPos, length - 1);	// length - 1 Ϊ��������ʵ�ʵı�����ֵ
	}

	for (int pos = length - 1; pos > 0; --pos) {
		swap(arr[0], arr[pos]);
		maxHeap(arr, 0, pos - 1);
	}
}


int main() {
	int arr[] = { 2, 1, 4, 3, 7, 8, 4, 2, 6, 9, 0};
	HeapSort(arr, 11);
	for (int i = 0; i < 11; ++i)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}