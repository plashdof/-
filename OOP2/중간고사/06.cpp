#include <iostream>
#include <random>
#include <iomanip>
#include<string>
using namespace std;
enum grade {A,B,C };

class Student {

private:
	string name;
	int score;
	int grade;
	
	
public:
	Student();
	Student(string name, int score);
	Student(Student& stu);
	void setName(string name) {
		this->name = name;
	}
	void setScore(int score) {
		this->score = score;
	}
	void setGrade(int grade) {
		this->grade = grade;
	}
	string getName() {
		return name;
	}
	int getScore() {
		return score;
	}
	int getGrade() {
		return grade;
	}
};

Student::Student() {
	this->name = "";
	this->score = 0;
	this->grade = C;
}
Student::Student(Student& stu) {
	this->name = name;
	this->score = score;
	this->grade = grade;
}
Student::Student(string _name, int score) {
	this->name = _name;
	this->score = score;
	
}

int main() {
	int population = 33;
	int countA = 0;
	int countB = 0;
	int countC = 0;
	int average = 0;
	string names[33] = { "공민선", "김민경", "김보겸", "김성원", "김세희", "김영범", "김영인", "김지연", "김푸름", "박소현",
"박준혁", "박진성", "박태남", "반웅재", "서동우", "서희환", "송치헌", "심원주", "안지현", "여민영",
"오영주", "유영진", "이강", "이채은", "이태희", "정휘진", "최경일", "최준혁", "최찬규", "하대훈",
"하지민", "한예원", "황태준" };
	default_random_engine eng(static_cast<unsigned int>(time(nullptr)));
	random_device seed;
	mt19937 engs(seed());
	uniform_int_distribution<int> dist(0, 30);
	Student* all_student = nullptr;
	all_student = new Student[population];
	for (int i = 0; i < population; i++) {
		all_student[i].setName(names[i]);
		int score = dist(eng);
		average += score;
		all_student[i].setScore(score);
		if (score >= 20) {
			all_student[i].setGrade(A);
			countA++;
		}
		else if (score < 20 && score >= 10) {
			all_student[i].setGrade(B);
			countB++;
		}
		else if (score < 10) {
			all_student[i].setGrade(C);
			countC++;
		}
	}
	average = average / population;
	Student* group_A = nullptr;
	Student* group_B = nullptr;
	Student* group_C = nullptr;
	group_A = new Student[countA];
	group_B = new Student[countB];
	group_C = new Student[countC];
	int cntA = 0;
	int cntB = 0;
	int cntC = 0;
	for (int j = 0; j < population; j++) {
		if (all_student[j].getGrade() == A) {
			group_A[cntA] = all_student[j];
			cntA++;
			
		}else if (all_student[j].getGrade() == B) {
			group_B[cntB] = all_student[j];
			cntB++;
			
		}else if (all_student[j].getGrade() == C) {
			group_C[cntC] = all_student[j];
			cntC++;
		}
	}
	auto print = [](int population, Student stu_arr[]) {
		for (int i = 0; i < population; i++) {
			if (i % 5 == 0) {
				cout << endl;
			}
			
			cout << stu_arr[i].getName() << " \t: " << stu_arr[i].getScore() << "\t";
		}
		cout << endl;
	};
	while (1) {
		cout << "1.전체 명단, 개인별 점수, 전체 평균  2. 그룹별 점수  3.검색  4.종료 :";
		int input;
		cin >> input;
		if (input == 1) {
			
			print(population, all_student);
			
			cout << "총인원 : " << population << endl;
			cout << "평균 : " << average << endl;
		}
		else if (input == 2) {

			cout << "==A==" << endl;
			print(countA, group_A);
			
			cout << endl;

			cout << "총인원 : " << countA << endl;

			cout << endl;

			cout << "==B==" << endl;
			print(countB, group_B);
			
			cout << endl;

			cout << "총인원 : " << countB << endl;
			cout << "==C==" << endl;
			print(countC, group_C);
			
			cout << endl;

			cout << "총인원 : " << countC << endl;
			cout << endl;
		}
		else if (input == 3) {
			Student* student = nullptr;
			string name;
			cout << "이름 입력 : ";
			cin >> name;
			for (int i = 0; i < population; i++) {
				if (all_student[i].getName() == name) {
					student = &all_student[i];
					break;
				}
			}
			if (student->getGrade() == A) {
				cout << "점수 : " << student->getScore() << endl;
				cout << "U deserve it! " << endl;
			}else if (student->getGrade() == B) {
				cout << "점수 : " << student->getScore() << endl;
				cout << "Well done " << endl;
			}else if (student->getGrade() == C) {
				cout << "점수 : " << student->getScore() << endl;
				cout << " Good" << endl;
			}

		}
		else if (input == 4) {

			break;
		}
		else {
			cout << "올바른 숫자를 입력해주세요." << endl;
		}
	}
		delete[] all_student;
		delete[] group_A;
		delete[] group_B;
		delete[] group_C;
		all_student = NULL;
		group_A = NULL;
		group_B = NULL;
		group_C = NULL;

	}
