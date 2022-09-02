#include <iostream>
using namespace std;

void tree(int a);

int main()
{
	for (int i = 1; i <= 4; i++)  
	{
		tree(i);
		cout << "\n";
	}


	return 0;
}

void tree(int a)
{
	for (int j = 1; j <= a; j++)  // ÃþÀ» ³ªÅ¸³¿.
	{
		for (int i = 1; i <= a - j; i++)   // ¾ÕÀÇ ºóÄ­
		{
			cout << " ";
		}

		for (int i = 1; i <= j; i++)     // º° ºÎºÐ
		{
			cout << "* ";
		}

		cout << "\n";
	}
	

}