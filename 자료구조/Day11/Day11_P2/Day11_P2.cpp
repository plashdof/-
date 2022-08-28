#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node {
public:
	int data;
	Node* parent;
	Node* rChild;
	Node* lChild;


	Node() {
		this->data = NULL;
		this->parent = NULL;
		this->rChild = NULL;
		this->lChild = NULL;
	}

	Node(int data) {
		this->data = data;
		this->parent = NULL;
		this->rChild = NULL;
		this->lChild = NULL;
	}


	~Node() {
	}

};


class BST {
public:
	Node* root;
	int height = 0;

	BST() {
		root = NULL;
		height = 0;
	}

	~BST() {
		this->treeDestructor(this->root);
	}

	void insertNode(int data) {

		int temp = 0;		//   삽입 할 때 마다, 높이를 측정!  

		if (root == NULL) {

			Node* v = new Node;
			v->data = data;
			root = v;
		}
		else {
			Node* cur = root;

			while (cur != NULL)
			{
				if (cur->data < data) {

					temp++;

					if (cur->rChild == NULL)
					{
						Node* w = new Node;
						w->parent = cur;
						w->data = data;

						cur->rChild = w;
						break;
					}
					cur = cur->rChild;
				}
				else {

					temp++;

					if (cur->lChild == NULL)
					{
						Node* w = new Node;
						w->parent = cur;
						w->data = data;

						cur->lChild = w;
						break;
					}
					cur = cur->lChild;
				}
			}
		}

		if (height < temp)		// 기존 높이와 비교하여, 높이가 늘어났으면 업데이트
		{
			height = temp;
		}
	}

	int getHeight() {
		return height;
	}


	Node* findNode(int data) {
		Node* cur = root;
		while (cur != NULL)
		{
			if (cur->data == data)
				return cur;
			else {
				if (cur->data < data)
					cur = cur->rChild;
				else
					cur = cur->lChild;
			}
		}

		return NULL;
	}



	void treeDestructor(Node* root) {
		if (root == NULL)
			return;
		if (root->lChild != NULL)
			this->treeDestructor(root->lChild);
		if (root->rChild != NULL)
			this->treeDestructor(root->rChild);
		delete(root);
	}

	void preOrder(Node* x) {
		cout << x->data << " ";
		if (x->lChild != NULL)
			preOrder(x->lChild);
		if(x->rChild != NULL)
			preOrder(x->rChild);
	}


	void Transplant( Node* u, Node* v)
	{
		if (u->parent == NULL)
			root = v;
		else if (u == u->parent->lChild)
			u->parent->lChild = v;
		else u->parent->rChild = v;

		if (v != NULL)
			v->parent = u->parent;
	}


	Node* Treemin( Node* x) {
		if (x->lChild == NULL)
		{
			return x;
		}
		else {
			Node* cur = x;

			while (cur->lChild != NULL)
			{
				cur = cur->lChild;
			}

			return cur;
		}
		
	}


	void DeleteNode(Node* z)
	{
		if (z->lChild == NULL)
			Transplant( z, z->rChild);
		else if (z->rChild == NULL)
			Transplant(z, z->lChild);
		else {
			Node* y = Treemin(z->rChild);
			if (y->parent != z)
			{
				Transplant(y, y->rChild);
				y->rChild = z->rChild;
				y->rChild->parent = y;
			}

			Transplant(z, y);
			y->lChild = z->lChild;
			y->lChild->parent = y;
		}
	}
};



int main() {
	int T = 0;
	int N = 0;
	int M = 0;
	int x = 0;

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N;

		BST BT;

		for (int j = 0; j < N; j++)
		{
			cin >> x;
			BT.insertNode(x);
		}

		cin >> M;

		for (int j = 0; j < M; j++)
		{
			cin >> x;
			BT.DeleteNode(BT.findNode(x));
		}


		BT.preOrder(BT.root);
		cout << "\n";


	}





}
