#include <iostream>
#include <string>
using namespace std;


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
		return arr[idx];
	}


	// set 기능 구현

	void set(int idx, int x) {

		if (arr[idx] == 0) {  // 배열 비어있을때 예외처리
			//cout << 0;
			cout << 0 << "\n";	// <--------- 코드 수정
		}

		else {
			arr[idx] = x;
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
			//for (int i = n; i >= idx; i--)
			for (int i = n - 2; i >= idx; i--)		// <--------- 코드 수정
			{
				arr[i + 1] = arr[i];
			}
			arr[idx] = num;
		}
	}


	// remove 기능 구현

	void remove(int idx) {


		if (arr[idx] != 0)
		{
			cout << arr[idx] << "\n";		// <--------- 코드 추가
			arr[idx] = 0;    //  해당 인덱스 원소 삭제
			for (int i = idx + 1; i < n; i++)
			{                           //  idx + 1 값부터 -1칸씩 이동
				arr[i - 1] = arr[i];
			}
		}
		else   //  배열 비어있을때 예외처리
		{
			cout << 0 << "\n";
		}

	}



	// printArray 기능 구현

	void printArray() {
		if (arr[0] == 0)   //  배열 자체가 빈 배열일때 예외처리
		{
			cout << "0\n";
		}

		else {
			for (int i = 0; i < n; i++)
			{
				if (arr[i] == 0)   // 배열 끝이면 반복문 탈출
				{
					break;
				}

				//  배열 원소 순서대로 출력부분
				cout << arr[i] << " ";


			}
			cout << "\n";
		}


	}

};

int main() {

	Array A(10000);

	int M = 0;
	cin >> M;
	string command = "";
	int idx = 0;
	int num = 0;

	for (int i = 0; i < M; i++)     //   명령어를 받아서, 각 명령어 마다 메소드 수행
	{
		cin >> command;

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

		if (command == "remove")
		{
			cin >> idx;
			A.remove(idx);
		}

		if (command == "printArray")
		{
			A.printArray();
		}
	}

	return 0;
}

/*
9
remove 1
printArray
add 0 1
add 0 2
printArray
add 1 3
remove 0
printArray
at 1

*/
