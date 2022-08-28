#include <iostream>
#include <string>
using namespace std;

class arrayStack {
public:
	int* S;
	int capacity;
	int t;

	arrayStack(int capacity) {
		this->capacity = capacity;
		this->S = new int[capacity];
		this->t = -1;
	}


	int empty() {
		if (t == -1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	int top() {
		if (empty())
		{
			return -1;
		}
		return S[t];
	}

	void push(int e) {
		if (t == capacity - 1)
		{
			return;
		}
		S[t + 1] = e;
		t++;
	}



};

int main()
{
	int N = 0;
	string s = "";
	int x = 0;

	arrayStack A(10000);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> s;

		if (s == "empty")
		{
			cout << A.empty() << "\n";
		}

		if (s == "top")
		{
			cout << A.top() << "\n";
		}

		if (s == "push")
		{
			cin >> x;
			A.push(x);
		}
	}



	return 0;
}