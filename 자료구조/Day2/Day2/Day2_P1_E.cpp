#include <iostream>
#include <string>
using namespace std;


// Array 클래스 설계
class Array {
public:
	int n;
	int* arr;


	Array(int size) {
		this->n = size;
		this->arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = 0;
		}
	}


	// at 기능 구현
	int at(int idx) {
		return arr[idx];    // 인덱스 원소 그대로 반환
	}

	// set 기능 구현
	void set(int idx, int x) {

		if (arr[idx] == 0) {   //  0 일때 0 출력
			cout << 0 << "\n";
		}

		else {
			arr[idx] = x;    //  0 아닐때, 덮어쓰기
		}

	}


	// add 기능 구현
	void add(int idx, int num) {
		if (arr[idx] == 0) {     //  해당자리 원소 0 일경우
			if (idx == 0)     // 인덱스 또한 0 인경우
			{
				arr[0] = num;
			}

			else {     // 인덱스는 0 이 아닌 경우
				for (int i = idx - 1; i >= 0; i--)
				{
					//  한칸씩 내려가며 원소 0 아닌 인덱스 찾기	 

					if (arr[i] == 0) {
						if (i == 0) {
							arr[0] = num;
							break;
						}
						else {
							continue;
						}
						
					}
					else {
						arr[i + 1] = num;
						break;
					}
				}
			}

		}

		else {    // 해당자리 원소 0 아닌 경우
			for (int i = n; i >= idx; i--)
			{
				arr[i + 1] = arr[i];
			}

			arr[idx] = num;
		}


	}

};

int main() {

	Array A(10001);   //   크기 10000의 배열객체 생성

	int M = 0;
	cin >> M;  
	string command = "";
	int idx = 0;
	int num = 0;

	for (int i = 0; i < M; i++)
	{
		cin >> command;      //    명령 입력 받음
		if (command == "at")
		{
			cin >> idx;
			cout << A.at(idx) << "\n";
		}

		if (command == "set")
		{
			cin >> idx >> num;
			A.set(idx, num);
		}

		if (command == "add")
		{
			cin >> idx >> num;
			A.add(idx, num);
		}
	}

	return 0;
}