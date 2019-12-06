#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <vector>
using namespace std;
template<class T>
class BinaryTreeNode
{
	//friend class BinaryTree<T>;
public:
	T element;
	BinaryTreeNode<T>* leftChild;
	BinaryTreeNode<T>* rightChild;

	BinaryTreeNode(T&);
	BinaryTreeNode();
	BinaryTreeNode(const T& ele);
};
template<class T>
class BinaryTree
{
public:
	BinaryTreeNode<T>* root;
	BinaryTree();
	void breadthFirstOrder(BinaryTreeNode<T>* root);		//广度优先遍历以root为根节点的子树
	void preOrder(BinaryTreeNode<T>* root);					//先序遍历
	void inOrder(BinaryTreeNode<T>* root);					//中序遍历
	void postOrder(BinaryTreeNode<T>* root);				//后序遍历
	void visit(BinaryTreeNode<T>* root);					//输出
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);	//先序遍历非递归
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root);	//中序遍历非递归
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);	//后续遍历非递归
	BinaryTreeNode<T>* setTreePreIn(vector<T>, vector<T>);
	BinaryTreeNode<T>* steTreeInPost(vector<T>, vector<T>);
	int FindDegree1(BinaryTreeNode<T>* node);
	int FindDegree2(BinaryTreeNode<T>* node);
	int FindDegree0(BinaryTreeNode<T>* node);
	int TreeDepth(BinaryTreeNode<T>* node);
	int TreeWidth(BinaryTreeNode<T>* node);
	T MaxElement(BinaryTreeNode<T>* node);
	bool isComplete(BinaryTreeNode<T>* root);
	int iscomplete(BinaryTreeNode<T>* root);
	BinaryTreeNode<T>* changeLeftRight(BinaryTreeNode<T>* node);
	BinaryTreeNode<T>* deleteLeave(BinaryTreeNode<T>* node);
};

template<class T>
BinaryTree<T>::BinaryTree():root(NULL){}

template<class T>
void BinaryTree<T>::breadthFirstOrder(BinaryTreeNode<T>* root)
{

	queue< BinaryTreeNode<T>*>nodeQueue;
	BinaryTreeNode<T>* pointer = root;
	
	if (pointer)
		nodeQueue.push(pointer);
	while (!nodeQueue.empty())
	{
		pointer = nodeQueue.front();
		visit(pointer);
		nodeQueue.pop();
		if (pointer->leftChild)
			nodeQueue.push(pointer->leftChild);
		if (pointer->rightChild)
			nodeQueue.push(pointer->rightChild);
	}
}
template<class T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T>* root)			//前序遍历
{
	if (root != NULL)
	{
		visit(root);
		preOrder(root->leftChild);
		preOrder(root->rightChild);
	}
}

template<class T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T>* root)			//中序遍历
{
	if (root != NULL)
	{
		inOrder(root->leftChild);
		visit(root);
		inOrder(root->rightChild);
	}
}

template<class T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T>* root)			//后序遍历
{
	if (root != NULL)
	{
		postOrder(root->leftChild);
		postOrder(root->rightChild);
		visit(root);
	}
}

template<class T>
void BinaryTree<T>::visit(BinaryTreeNode<T>* root)
{
	cout << root->element << "  ";
}

template<class T>
void BinaryTree<T>::PreOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	stack< BinaryTreeNode<T>*>nodeStack;
	BinaryTreeNode<T>* pointer = root;

	while (!nodeStack.empty() || pointer)
	{
		if (pointer)
		{
			visit(pointer);
			if (pointer->rightChild != NULL)
				nodeStack.push(pointer->rightChild);
			pointer = pointer->leftChild;
		}
		else
		{
			pointer = nodeStack.top();
			nodeStack.pop();
		}
	}
}

template<class T>
void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	stack< BinaryTreeNode<T>*>nodeStack;
	BinaryTreeNode<T>* pointer = root;

	while (!nodeStack.empty() || pointer)
	{
		if (pointer)
		{
			nodeStack.push(pointer);
			pointer = pointer->leftChild;
		}
		else
		{
			pointer = nodeStack.top();
			visit(pointer);
			pointer = pointer->rightChild;
			nodeStack.pop();
		}
	}
}

