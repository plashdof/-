#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int e) {
		this->data = e;
		this->next = NULL;
	}

};


class CLinkedList {
public:
	Node* head;
	Node* tail;

	CLinkedList() {
		head = NULL;
		tail = NULL;
	}

	void addBack(int x) {
		Node* v = new Node(NULL);
		v->data = x;
		v->next = NULL;

		if (empty()) {
			head = tail = v;
		}
		else {
			tail->next = v;
			tail = v;
			tail->next = head;
		}
	}

	void Delete(int x) {
		Node* v = new Node(NULL);
		Node* v_back = new Node(NULL);

		v = head;

		x = x % 10;

		if (x == 0)
		{
			removeFront();
		}
		else {
			
			for (int i = 0; i < x; i++)
			{
				if (i == x - 1)
				{
					v_back = v;
				}
				v = v->next;
			}

			remove(v_back, v);
		}
		


	}

	void removeFront() {

		Node* old = head;

		head = old->next;
		tail->next = head;

		delete old;


	}


	void remove(Node* v_back, Node* v) {

		Node* old = v;

		v = old->next;
		v_back->next = v;
		delete old;

	}

	void showList() {
		if (empty())
		{
			cout << "-1\n";
			return;
		}

		Node* cur = head;
		while (cur->next != head)
		{
			cout << cur->data << " ";
			cur = cur->next;
		}
		cout << cur->data << "\n";

	}

	int empty() {
		if (head == NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

};


int main()
{
	int N = 0;
	int x = 0;
	string s = "";
	

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		CLinkedList C;

		for (int j = 0; j < 10; j++)
		{
			cin >> x;
			C.addBack(x);
		}

		

		for (int j = 0; j < 3; j++)
		{
			cin >> s;
			cin >> x;
			C.Delete(x);

		}

		C.showList();
	}
}



/*
3
15 54 64 86 6 23 57 89 999 14
Delete 8
Delete 0
Delete 5
34 22 2 33 56 89 87 335 446 2
Delete 9
Delete 1
Delete 7


*/