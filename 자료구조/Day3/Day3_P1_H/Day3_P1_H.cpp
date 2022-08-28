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

		if (empty()) {
			tail = v;
		}

		v->data = x;
		v->next = head;
		head = v;

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

	void showList() {
		if (empty())
		{
			cout << "-1\n";
			return;
		}
		
		Node* cur = head;
		while (cur->next != NULL)
		{
			cout << cur->data << " ";
			cur = cur->next;
		}
		cout << cur->data << "\n";
		

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
		if (S == "showList")
		{
			A.showList();
		}
		if (S == "addBack")
		{
			cin >> x;
			A.addBack(x);
		}
	}

	return 0;
}