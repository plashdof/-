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

	int size() {
		return t + 1;
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

	int pop() {
		if (empty())
		{
			return -1;
		}
		else
		{
			t--;
			return S[t+1];
			
		}
	}

};


int calPostfix(string exp) {

	arrayStack S(1000);

	string postfix = exp;

	int n = postfix.size();
	char testch;

	int a = 0;
	int b = 0;

	for (int i = 0; i < n; i++) {
		testch = exp.at(i);

		int x = testch - '0';

		if (1 <= x && x <= 9)
		{
			S.push(x);
		}
		else {
			a = S.pop();
			b = S.pop();

			if (testch == '+')
			{
				S.push(a + b);
			}

			if (testch == '-')
			{
				S.push(b - a);
			}

			if (testch == '*')
			{
				S.push(a * b);
			}
		}

	}

	return S.top();

}


int main()
{
	int N = 0;
	string s = "";

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> s;

		cout << calPostfix(s) << "\n";
	}


	return 0;
}