/*About Stack*/
#include <iostream>
#include <stack>

using namespace std;
 
class Solution{
public:
	/*
	思路：假设stackA存放数，stackB为辅助栈。stackA元素个数为N。
	第1次操作：先取stackA栈顶元素，记为tmp，然后把剩余N-1个元素转移到stackB中，接着把tmp和stackB的N-1个元素依次压入stackA中，这样完成了stackA原栈顶的反转。
	第2次操作：先取stackA栈顶元素，记为tmp，因为栈底有一个元素已完成反转，故只需要把剩余的N-2个元素转移到stackB，接着把tmp和stackB的N-2个元素依次压入stackA中，这样完成了stackA原栈顶第二个元素的反转。
	...

	第i次操作：先取stackA栈顶元素，记为tmp，之前已有i-1个元素完成反转，只需要把栈顶的N-i+1个元素转移到stackB，接着把tmp和stackB的N-i+1依次压入stackA中。
	注意：第N次操作时，因为前面N-1次操作已完成，而此时的栈顶就是初始的栈底，故第N次操作不需要做。总的过程只需要N-1次操作。
	*/
	/*利用两个栈，翻转期中一个栈*/
	void ReverseStack(stack<int> &A, stack<int>&B) {
		if (A.empty())
			return;
		// 共需要操作 A.size() - 1 次
		for (int i = 0; i < A.size() - 1; ++i) {
			// 1.取出A的栈顶元素
			int tmp = A.top();
			A.pop();
			// 2.除了已经A中翻转后的元素，其余元素转移到B栈中。
			while (A.size() > i) {
				B.push(A.top());
				A.pop();
			}
			// 3.依次压入tmp和B中元素到A中去
			A.push(tmp);
			while (!B.empty()) {
				A.push(B.top());
				B.pop();
			}//while B
		}// for
	}//ReverseStack

	void TestReverseStack() {
		stack<int> A;
		stack<int> B;
		cout << "入栈顺序" << endl;
		for (int i = 5; i > 0; --i) {
			cout << i << " ";
			A.push(i);
		}
		cout << endl;
		cout << "翻转后从栈顶到栈底的顺序：" << endl;
		ReverseStack(A, B);
		while (!A.empty()) {
			cout << A.top() << " ";
			A.pop();
		}//while
		cout << endl;
	}
};

int main() {
	Solution sln;
	sln.TestReverseStack();
	return 0;
}