template<class T>
void BinaryTree<T>::PostOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	stack< BinaryTreeNode<T>*>nodeStack;
	BinaryTreeNode<T>* pointer = root;
	BinaryTreeNode<T>* pre = root;

	while (pointer)
	{
		for (; pointer->leftChild != NULL; pointer = pointer->leftChild)
			nodeStack.push(pointer);

		while (pointer != NULL && (pointer->rightChild == NULL || pointer->rightChild == pre))
		{
			visit(pointer);
			pre = pointer;
			if (nodeStack.empty())
				return;
			pointer = nodeStack.top();
			nodeStack.pop();
		}
		nodeStack.push(pointer);
		pointer = pointer->rightChild;
	}
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::setTreePreIn(vector<T> pre, vector<T> in)
{
	if (pre.size() == 0 || in.size() == 0)
		return NULL;

	BinaryTreeNode<T>* node = new BinaryTreeNode<T>(pre[0]);
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] == pre[0])
		{
			node->leftChild = setTreePreIn(vector<T>(pre.begin() + 1, pre.begin() + i + 1), vector<T>(in.begin(), in.begin() + i));
			node->rightChild = setTreePreIn(vector<T>(pre.begin() + i + 1, pre.end()), vector<T>(in.begin() + i + 1, in.end()));
		}
	}
	return node;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::steTreeInPost(vector<T> pos, vector<T> in)
{
	if (pos.size() == 0 || in.size() == 0)
		return NULL;
	BinaryTreeNode<T>* node = new BinaryTreeNode<T>(pos[pos.size() - 1]);
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] == pos[pos.size() - 1])
		{
			node->leftChild = steTreeInPost(vector<T>(pos.begin(), pos.begin() + i), vector<T>(in.begin(), in.begin() + i));
			node->rightChild = steTreeInPost(vector<T>(pos.begin() + i, pos.end() - 1), vector<T>(in.begin() + i + 1, in.end()));
		}
	}
	return node;
}

template<class T>
int BinaryTree<T>::FindDegree1(BinaryTreeNode<T>* node)
{
	if (node != NULL)
	{
		if ((node->leftChild || node->rightChild) && !(node->leftChild && node->rightChild))
			return FindDegree1(node->leftChild) + FindDegree1(node->rightChild) + 1;
		return FindDegree1(node->leftChild) + FindDegree1(node->rightChild);
	}
	return 0;
}

template<class T>
int BinaryTree<T>::FindDegree2(BinaryTreeNode<T>* node)
{
	if (node != NULL)
	{
		if (node->leftChild && node->rightChild)
			return FindDegree2(node->leftChild) + FindDegree2(node->rightChild) + 1;
		return FindDegree2(node->leftChild) + FindDegree2(node->rightChild);
	}
	return 0;
}

template<class T>
int BinaryTree<T>::FindDegree0(BinaryTreeNode<T>* node)
{
	if (node == NULL)
		return 0;
	if (node->leftChild == NULL && node->rightChild == NULL)
		return 1;
	return FindDegree0(node->leftChild) + FindDegree0(node->rightChild);
}

template<class T>
int BinaryTree<T>::TreeDepth(BinaryTreeNode<T>* node)
{
	if (node != NULL) {
		int left = TreeDepth(node->leftChild);
		int right = TreeDepth(node->rightChild);
		return (left > right) ? left + 1 : right + 1;
	}
	return 1;
}
template<class T>
int re(queue<BinaryTreeNode<T>*> nq) {
	if (!nq.empty())
	{
		queue<BinaryTreeNode<T>*> nodequeue;
		int i = 1;
		BinaryTreeNode<T>* tmp;
		while (!nq.empty())
		{
			tmp = nq.front();
			if (tmp->leftChild)
				nodequeue.push(tmp->leftChild);
			if (tmp->rightChild)
				nodequeue.push(tmp->rightChild);
			i++;
			nq.pop();
		}
		int before = re(nodequeue);
		return before > i ? before : i;
	}
	return 0;
}

template<class T>
int BinaryTree<T>::TreeWidth(BinaryTreeNode<T>* node)
{
	if (root != NULL)
	{
		queue<BinaryTreeNode<T>*> nodequeue;
		nodequeue.push(root);
		int width = re(nodequeue);
		return width;
	}
	return 0;
}

template<class T>
T BinaryTree<T>::MaxElement(BinaryTreeNode<T>* node)
{
	T left, right, temp;
	if (node != NULL)
	{
		left = MaxElement(node->leftChild);
		right = MaxElement(node->rightChild);
		temp = (left > right) ? left : right;
		return (node->element > temp) ? node->element : temp;
	}
	return T(0);
}

