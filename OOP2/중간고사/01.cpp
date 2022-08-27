#include <iostream>
#include <random>
#include <iomanip>
#include <string>
using namespace std;

void printGroup(string* students, int* scores, int stuNum);
void printGroup(string* students, int* scores, int* otherGroup, int stuNum);

int main() {
	string students[] = {
		"공민선", "김민경", "김보겸", "김성원", "김세희", "김영범", "김영인", "김지연", "김푸름", "박소현",
		"박준혁", "박진성", "박태남", "반웅재", "서동우", "서희환", "송치헌", "심원주", "안지현", "여민영",
		"오영주", "유영진", "이강", "이채은", "이태희", "정휘진", "최경일", "최준혁", "최찬규", "하대훈",
		"하지민", "한예원", "황태준"
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

	cout << "*****계절학기 성적 확인 프로그램*****" << endl;
	cout << "1) 전체 점수 확인" << endl;
	cout << "2) 그룹별 점수 확인" << endl;
	cout << "3) 개인 점수 확인" << endl;
	cout << "4) 종료" << endl;

	string command;
	getline(cin, command);

	while (command != "4") {
		if (command == "1") {
			printGroup(students, scores, maxstudents);
			float av = totalGrade / maxstudents;

			cout << endl << "평균: " << av << endl;
		}
		else if (command == "2") {
			cout << "=== A ===" << endl;
			printGroup(students, groupA, scores, stu_A);
			cout << "총인원: " << stu_A << endl;

			cout << "=== B ===" << endl;
			printGroup(students, groupB, scores, stu_B);
			cout << "총인원: " << stu_B << endl;

			cout << "=== C ===" << endl;
			printGroup(students, groupC, scores, stu_C);
			cout << "총인원: " << stu_C << endl;
		}
		else if (command == "3") {
			cout << "이름을 입력하세요 : ";
			string name;
			getline(cin, name);

			for (int i = 0; i < maxstudents; i++) {
				if (students[i] == name) {
					cout << scores[i] << endl;
					cout << "담당교수 피드백 : ";

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
			cout << "올바른 숫자를 입력해주세요" << endl;
		}

		cout << endl << "1) 전체 점수 확인" << endl;
		cout << "2) 그룹별 점수 확인" << endl;
		cout << "3) 개인 점수 확인" << endl;
		cout << "4) 종료" << endl;
		getline(cin, command);
	}

	delete[] groupA;
	delete[] groupB;
	delete[] groupC;

	groupA = nullptr;
	groupB = nullptr;
	groupC = nullptr;

	cout << "프로그램 종료" << endl;
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