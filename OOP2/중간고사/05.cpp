#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

string students[]{
        "공민선", "김민경", "김보겸", "김성원", "김세희", "김영범", "김영인", "김지연", "김푸름", "박소현",
        "박준혁", "박진성", "박태남", "반웅재", "서동우", "서희환", "송치헌", "심원주", "안지현", "여민영",
        "오영주", "유영진", "이강", "이채은", "이태희", "정휘진", "최경일", "최준혁", "최찬규", "하대훈",
        "하지민", "한예원", "황태준"
};

int score[33] = { 0, }; // 학생별 점수 저장할 배열
int anum = 0;
int bnum = 0;
int cnum = 0;

int* Aclass;
int* Bclass;
int* Cclass;

int Aidx = 0;
int Bidx = 0;
int Cidx = 0;

void print(int case_num)
{
    if (case_num == 1)
    {
        double sum = 0;

        for (int i = 0; i < 33; i++)
        {
            cout << "   이름:" << students[i] << " " << "점수:" << score[i];
            if (score[i] < 10)cout << " ";
            if (students[i] == "이강")cout << " ";
            sum += score[i];
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "총 인원: " << 33;
        cout << endl << "평균:" << sum / 32 << endl;
    }
    else if (case_num == 2)
    {
        cout << "A클래스" << endl;
        for (int i = 0; i < anum; i++)
        {
            cout << "   이름:" << students[Aclass[i]] << " " << "점수:" << score[Aclass[i]];
            if (score[i] < 10)cout << " ";
            if (students[Aclass[i]] == "이강")cout << " ";
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "A그룹 총원:" << anum << endl << endl;

        cout << "B클래스" << endl;
        for (int i = 0; i < bnum; i++)
        {
            cout << "   이름:" << students[Bclass[i]] << " " << "점수:" << score[Bclass[i]];
            if (score[i] < 10)cout << " ";
            if (students[Bclass[i]] == "이강")cout << " ";
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "B그룹 총원:" << bnum << endl << endl;

        cout << "C클래스" << endl;
        for (int i = 0; i < cnum; i++)
        {
            cout << "   이름:" << students[Cclass[i]] << " " << "점수:" << score[Cclass[i]];
            if (score[i] < 10)cout << " ";
            if (students[Cclass[i]] == "이강")cout << " ";
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "C그룹 총원:" << cnum << endl << endl;
    }
}


int main() {
    default_random_engine eng(static_cast<unsigned int>(time(nullptr)));

    uniform_int_distribution<int> dist(0, 30);

    for (int i = 0; i < 32; i++)    //0~30 무작위 점수 할당
    {
        score[i] = dist(eng);
    }


    for (int i = 0; i < 33; i++)        //점수대별 명수 확인
    {
        if (score[i] >= 20)anum++;
        else if (score[i] >= 10)bnum++;
        else if (score[i] < 10)cnum++;
    }

    Aclass = new int[anum];        //클래스별 동적할당
    Bclass = new int[bnum];
    Cclass = new int[cnum];

    for (int i = 0; i < 33; i++)       // 점수별 클래스 분류(인덱스로)
    {
        if (score[i] >= 20)
        {
            Aclass[Aidx] = i;
            Aidx++;
        }
        else if (score[i] >= 10)
        {
            Bclass[Bidx] = i;
            Bidx++;
        }
        else if (score[i] < 10)
        {
            Cclass[Cidx] = i;
            Cidx++;
        }
    }


    while (1)
    {
        cout << endl<<"메뉴 선택" << endl;
        cout << "1번: 전체성적   2번: 그룹별성적    3번: 조회   4번: 종료" << endl;

        int choice = 0;
        cin >> choice;          //메뉴 구현

        if (choice == 1)
        {
            print(1);
        }
        else if (choice == 2)
        {
            print(2);
        }
        else if (choice == 3)
        {
            cout << "학생이름을 입력해주세요" << endl;
            string tmp;
            int find_idx = 0;
            cin >> tmp;

            for (int i = 0; i < 33; i++)
            {
                if (tmp == students[i])
                {
                    find_idx = i;
                    cout << "이름: " << tmp << " 점수: " << score[i] << endl;
                }
            }

            if (score[find_idx] >= 20)cout << "교수피드백: " << "U deserve it" << endl;
            else if (score[find_idx] >= 10)cout << "교수피드백: " << "Well done" << endl;
            else if (score[find_idx] < 10)cout << "교수피드백: " << "Good" << endl;
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "올바른 숫자를 입력해주세요." << endl;
        }

    }

    delete[] Aclass;
    delete[] Bclass;
    delete[] Cclass;



    return 0;
}
