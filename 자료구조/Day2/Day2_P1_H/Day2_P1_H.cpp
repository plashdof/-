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

	// at ��� ����

	int at(int idx) {
		return arr[idx];
	}


	// set ��� ����

	void set(int idx, int x) {

		if (arr[idx] == 0) {  // �迭 ��������� ����ó��
			cout << 0 << "\n";
		}

		else {
			arr[idx] = x;
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
			for (int i = n - 2; i >= idx; i--)
			{
				arr[i + 1] = arr[i];
			}

			arr[idx] = num;
		}


	}


	// remove ��� ����

	void remove(int idx) {


		if (arr[idx] != 0)
		{
			cout << arr[idx] << "\n";
		

			arr[idx] = 0;    //  �ش� �ε��� ���� ����
			for (int i = idx + 1; i < n; i++) 
			{                           //  idx + 1 ������ -1ĭ�� �̵�
				arr[i - 1] = arr[i];
			}
		}
		else   //  �迭 ��������� ����ó��
		{
			cout << 0 << "\n";
		}
		
	}



	// printArray ��� ����

	void printArray() {
		if (arr[0] == 0)   //  �迭 ��ü�� �� �迭�϶� ����ó��
		{
			cout << "0\n";
		}

		else {
			for (int i = 0; i < n; i++)
			{    
				if (arr[i] == 0)   // �迭 ���̸� �ݺ��� Ż��
				{
					break;
				}
				
					//  �迭 ���� ������� ��ºκ�
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

	for (int i = 0; i < M; i++)     //   ��ɾ �޾Ƽ�, �� ��ɾ� ���� �޼ҵ� ����
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