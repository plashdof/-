#include <iostream>
#include <string>

using namespace std;

int arr[101] = { 0 };

int main() {

	int M = 0, N = 0, temp = 0;
	int Kor = 0, Jap = 0, Chi = 0;

	cin >> M;

	for (int i = 0; i < M; i++)
	{
		cin >> N;
		for (int j = 0; j < N; j++)
		{
			cin >> temp;
			arr[j] = temp;
		}


		for (int j = 0; j < N; j = j + 3)
		{
			Kor += arr[j];
			Jap += arr[j + 1];
			Chi += arr[j + 2];
		}

		cout << Kor << " " << Jap << " " << Chi << "\n";
		Kor = 0, Jap = 0, Chi = 0;

		for (int j = 0; j < N; j++)
		{
			arr[j] = 0;
		}
	}

	

}

//5
//9
//150 12 10 0 96 89 19 630 96
//6
//120 23 45 21 
//5
//33 45 67 756 234
//3
//111 13 43
//7
//134 0 66 753 0 23 2