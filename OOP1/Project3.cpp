#include <iostream>
using namespace std;

int recursion(int num);


int main()
{
	int num = 0;
	cout << "���� ���� �Է��Ͻÿ� : ";
	cin >> num;

	for (int i = 1; i <= num; i++)
	{
		cout << recursion(i) << " ";
	}

	return 0;
}

int recursion(int num)
{
	if (num == 1 || num == 2 || num == 3 || num == 4)
	{
		return num;
	}
	else
	{
		return recursion(num - 2) + recursion(num - 4);
	}
}