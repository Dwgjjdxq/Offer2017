#include <iostream>
using namespace std;

void swap(int &a, int &b) {
	a ^= b;
	b ^= a;
	a ^= b;
}

/*
	建立最大堆
	1. 其实就是拿 "当前父节点" 与 "左右子结点中最大的结点" 比较，
	2. 如果 "当前父节点" 就是最大的，那么不需要调整，直接break；
	3. 否则，将 "最大结点值" 覆盖到 "当前父节点"，同时 "最大结点值" 的位置让给 "当前父节点"
	   让 "当前父节点"重新寻找确认最终位置，继续与 "最大结点值" 留下来的 "左右子结点" 去比较；

	   (父亲没有他的其中一个孩子大，就让他去和那个孩子的孩子去比较，直到找到比两个孩子都大的位置，
	   或者没有孩子的时候，就结束，然后让父亲坐在这个位置)；

	4. 循环往复直到出现 "当前父节点" 所更新的位置本身就是最大了，或者没有子结点了，此时退出去
	   将 "当前父节点" 的值放到 "当前位置"。

*/
void maxHeap(int *arr, int curPos, int length) {
	int temp = arr[curPos];
	int maxPos = (curPos << 1) + 1;	// 代表curPos的左子树结点

	/*左右子结点总是将最大的与temp比较，temp已经暂时保存起来了，直到出现temp最大，或者已经没有子结点为止*/
	for (; maxPos <= length; maxPos = 2 * maxPos + 1) {		/* maxPos = maxPos * 2 + 1,即重新进入子结点的比较 */

		/*寻找最大的子结点*/   // 此处maxPos < length 不能等于，如果等于，则maxPos+1不存在
		if (maxPos < length && arr[maxPos] < arr[maxPos + 1])
			maxPos++;	// 代表curPos右子树结点

		/*如果父节点的值是最大的，那么停止查找*/
		if (temp >= arr[maxPos])	/*表示左右子结点检查之后均没有当前父节点大，就退出循环*/
			break;

		/*父节点被最大的子结点覆盖*/
		arr[curPos] = arr[maxPos];

		/*同时将该最大子结点位置作为父节点可能存放的位置，继续寻找父节点最终存放的位置*/
		curPos = maxPos;
	}

	/*此位置就是父节点存放的位置，更新完毕*/
	arr[curPos] = temp;
}
void HeapSort(int arr[], int length) {
	if (arr == NULL || length <= 0)
		return;

	/*将一个无序数组建立一个大顶堆，即父节点比左右子节点都大*/
	/*堆元素的下标是从0到length - 1标记*/
	/*因为建立的堆是依据完全二叉树的思想实现的，所以，此处的 length/2 - 1 位置是从下往上，从右往左第一个非叶子结点*/
	for (int curPos = (length >> 1) - 1; curPos >= 0; --curPos) {
		maxHeap(arr, curPos, length - 1);	// length - 1 为二叉树中实际的标号最大值
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