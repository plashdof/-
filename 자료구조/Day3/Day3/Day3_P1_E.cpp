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

	friend class SLinkedList;
};


class SLinkedList {
public:
	Node* head;
	Node* tail;

	SLinkedList() {
		head = NULL;
		tail = NULL;
	}

	void addFront(int x) {

		Node* v = new Node(NULL);
		v->data = x;
		v->next = head;
		head = v;

		if (empty()) {
			tail = v;
		}
	}

	void removeFront() {
		if (empty()) {
			cout << "-1\n";
			return;
		}

		Node* old = head;

		cout << old->data << "\n";

		head = old->next;
		delete old;


		if (empty()) {
			tail = NULL;
		}

	}

	int front() {
		if (empty()) {
			return -1;
		}

		return head->data;
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




int main() {
	int N = 0;
	int x = 0;
	string S = "";


	SLinkedList A;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> S;
		if (S == "empty")
		{
			cout << A.empty() << "\n";
		}
		if (S == "front")
		{
			cout << A.front() << "\n";
		}
		if (S == "addFront")
		{
			cin >> x;
			A.addFront(x);
		}
		if (S == "removeFront")
		{
			A.removeFront();
		}
	}


	return 0;
}