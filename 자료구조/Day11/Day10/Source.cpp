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

	void insertleft(Node* lChild) {
		this->lChild = lChild;
		lChild->parent = this;
	}

	void insertright(Node* rChild) {
		this->rChild = rChild;
		rChild->parent = this;
	}


	void printDegree() {
		int count = 0;

		if (rChild != NULL)
		{
			count++;
		}

		if (lChild != NULL)
		{
			count++;
		}

		cout << count << " ";
	}


	void printDepth() {
		Node* cur = this;
		int Depth = 0;

		while (cur->parent != NULL)
		{
			cur = cur->parent;
			Depth++;
		}

		cout << Depth << " ";
	}
};


class BST {
public:
	Node* root;
	int height;

	BST() {
		root = NULL;
		height = 0;
	}

	~BST() {
		this->treeDestructor(this->root);
	}

	void insertNode(int data) {

		int height = 0;
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

};





int main() {
	int T = 0;
	int N = 0;
	int x = 0;
	int M = 0;
	

	

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		BST BT;

		cin >> N;

		for (int j = 0; j < N; j++)
		{
			cin >> x;
			BT.insertNode(x);
		}

		cin >> M;

		vector<int> v;

		for (int j = 0; j < M; j++)
		{
			cin >> x;
			v.push_back(x);
		}

		for (int j = 0; j < M; j++)
		{

			if (BT.findNode(v[j]) == NULL)    //  BST 에 없는 노드일 경우 예외처리
			{
				cout << "0\n";
			}
			else {
				(BT.findNode(v[j]))->printDegree();
				(BT.findNode(v[j]))->printDepth();
				cout << "\n";
			}
		}
	}

	return 0;
}