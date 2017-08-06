/*
	建立二叉树，递归版前序、中序、后续遍历，非递归前序、中序及非递归层次层次遍历
	
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

	/*递归版前序*/
	void preOrder(TreeNode* root) {
		if (root == NULL)
			return;
		std::cout << root->val << " ";
		preOrder(root->left);
		preOrder(root->right);
	}

	/*递归版中序*/
	void InOrder(TreeNode* root) {
		if (root == NULL)
			return;
		InOrder(root->left);
		std::cout << root->val << " ";
		InOrder(root->right);
	}

	/*递归版后续*/
	void PostOrder(TreeNode* root) {
		if (root == nullptr)
			return;
		PostOrder(root->left);
		PostOrder(root->right);
		std::cout << root->val << " ";
	}

	/*非递归版前序遍历*/
	/*
		方法一：
		构建一个栈，先让根进栈，只要栈不为空，就做弹出操作，
		每次弹出结点之后，就立即将结点的左右子树入栈，先将右子树入栈，再入栈左子树，这样保证右子树在栈中处于左子树的下面。
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
		方法二：
		构建一个栈，如果当前节点不为空，或者栈不为空，循环打印当前结点左子树，并将该节点入栈，
		左子树到底之后，再返回来指向栈顶元素，开始出栈，开始查找栈中元素的右子树
	*/
	void preOrder_NonRecursive_2(TreeNode* root) {
		if (!root)
			return;
		std::stack<TreeNode*> sta;
		TreeNode* cur = root;

		while (cur != NULL || !sta.empty()) {

			/*先打印，再一路向左入栈*/
			while (cur) {
				std::cout << cur->val << " ";
				sta.push(cur);
				cur = cur->left;
			}
			/*处理栈顶元素的右子树*/
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

		/*循环打印当前结点及其左子树结点，并入栈，直到为空*/
		while (cur) {
			std::cout << cur->val << " ";
			sta.push(cur);
			cur = cur->left;
		}

		/*当栈中有元素*/
		while (!sta.empty()) {
			/*开始指向栈顶元素的右子树，并弹出栈顶元素*/
			cur = sta.top()->right;
			sta.pop();
			
			/*继续以该结点为准备打印和入栈结点，循环打印和入栈左子树结点，直到为空*/
			while (cur) {
				std::cout << cur->val << " ";
				sta.push(cur);
				cur = cur->left;
			}//while 当前节点还有左子树

		}//while 栈不为空

	} //preOrder_NonRecursive_3

	/*
		非递归中序遍历
		方法一：先循环左子树全部入栈，开始打印结点并出栈，再指向右子树处理
	*/
	void InOrder_NonRecursive_1(TreeNode* root) {

		std::stack<TreeNode*> sta;
		TreeNode * cur = root;	// 指向当前要处理的结点

		while (!sta.empty() || cur != NULL) {
			
			/*一路向左并入栈*/
			while (cur) {
				sta.push(cur);
				cur = cur->left;
			}
			/*再开始打印栈顶，并出栈，开始指向右子树*/
			if (!sta.empty()) {
				cur = sta.top();
				std::cout << cur->val << " ";
				sta.pop();
				cur = cur->right;
			}//if
		}//while
	}//InOrder_NonRecursive_1

	
	/*非递归后续遍历*/
	void PostOrder_Noncursive(TreeNode* root) {
		if (!root)
			return;

		std::stack<TreeNode*> sta;
		TreeNode* cur = root;
		TreeNode* pre = NULL;

		while (cur != NULL || !sta.empty()) {
			
			/*一路向左入栈直到为空*/
			while (cur) {
				sta.push(cur);
				cur = cur->left;
			}
			/*开始处理栈顶元素*/
			cur = sta.top();
			
			/*当前节点的右子树为空，或者之前（当前节点的右子树不为空但之前已经打印过了）已被打印过，则打印该结点*/
			if (cur->right == NULL || cur->right == pre) {
				std::cout << cur->val << " ";
				pre = cur;
				sta.pop();
				cur = NULL;
			}
			else 
				cur = cur->right;	/*否则就访问右结点*/
		}//while
	}//PostOrder_Noncursive

	/*非递归后续遍历---双栈法*/
	/*
		两个栈s1和s2，因为后续遍历是最后打印根节点，其次是右子树方面的根节点，最先打印左子树的根节点
		则s1的功能就是先将根节点放入，再将左子树、右子树入栈，通过双栈，就可以先将右子树的根节点弹出放入s2栈中，
		此时，正好将右子树的结点放入栈2的底部，保证了倒数第二打印，然后才处理左子树，放入了s2的最上面，也就最先打印。
	*/
	void PostOrder_NonRecursive_1(TreeNode* root) {
		if (!root)
			return;
		std::stack<TreeNode*> s1, s2;

		/*先将根节点入栈s1*/
		s1.push(root);
		TreeNode* cur = NULL;
		
		
		while (!s1.empty()) {

			/*将本身是 根节点 | 左子树的根节点 | 右子树的根节点 （即栈顶元素）弹出，并弹入s2中*/
			cur = s1.top();	
			s1.pop();
			s2.push(cur);
			
			/*分别将刚才栈顶元素的左右子树结点放入栈s1中*/
			if (cur->left)
				s1.push(cur->left);
			if (cur->right)
				s1.push(cur->right);
		}

		// 打印栈中元素
		while (!s2.empty()) {
			std::cout << s2.top()->val << " ";
			s2.pop();
		}// while

	}//PostOrder_NonRecursive_1

};

int main() {
	myTree tree;
	std::vector<int> nums = { 9, 6, 13, 4, 8, 12, flag, flag, flag, flag };
	TreeNode* root = tree.generateTree(nums);

	std::cout << "递归前序遍历：" << std::endl;
	tree.preOrder(root);
	std::cout << std::endl << "非递归1前序遍历：" << std::endl;
	tree.preOrder_NonRecursive_1(root);
	std::cout << std::endl << "非递归2前序遍历：" << std::endl;
	tree.preOrder_NonRecursive_2(root); 
	std::cout << std::endl << "非递归3前序遍历：" << std::endl;
	tree.preOrder_NonRecursive_3(root);
	std::cout << std::endl << "递归中序遍历：" << std::endl;
	tree.InOrder(root);
	std::cout << std::endl << "非递归中序遍历：" << std::endl;
	tree.InOrder_NonRecursive_1(root);
	std::cout << std::endl << "递归后序遍历：" << std::endl;
	tree.PostOrder(root);
	std::cout << std::endl << "非递归后序遍历：" << std::endl;
	tree.PostOrder_Noncursive(root);
	std::cout << std::endl << "非递归后序遍历1：" << std::endl;
	tree.PostOrder_NonRecursive_1(root);
	std::cout << std::endl;
	
	return 0;
}