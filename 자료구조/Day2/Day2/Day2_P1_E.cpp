#include <iostream>
#include <string>
using namespace std;


// Array Ŭ���� ����
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


	// at ��� ����
	int at(int idx) {
		return arr[idx];    // �ε��� ���� �״�� ��ȯ
	}

	// set ��� ����
	void set(int idx, int x) {

		if (arr[idx] == 0) {   //  0 �϶� 0 ���
			cout << 0 << "\n";
		}

		else {
			arr[idx] = x;    //  0 �ƴҶ�, �����
		}

	}


	// add ��� ����
	void add(int idx, int num) {
		if (arr[idx] == 0) {     //  �ش��ڸ� ���� 0 �ϰ��
			if (idx == 0)     // �ε��� ���� 0 �ΰ��
			{
				arr[0] = num;
			}

			else {     // �ε����� 0 �� �ƴ� ���
				for (int i = idx - 1; i >= 0; i--)
				{
					//  ��ĭ�� �������� ���� 0 �ƴ� �ε��� ã��	 

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

		else {    // �ش��ڸ� ���� 0 �ƴ� ���
			for (int i = n; i >= idx; i--)
			{
				arr[i + 1] = arr[i];
			}

			arr[idx] = num;
		}


	}

};

int main() {

	Array A(10001);   //   ũ�� 10000�� �迭��ü ����

	int M = 0;
	cin >> M;  
	string command = "";
	int idx = 0;
	int num = 0;

	for (int i = 0; i < M; i++)
	{
		cin >> command;      //    ��� �Է� ����
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