#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Generator
{
private:
	int num1 = 0;
	int num2 = 0;


public:

	void make_number()
	{
		srand(static_cast<int>(time(0)));

		num1 = rand() % 9 + 1;
		num2 = rand() % 9 + 1;
	}
	
	int get_num1()
	{
		return num1;
	}

	int get_num2()
	{
		return num2;
	}

	void right_answer()
	{
		srand(static_cast<int>(time(0)));

		int num = rand() % 4;

		switch (num)
		{
		case 0:
			cout << "Very good!";
			break;
		case 1:
			cout << "Excellent!";
			break;
		case 2:
			cout << "Nice Work!";
			break;
		case 3:
			cout << "Keep up the good work!";
		}
	}

	void wrong_answer()
	{
		srand(static_cast<int>(time(0)));

		int num = rand() % 4;

		switch (num)
		{
		case 0:
			cout << "No. Please try again";
			break;
		case 1:
			cout << "Wrong. Try once more.";
			break;
		case 2:
			cout << "Don't give up!";
			break;
		case 3:
			cout << "No. Keep trying.";
		}
	}
};

int main()
{
	Generator test;


	while (1)
	{
		test.make_number();
		int answer = test.get_num1() * test.get_num2();
		int guess = 0;

		cout << "How much is " << test.get_num1() << " * " << test.get_num2() << " ?";

		cin >> guess;

		while (guess != answer)
		{
			test.wrong_answer();
			cin >> guess;
		}

		test.right_answer();
		cout << "\n";

	}
	

	return 0;
}