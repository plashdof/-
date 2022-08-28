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

	~arrQueue() {
		delete[] Q;
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

	int size() {
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
		if (size() == capacity - 1)
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

	int dequeue() {
		if (isEmpty()) {
			cout << "Empty\n";
			return 0;
		}
		else {

			if (f + 1 == capacity)
			{
				f = 0;
				return Q[capacity - 1];
			}
			else {
				f++;
				return Q[f - 1];
			}

		}
	}
	
};

int main() {
	int T = 0;
	cin >> T;

	int N = 0;
	int x = 0;
	int y = 0;

	int P1 = 0;
	int P2 = 0;

	for (int i = 0; i < T; i++)
	{
		cin >> N;
		arrQueue A(N);

		for (int j = 0; j < N; j++)
		{
			cin >> x;
			A.enqueue(x);
		}

		arrQueue B(N);

		for (int j = 0; j < N; j++)
		{
			cin >> y;
			B.enqueue(y);
		}


		for (int i = 0; i < N; i++)
		{
			int a = A.dequeue();
			int b = B.dequeue();

			if (a > b)
			{
				P1++;
			}
			else if (a < b)
			{
				P2++;
			}
		}


		if (P1 > P2)
		{
			cout << "1\n";
		}
		else if (P1 < P2)
		{
			cout << "2\n";
		}
		else
		{
			cout << "0\n";
		}

		P1 = 0;
		P2 = 0;
	}

	

	return 0;
}