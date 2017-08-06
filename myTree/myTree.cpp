/*
	�������������ݹ��ǰ�����򡢺����������ǵݹ�ǰ�����򼰷ǵݹ��β�α���
	
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

const int flag = INT_MIN;

struct TreeNode {
	int val;
	TreeNode* left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class myTree{
public:
	TreeNode* generateTree(const std::vector<int> & nums) {
		if (nums.empty())
			return NULL;

		std::queue<TreeNode*> que;
		TreeNode* root = new TreeNode(nums[0]);
		que.push(root);

		int size = nums.size();
		for (int i = 1; i < size; i += 2) {
			TreeNode* left = NULL, *right = NULL;
			TreeNode* tmp = que.front();
			que.pop();

			if (nums[i] != flag) {
				left = new TreeNode(nums[i]);
				que.push(left);
			}//if_left
			if (i + 1 < size && nums[i+1] != flag) {
				right = new TreeNode(nums[i + 1]);
				que.push(right);
			}//if_right

			tmp->left = left; tmp->right = right;
			
		}//for
		return root;
	}//generateTree

	/*�ݹ��ǰ��*/
	void preOrder(TreeNode* root) {
		if (root == NULL)
			return;
		std::cout << root->val << " ";
		preOrder(root->left);
		preOrder(root->right);
	}

	/*�ݹ������*/
	void InOrder(TreeNode* root) {
		if (root == NULL)
			return;
		InOrder(root->left);
		std::cout << root->val << " ";
		InOrder(root->right);
	}

	/*�ݹ�����*/
	void PostOrder(TreeNode* root) {
		if (root == nullptr)
			return;
		PostOrder(root->left);
		PostOrder(root->right);
		std::cout << root->val << " ";
	}

	/*�ǵݹ��ǰ�����*/
	/*
		����һ��
		����һ��ջ�����ø���ջ��ֻҪջ��Ϊ�գ���������������
		ÿ�ε������֮�󣬾���������������������ջ���Ƚ���������ջ������ջ��������������֤��������ջ�д��������������档
	*/
	void preOrder_NonRecursive_1(TreeNode * root) {
		if (root == nullptr)
			return;

		std::stack<TreeNode*> sta;
		sta.push(root);

		while (!sta.empty()) {
			TreeNode* cur = sta.top();
			std::cout << cur->val << " ";
			sta.pop();

			if (cur->right)
				sta.push(cur->right);
			if (cur->left)
				sta.push(cur->left);
		}//while	
	}//preOrder_NonRecursive_1

	/*
		��������
		����һ��ջ�������ǰ�ڵ㲻Ϊ�գ�����ջ��Ϊ�գ�ѭ����ӡ��ǰ����������������ýڵ���ջ��
		����������֮���ٷ�����ָ��ջ��Ԫ�أ���ʼ��ջ����ʼ����ջ��Ԫ�ص�������
	*/
	void preOrder_NonRecursive_2(TreeNode* root) {
		if (!root)
			return;
		std::stack<TreeNode*> sta;
		TreeNode* cur = root;

		while (cur != NULL || !sta.empty()) {

			/*�ȴ�ӡ����һ·������ջ*/
			while (cur) {
				std::cout << cur->val << " ";
				sta.push(cur);
				cur = cur->left;
			}
			/*����ջ��Ԫ�ص�������*/
			if (!sta.empty())
			{
				cur = sta.top()->right;
				sta.pop();
			}//if

		}//while
	}//preOrder_NonRecursive_2

	void preOrder_NonRecursive_3(TreeNode* root) {
		if (!root)
			return;
		TreeNode* cur = root;
		std::stack<TreeNode*> sta;

		/*ѭ����ӡ��ǰ��㼰����������㣬����ջ��ֱ��Ϊ��*/
		while (cur) {
			std::cout << cur->val << " ";
			sta.push(cur);
			cur = cur->left;
		}

		/*��ջ����Ԫ��*/
		while (!sta.empty()) {
			/*��ʼָ��ջ��Ԫ�ص���������������ջ��Ԫ��*/
			cur = sta.top()->right;
			sta.pop();
			
			/*�����Ըý��Ϊ׼����ӡ����ջ��㣬ѭ����ӡ����ջ��������㣬ֱ��Ϊ��*/
			while (cur) {
				std::cout << cur->val << " ";
				sta.push(cur);
				cur = cur->left;
			}//while ��ǰ�ڵ㻹��������

		}//while ջ��Ϊ��

	} //preOrder_NonRecursive_3

	/*
		�ǵݹ��������
		����һ����ѭ��������ȫ����ջ����ʼ��ӡ��㲢��ջ����ָ������������
	*/
	void InOrder_NonRecursive_1(TreeNode* root) {

		std::stack<TreeNode*> sta;
		TreeNode * cur = root;	// ָ��ǰҪ�����Ľ��

		while (!sta.empty() || cur != NULL) {
			
			/*һ·������ջ*/
			while (cur) {
				sta.push(cur);
				cur = cur->left;
			}
			/*�ٿ�ʼ��ӡջ��������ջ����ʼָ��������*/
			if (!sta.empty()) {
				cur = sta.top();
				std::cout << cur->val << " ";
				sta.pop();
				cur = cur->right;
			}//if
		}//while
	}//InOrder_NonRecursive_1

	
	/*�ǵݹ��������*/
	void PostOrder_Noncursive(TreeNode* root) {
		if (!root)
			return;

		std::stack<TreeNode*> sta;
		TreeNode* cur = root;
		TreeNode* pre = NULL;

		while (cur != NULL || !sta.empty()) {
			
			/*һ·������ջֱ��Ϊ��*/
			while (cur) {
				sta.push(cur);
				cur = cur->left;
			}
			/*��ʼ����ջ��Ԫ��*/
			cur = sta.top();
			
			/*��ǰ�ڵ��������Ϊ�գ�����֮ǰ����ǰ�ڵ����������Ϊ�յ�֮ǰ�Ѿ���ӡ���ˣ��ѱ���ӡ�������ӡ�ý��*/
			if (cur->right == NULL || cur->right == pre) {
				std::cout << cur->val << " ";
				pre = cur;
				sta.pop();
				cur = NULL;
			}
			else 
				cur = cur->right;	/*����ͷ����ҽ��*/
		}//while
	}//PostOrder_Noncursive

	/*�ǵݹ��������---˫ջ��*/
	/*
		����ջs1��s2����Ϊ��������������ӡ���ڵ㣬���������������ĸ��ڵ㣬���ȴ�ӡ�������ĸ��ڵ�
		��s1�Ĺ��ܾ����Ƚ����ڵ���룬�ٽ�����������������ջ��ͨ��˫ջ���Ϳ����Ƚ��������ĸ��ڵ㵯������s2ջ�У�
		��ʱ�����ý��������Ľ�����ջ2�ĵײ�����֤�˵����ڶ���ӡ��Ȼ��Ŵ�����������������s2�������棬Ҳ�����ȴ�ӡ��
	*/
	void PostOrder_NonRecursive_1(TreeNode* root) {
		if (!root)
			return;
		std::stack<TreeNode*> s1, s2;

		/*�Ƚ����ڵ���ջs1*/
		s1.push(root);
		TreeNode* cur = NULL;
		
		
		while (!s1.empty()) {

			/*�������� ���ڵ� | �������ĸ��ڵ� | �������ĸ��ڵ� ����ջ��Ԫ�أ�������������s2��*/
			cur = s1.top();	
			s1.pop();
			s2.push(cur);
			
			/*�ֱ𽫸ղ�ջ��Ԫ�ص���������������ջs1��*/
			if (cur->left)
				s1.push(cur->left);
			if (cur->right)
				s1.push(cur->right);
		}

		// ��ӡջ��Ԫ��
		while (!s2.empty()) {
			std::cout << s2.top()->val << " ";
			s2.pop();
		}// while
	}//PostOrder_NonRecursive_1

	/*��α���������*/
	void LevelOrder(TreeNode* root) {
		if (!root)
			return;
		std::queue<TreeNode*> que;
		que.push(root);
		std::vector<int> res;

		while (!que.empty()) {
			int sz = que.size();
			for (int i = 0; i < sz; ++i) {
				TreeNode* tmp = que.front();
				que.pop();
				res.push_back(tmp->val);
				if (tmp->left)
					que.push(tmp->left);
				if (tmp->right)
					que.push(tmp->right);
			}
		}
		PrintVec(res);
	}

	void PrintVec(const std::vector<int> &res) {
		if (res.empty())
			return;
		for (auto ele : res) {
			std::cout << ele << " ";
		}
		std::cout << std::endl;
	}

	void Test(TreeNode* root) {
		std::cout << "�� " << times << " �β��ԣ�" << std::endl;
		std::cout << std::endl << "�ݹ�ǰ�������" << std::endl;
		preOrder(root);
		std::cout << std::endl << "�ǵݹ�1ǰ�������" << std::endl;
		preOrder_NonRecursive_1(root);
		std::cout << std::endl << "�ǵݹ�2ǰ�������" << std::endl;
		preOrder_NonRecursive_2(root);
		std::cout << std::endl << "�ǵݹ�3ǰ�������" << std::endl;
		preOrder_NonRecursive_3(root);
		std::cout << std::endl << "�ݹ����������" << std::endl;
		InOrder(root);
		std::cout << std::endl << "�ǵݹ����������" << std::endl;
		InOrder_NonRecursive_1(root);
		std::cout << std::endl << "�ݹ���������" << std::endl;
		PostOrder(root);
		std::cout << std::endl << "�ǵݹ���������" << std::endl;
		PostOrder_Noncursive(root);
		std::cout << std::endl << "�ǵݹ�������1��" << std::endl;
		PostOrder_NonRecursive_1(root);
		std::cout << std::endl;
		std::cout << "�ǵݹ��α�����" << std::endl;
		LevelOrder(root);
		std::cout << "------------------------------" << std::endl;
		++times;
	}
	static int times;
};

int myTree::times = 1;

int main() {
	myTree tree;
	std::vector<int> nums1 = { 9, 6, 13, 4, 8, 12, flag, flag, flag, 7, flag, flag, flag };
	TreeNode* root1 = tree.generateTree(nums1);
	std::vector<int> nums2 = {};
	TreeNode* root2 = tree.generateTree(nums2);
	std::vector<int> nums3 = { 1, 2, flag, 3, flag, 4, flag, 5, flag, 6, flag, 7, flag, flag, flag };
	TreeNode* root3 = tree.generateTree(nums3);
	
	tree.Test(root1);
	tree.Test(root2);
	tree.Test(root3);
	
	
	return 0;
}