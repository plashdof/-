#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node {
public:

	int data;
	Node* par;
	vector<Node*> chi;

	Node() {
		this->data = NULL;
		this->par = NULL;
	}

	Node(int data) {
		this->data = data;
		this->par = NULL;
	}

	~Node() {
	}

	int get_data() {
		return this->data;
	}

	Node* get_par() {
		return par;
	}

	void insertChild(Node* chi) {		// 추가할 chi노드의 par 에 현재 Node 집어넣음
		chi->par = this;
		this->chi.push_back(chi);
		return;
	}

	void delChild(Node* chi) {

		for (int i = 0; i < this->chi.size(); i++) {
			if (this->chi[i] == chi) {
				this->chi.erase(this->chi.begin() + i);
				break;
			}
		}

		return;
	}
};

class GeneralTree {
private:
	Node* root;
	vector<Node*> node_list;


public:
	GeneralTree() {
		root = NULL;
	}

	GeneralTree(int data) {
		root = new Node(data);
		node_list.push_back(root);
	}

	~GeneralTree() {
	}

	Node* findNode(int data) {
		for (int i = 0; i < node_list.size(); i++)
		{
			if (node_list[i]->get_data() == data)
			{
				return node_list[i];
			}
			else {
				continue;
			}
		}
	}

	int Empty(int data) {
		for (int i = 0; i < node_list.size(); i++)
		{
			if (node_list[i]->get_data() == data)
			{
				return 0;
			}
		}

		return 1;
	}

	void insertNode(int par_data, int data)
	{
		if (Empty(par_data))
		{
			cout << "-1\n";
		}
		else
		{
			Node* v = new Node(data);

			findNode(par_data)->insertChild(v);
			node_list.push_back(v);
		}


	}

	void printChild(int data) {
		if (Empty(data))
		{
			cout << "-1\n";
		}
		else
		{
			vector<Node*> v = findNode(data)->chi;

			if (v.empty())
			{
				cout << "0\n";
			}
			else
			{
				for (int i = 0; i < v.size(); i++)
				{
					cout << v[i]->get_data() << " ";
				}

				cout << "\n";
			}
		}
	}

	void printDepth(int data) {
		if (Empty(data))
		{
			cout << "-1\n";
		}
		else {

			Node* cur = findNode(data);
			int count = 0;

			while (root != cur)
			{
				cur = cur->get_par();
				count++;
			}

			cout << count << "\n";
		}
	}

};


void preOrder(GeneralTree T, int data)
{
	cout << data << " ";
	
	for (int i = 0; i < (T.findNode(data))->chi.size(); i++)	//  트리 T 에서 해당데이터 노드 찾은뒤
												                // 해당 노드의 chi 벡터의 원소수 반환
	{
		preOrder(T, (T.findNode(data))->chi[i]->data);
	}
	
}

void postOrder(GeneralTree T, int data)
{
	for (int i = 0; i < (T.findNode(data))->chi.size(); i++)	
	{
		postOrder(T, (T.findNode(data))->chi[i]->data);
	}

	cout << data << " ";

}



int main() {
	int N = 0;
	int M = 0;
	int x = 0;
	int y = 0;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		GeneralTree T(1);

		cin >> M;

		for (int j = 0; j < M; j++)
		{
			cin >> x;
			cin >> y;
			T.insertNode(x, y);
		}

		preOrder(T, 1);
		cout << "\n";

		postOrder(T, 1);
		cout << "\n";

	}
}