template<class T>
bool BinaryTree<T>::isComplete(BinaryTreeNode<T>* root)
{
	if (root == NULL)
		return false;
	int du = 2;
	if (root->leftChild == NULL)
		du--;
	if (root->rightChild == NULL)
		du--;
	else if (du == 1)//防止根节点只有一个右孩子
		return false;
	queue<BinaryTreeNode<T>*> nodequeue;
	BinaryTreeNode<T>* node = root;
	nodequeue.push(root);
	while (!nodequeue.empty())
	{
		node = nodequeue.front();
		int tmp = 2;
		if (node->leftChild == NULL)
			tmp--;
		if (node->rightChild == NULL)
			tmp--;
		else if (tmp == 1)
			return false;//防止只有一个孩子是在右孩子
		if (tmp > du)
			return false;
		else
			du = tmp;
		if (node->leftChild)
			nodequeue.push(node->leftChild);
		if (node->rightChild)
			nodequeue.push(node->rightChild);
		nodequeue.pop();
	}
	return true;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::changeLeftRight(BinaryTreeNode<T>* node)
{
	if (node != NULL)
	{
		BinaryTreeNode<T>* right = changeLeftRight(node->rightChild);
		BinaryTreeNode<T>* left = changeLeftRight(node->leftChild);
		node->rightChild = left;
		node->leftChild = right;
		return node;
	}
	return nullptr;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::deleteLeave(BinaryTreeNode<T>* node)
{
	if (node != NULL)
	{
		if (node->leftChild == NULL && node->rightChild == NULL)
		{
			delete node;
			return NULL;
		}
		node->leftChild = deleteLeave(node->leftChild);
		node->rightChild = deleteLeave(node->rightChild);
	}
	return node;
}

int main()
{
	vector<char> preOrder, inOrder, postOrder;
	string pre, in, post;
	pre = "ABECDFGHIJ";
	in = "EBCDAFHIGJ";
	post = "EDCBIHJGFA";
	//cout << "输入先序序列" << endl;
	//cin >> pre;
	//cout << "输入中序序列" << endl;
	//cin >> in;
	//cout << "输入中序序列" << endl;
	//cin >> post;
	for (int i = 0; i < pre.length(); i++)
	{
		preOrder.push_back(pre[i]);
	}
	for (int i = 0; i < in.length(); i++)
	{
		inOrder.push_back(in[i]);
	}
	for (int i = 0; i < post.length(); i++)
	{
		postOrder.push_back(post[i]);
	}
	BinaryTree<char> c;
	c.root = c.setTreePreIn(preOrder, inOrder);
	c.breadthFirstOrder(c.root);
	cout << endl;
	c.InOrderWithoutRecusion(c.root);
	cout << endl;
	c.PreOrderWithoutRecusion(c.root);
	cout << endl;
	c.PostOrderWithoutRecusion(c.root);
	cout << endl;
	cout<< "------------------------------------------------" << endl;
	c.root = c.steTreeInPost(postOrder, inOrder);
	c.inOrder(c.root);
	cout << endl;
	c.preOrder(c.root);
	cout << endl;
	c.postOrder(c.root);
	cout << endl;
	cout << "输出度为1的节点个数:" << endl;
	int a1 = c.FindDegree1(c.root);
	cout << a1 << endl;
	cout << "输出度为2的节点个数:" << endl;
	int a2 = c.FindDegree2(c.root);
	cout << a2 << endl;
	cout << "输出度为0的节点个数:" << endl;
	int a0 = c.FindDegree0(c.root);
	cout << a0 << endl;
	cout << "输出最大元素:" << endl;
	char c0 = c.MaxElement(c.root);
	cout << c0 << endl;
	cout << "交换每个节点的左右孩子:" << endl;
	c.root = c.changeLeftRight(c.root);
	cout << "中序遍历:";
	c.inOrder(c.root);cout << endl;
	cout << "先序遍历:";
	c.preOrder(c.root);cout << endl;
	cout << "删除所有叶子节点:" << endl;
	c.root = c.deleteLeave(c.root);
	cout << "中序遍历:";
	c.inOrder(c.root);cout << endl;
	cout << "先序遍历:";
	c.preOrder(c.root);cout << endl;
	int height = c.TreeDepth(c.root);
	cout << "树的高度:" << endl;
	cout << height << endl;
	cout << "树的宽度:" << endl;
	int width = c.TreeWidth(c.root);
	cout << width << endl;
	cout << "是否为完全二叉树:" << endl;
	int iii = c.iscomplete(c.root);
	cout << iii << endl;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(T& e):element(e),leftChild(NULL),rightChild(NULL){}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode():leftChild(NULL), rightChild(NULL){}
