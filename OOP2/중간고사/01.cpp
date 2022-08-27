#include <iostream>
#include <random>
#include <iomanip>
#include <string>
using namespace std;

void printGroup(string* students, int* scores, int stuNum);
void printGroup(string* students, int* scores, int* otherGroup, int stuNum);

int main() {
	string students[] = {
		"���μ�", "��ΰ�", "�躸��", "�輺��", "�輼��", "�迵��", "�迵��", "������", "��Ǫ��", "�ڼ���",
		"������", "������", "���³�", "�ݿ���", "������", "����ȯ", "��ġ��", "�ɿ���", "������", "���ο�",
		"������", "������", "�̰�", "��ä��", "������", "������", "�ְ���", "������", "������", "�ϴ���",
		"������", "�ѿ���", "Ȳ����"
	};
	const int maxstudents = sizeof(students) / sizeof(students[0]);
	int scores[maxstudents];
	int stu_A = 0;
	int stu_B = 0;
	int stu_C = 0;
	float totalGrade = 0;

	default_random_engine rng(static_cast<unsigned int>(time(nullptr)));
	uniform_int_distribution<int> dist(0, 30);

	for (int i = 0; i < maxstudents; i++) {
		int score = dist(rng);
		scores[i] = score;
		totalGrade = totalGrade + score;

		if (score > 19) {
			stu_A++;
		}
		else if (score > 9 && score < 20) {
			stu_B++;
		}
		else {
			stu_C++;
		}
	}

	int* groupA = new int[stu_A];
	int* groupB = new int[stu_B];
	int* groupC = new int[stu_C];
	int indexA = 0;
	int indexB = 0;
	int indexC = 0;

	for (int i = 0; i < maxstudents; i++) {
		if (scores[i] > 19) {
			groupA[indexA] = i;
			indexA++;
		}
		else if (scores[i] > 9 && scores[i] < 20) {
			groupB[indexB] = i;
			indexB++;
		}
		else {
			groupC[indexC] = i;
			indexC++;
		}
	}

	cout << "*****�����б� ���� Ȯ�� ���α׷�*****" << endl;
	cout << "1) ��ü ���� Ȯ��" << endl;
	cout << "2) �׷캰 ���� Ȯ��" << endl;
	cout << "3) ���� ���� Ȯ��" << endl;
	cout << "4) ����" << endl;

	string command;
	getline(cin, command);

	while (command != "4") {
		if (command == "1") {
			printGroup(students, scores, maxstudents);
			float av = totalGrade / maxstudents;

			cout << endl << "���: " << av << endl;
		}
		else if (command == "2") {
			cout << "=== A ===" << endl;
			printGroup(students, groupA, scores, stu_A);
			cout << "���ο�: " << stu_A << endl;

			cout << "=== B ===" << endl;
			printGroup(students, groupB, scores, stu_B);
			cout << "���ο�: " << stu_B << endl;

			cout << "=== C ===" << endl;
			printGroup(students, groupC, scores, stu_C);
			cout << "���ο�: " << stu_C << endl;
		}
		else if (command == "3") {
			cout << "�̸��� �Է��ϼ��� : ";
			string name;
			getline(cin, name);

			for (int i = 0; i < maxstudents; i++) {
				if (students[i] == name) {
					cout << scores[i] << endl;
					cout << "��米�� �ǵ�� : ";

					if (scores[i] > 19) {
						cout << "U deserve it!" << endl;
					}
					else if (scores[i] > 9 && scores[i] < 20) {
						cout << "Well done" << endl;
					}
					else {
						cout << "good" << endl;
					}
				}
			}
		}
		else {
			cout << "�ùٸ� ���ڸ� �Է����ּ���" << endl;
		}

		cout << endl << "1) ��ü ���� Ȯ��" << endl;
		cout << "2) �׷캰 ���� Ȯ��" << endl;
		cout << "3) ���� ���� Ȯ��" << endl;
		cout << "4) ����" << endl;
		getline(cin, command);
	}

	delete[] groupA;
	delete[] groupB;
	delete[] groupC;

	groupA = nullptr;
	groupB = nullptr;
	groupC = nullptr;

	cout << "���α׷� ����" << endl;
	return 0;
}

void printGroup(string* students, int* scores, int stuNum) {
	for (int i = 0; i < stuNum; i++) {
		cout << students[i] << " : " << *(scores + i) << " ";

		if ((i + 1) % 5 == 0)
			cout << endl;
		else if (i == stuNum-1)
			cout << endl;
	}
}

void printGroup(string* students, int* otherGroup, int* scores, int stuNum) {
	for (int i = 0; i < stuNum; i++) {
		cout << students[otherGroup[i]] << " : " << *(scores + otherGroup[i]) << " ";

		if ((i + 1) % 5 == 0)
			cout << endl;
		else if (i == stuNum - 1)
			cout << endl;
	}
}