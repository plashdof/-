#include<iostream>
#include<random>
#include<iomanip>
#include<string>

using namespace std;

static int asize = 0;
static int bsize = 0, csize = 0;

class Students {
public:
	string name;
	int j;
	Students() {
		name = "";
		j = -1;
	}
	Students(string name, int j) {
		this->j = j;
		this->name = name;
	}
};

Students *groupA;
Students*groupB;
Students*groupC;

void division(const Students* stu) {
	

	int acnt = 0, bcnt = 0, ccnt = 0;
	for (int i = 0; i < 33; i++) {
		if (stu[i].j >= 20) {
			asize++;
		}
		else if (stu[i].j >= 10) {
			bsize++;
		}
		else {
			csize++;
		}
	}
	groupA = new Students[asize];
	groupB = new Students[bsize];
	groupC = new Students[csize];

	for (int i = 0; i < 33; i++) {
		if (stu[i].j >= 20) {
			groupA[acnt] = stu[i];
			acnt++;
		}
		else if (stu[i].j >= 10) {
			groupB[bcnt] = stu[i];
			bcnt++;
		}
		else {
			groupC[ccnt] = stu[i];
			ccnt++;
		}
	}
	

}

void print(const Students* group ,int );

int main() {
	string s[] = { "공민선", "김민경", "김보겸", "김성원", "김세희", "김영범", "김영인", "김지연", "김푸름", "박소현",
		"박준혁", "박진성", "박태남", "반웅재", "서동우", "서희환", "송치헌", "심원주", "안지현", "여민영",
		"오영주", "유영진", "이강", "이채은", "이태희", "정휘진", "최경일", "최준혁", "최찬규", "하대훈",
		"하지민", "한예원", "황태준" };

	Students *stu = new Students[33];
	default_random_engine eng(static_cast<unsigned int>(time(nullptr)));
	uniform_int_distribution<int> dist(0, 30);
	for (int i = 0; i < 33; i++) {
		stu[i].name = s[i];	//이름부여0
		stu[i].j = dist(eng);
	}
	//입력 완료

	division(stu);
	//분류 완료
	
	
	while (true) {
		int select;
		cout << "1) 전체 성적 2) 그룹별 출력 3)학생 조회 4) 프로그램종료 : ";
		cin >> select;
		if (select == 1) {
			float avg;
			float total = 0;
			print(stu, 33);
			for (int i = 0; i < 33; i++) {
				total += stu[i].j;
			}
			avg = total / 33;
			printf("평균 : %0.2f", avg);
			//cout << "평균 : " << (%f)avg << endl;
			
		}
		else if (select == 2) {
			cout << "---------------------A그룹-------------------------------------" << endl;
			print(groupA, asize  );
			cout << "---------------------B그룹-------------------------------------" << endl;
			print(groupB, bsize );
			cout << "---------------------C그룹-------------------------------------" << endl;
			print(groupC, csize );
		}
		else if (select == 3) {
			string name;
			cout << "이름을 입력하세요 : ";
			cin >> name;
			for (int i = 0; i < 33; i++) {
				if (stu[i].name == name) {
					cout << "점수 : " << stu[i].j << endl;
					if (stu[i].j >= 20) {
						cout << "담당교수 피드백 : U deserve it !" << endl;
					}
					else if (stu[i].j >= 10) {
						cout << "담당교수 피드백 : Well done !" << endl;
					}
					else {
						cout << "담당교수 피드백 : Good !" << endl;
					}
				}
			}
		}
		else if (select == 4) {
			break;
		}
		else {
			cout << "올바른 숫자를 입력해주세요" << endl;
		}
		cout << endl;


	
	
	}
	

	delete[] groupA;
	delete[] groupB;
	delete[] groupC;
	delete[] stu;
	groupA = NULL;
	groupB = NULL;
	groupC = NULL;
	stu = NULL;
	return 0;
}

void print(const Students* group , int size) {
	//그룹들 입력받아서 출력
	int cnt = 0;
	for (int i = 1; i <= size; i++) {
		cout << group[i-1].name << " : " << "\t" << group[i-1].j << " ";
		if (i % 5 == 0 && i != 0) {
			cout << endl;
		}
	}
	cout << endl;
	cout << "총 인원 : " << (size ) << endl;
	//index때문에 1빼서 받았으니까 총 인원은 다시 1 증가
	
}