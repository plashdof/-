#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int arr[101] = { 0 };

int main() {


	int M = 0, N = 0, temp = 0;
	int Kor = 0, Jap = 0, Chi = 0;
	int Kor_count = 0, Jap_count = 0, Chi_count = 0;


	cin >> M;


	for (int i = 0; i < M; i++)
	{
		cin >> N;

		// 각 나라별, 저금한 사람 명수 저장

		if (N % 3 == 0)
		{
			Kor_count = (N / 3);
			Jap_count = (N / 3);
			Chi_count = (N / 3);
		}
		else if (N % 3 == 1)
		{
			Kor_count = floor(N / 3) + 1;
			Jap_count = floor(N / 3);
			Chi_count = floor(N / 3);
		}
		else
		{
			Kor_count = floor(N / 3) + 1;
			Jap_count = floor(N / 3) + 1;
			Chi_count = floor(N / 3);
		}



		for (int j = 0; j < N; j++)
		{
			cin >> temp;
			arr[j] = temp;
		}


		for (int j = 0; j < N; j = j + 3)
		{
			// 각 나라별, 총 금액 합산

			Kor += arr[j];
			Jap += arr[j + 1];
			Chi += arr[j + 2];

			// 각 나라별, 0이 들어가 있는 금고, 명수에서 뺴주기

			if (arr[j] == 0)
			{
				Kor_count--;
			}
			if (j+1 < N && arr[j + 1] == 0)
			{
				Jap_count--;
			}
			if (j+2 < N && arr[j + 2] == 0)
			{
				Chi_count--;
			}
		}

		int K = 0, J = 0, C = 0;


		if (Kor_count != 0)
		{
			K = floor(Kor / Kor_count);
		}
		if (Jap_count != 0)
		{
			J = floor(Jap / Jap_count);
		}
		if (Chi_count != 0)
		{
			C = floor(Chi / Chi_count);
		}

		cout << Kor << " " << Jap << " " << Chi << "\n";

		cout << K << " "
			<< J << " "
			<< C << "\n";

		Kor = 0, Jap = 0, Chi = 0;

		for (int j = 0; j < N; j++)
		{
			arr[j] = 0;
		}
	}



}