#include <iostream>
#include <string>
using namespace std;

class arrQueue {
public:

	int f;
	int r;
	int capacity;
	int* Q;

	arrQueue(int size)
	{
		this->capacity = size + 1;        //  Full 과 Empty 구분 위해 capacity 한칸 더 설정
		this->Q = new int[size + 1];
		this->f = 0;
		this->r = -1;
	}

	int isEmpty() {
		if (r == f - 1 || (f == 0 && r == capacity - 1))    //   f = 0 그리고 r = 최대인 경우 예외처리
		{
			return 1;
		}
		else
		{
			return 0;

		}
	}

	int size(){
		if (isEmpty()) {
			return 0;
		}
		else
		{
			if (f <= r)
			{
				return r - f + 1;
			}
			else {
				return r - f + 1 + capacity;
			}
		}
	}

	void enqueue(int x) {
		if (size() == capacity-1)
		{
			cout << "FULL\n";
		}
		else {
			if (r + 1 == capacity)
			{
				r = 0;
			}
			else {
				r++;
			}

			Q[r] = x;
		}
	}

	void dequeue() {
		if (isEmpty()) {
			cout << "Empty\n";
		}
		else {

			cout << Q[f] << "\n";

			if (f + 1 == capacity)
			{
				f = 0;
			}
			else {
				f++;
			}

			
		}
	}

	void front() {
		if (isEmpty())
		{
			cout << "Empty\n";
		}
		else {
			cout << Q[f] << "\n";
		}
	}

	void rear() {
		if (isEmpty())
		{
			cout << "Empty\n";
		}
		else {
			cout << Q[r] << "\n";
		}
	}
};


int main() {
	int S = 0;
	int N = 0;
	int x = 0;
	string s = "";

	cin >> S;

	arrQueue A(S);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> s;

		if (s == "isEmpty")
		{
			cout << A.isEmpty() << "\n";
		}

		if (s == "size")
		{
			cout << A.size() << "\n";
		}

		if (s == "enqueue")
		{
			cin >> x;
			A.enqueue(x);
		}

		if (s == "dequeue")
		{
			A.dequeue();
		}

		if (s == "front")
		{
			A.front();
		}

		if (s == "rear")
		{
			A.rear();
		}
	}


}