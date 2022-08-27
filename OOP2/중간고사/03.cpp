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
	string s[] = { "���μ�", "��ΰ�", "�躸��", "�輺��", "�輼��", "�迵��", "�迵��", "������", "��Ǫ��", "�ڼ���",
		"������", "������", "���³�", "�ݿ���", "������", "����ȯ", "��ġ��", "�ɿ���", "������", "���ο�",
		"������", "������", "�̰�", "��ä��", "������", "������", "�ְ���", "������", "������", "�ϴ���",
		"������", "�ѿ���", "Ȳ����" };

	Students *stu = new Students[33];
	default_random_engine eng(static_cast<unsigned int>(time(nullptr)));
	uniform_int_distribution<int> dist(0, 30);
	for (int i = 0; i < 33; i++) {
		stu[i].name = s[i];	//�̸��ο�0
		stu[i].j = dist(eng);
	}
	//�Է� �Ϸ�

	division(stu);
	//�з� �Ϸ�
	
	
	while (true) {
		int select;
		cout << "1) ��ü ���� 2) �׷캰 ��� 3)�л� ��ȸ 4) ���α׷����� : ";
		cin >> select;
		if (select == 1) {
			float avg;
			float total = 0;
			print(stu, 33);
			for (int i = 0; i < 33; i++) {
				total += stu[i].j;
			}
			avg = total / 33;
			printf("��� : %0.2f", avg);
			//cout << "��� : " << (%f)avg << endl;
			
		}
		else if (select == 2) {
			cout << "---------------------A�׷�-------------------------------------" << endl;
			print(groupA, asize  );
			cout << "---------------------B�׷�-------------------------------------" << endl;
			print(groupB, bsize );
			cout << "---------------------C�׷�-------------------------------------" << endl;
			print(groupC, csize );
		}
		else if (select == 3) {
			string name;
			cout << "�̸��� �Է��ϼ��� : ";
			cin >> name;
			for (int i = 0; i < 33; i++) {
				if (stu[i].name == name) {
					cout << "���� : " << stu[i].j << endl;
					if (stu[i].j >= 20) {
						cout << "��米�� �ǵ�� : U deserve it !" << endl;
					}
					else if (stu[i].j >= 10) {
						cout << "��米�� �ǵ�� : Well done !" << endl;
					}
					else {
						cout << "��米�� �ǵ�� : Good !" << endl;
					}
				}
			}
		}
		else if (select == 4) {
			break;
		}
		else {
			cout << "�ùٸ� ���ڸ� �Է����ּ���" << endl;
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
	//�׷�� �Է¹޾Ƽ� ���
	int cnt = 0;
	for (int i = 1; i <= size; i++) {
		cout << group[i-1].name << " : " << "\t" << group[i-1].j << " ";
		if (i % 5 == 0 && i != 0) {
			cout << endl;
		}
	}
	cout << endl;
	cout << "�� �ο� : " << (size ) << endl;
	//index������ 1���� �޾����ϱ� �� �ο��� �ٽ� 1 ����
	
}