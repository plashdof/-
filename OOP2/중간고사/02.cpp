#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

class stud {
public:
    string name;
    int grade;
};

int main() {
    random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : time(nullptr);
    mt19937 eng(static_cast<unsigned int>(seed));
    uniform_int_distribution<int> dist(0, 30);

    string students[] = {"공민선", "김민경", "김보겸", "김성원", "김세희", "김영범", "김영인", "김지연", "김푸름", "박소현",
                         "박준혁", "박진성", "박태남", "반웅재", "서동우", "서희환", "송치헌", "심원주", "안지현", "여민영",
                         "오영주", "유영진", "이강", "이채은", "이태희", "정휘진", "최경일", "최준혁", "최찬규", "하대훈",
                         "하지민", "한예원", "황태준"};

    int grades[33] = {0,};
    float mean = 0;

    for (int i = 0 ; i < 33 ; i++) {
        grades[i] = dist(eng);
        mean += grades[i];
    }

    mean /= 33;

    int gruapA = 0;
    int gruapB = 0;
    int gruapC = 0;

    for (auto grade : grades) {
        if (grade >= 20) {
            gruapA++;
        } else if (grade >= 10) {
            gruapB++;
        } else {
            gruapC++;
        }
    }

    int *arrA = new int[gruapA];
    int *arrB = new int[gruapB];
    int *arrC = new int[gruapC];

    gruapA = 0;
    gruapB = 0;
    gruapC = 0;

    for (int i = 0; i < 33; i++) {
        if (grades[i] >= 20) {
            arrA[gruapA] = i;
            gruapA++;
        } else if (grades[i] >= 10) {
            arrB[gruapB] = i;
            gruapB++;
        } else {
            arrC[gruapC] = i;
            gruapC++;
        }
    }

    while(1){
        cout << "1)전체성적   2)그룹별 성적   3)조회   4)종료 :";
        int choi = 0;
        cin >> choi;
        if(choi == 1){
            for(int i = 0 ; i < 33 ; i++){
                if(i%5 == 0 && i !=0) cout << "\n";
                cout << students[i] << " :\t" << grades[i] << " ";

            }
            cout << "\n" << "총인원 :\t" << 33 <<"\n\n";
            cout << "평균 :\t" << mean << endl;
        }
        else if(choi == 2){
            cout << "==A=="<< endl;
            for(int i = 0 ; i<gruapA ; i++){
                if(i%5 == 0 && i !=0) cout << "\n";
                cout << students[arrA[i]] << " :\t" << grades[arrA[i]] << " ";
            }
            cout << "\n" << "총인원 :\t" << gruapA <<"\n\n";
            cout << "==B=="<< endl;
            for(int i = 0 ; i<gruapB ; i++){
                if(i%5 == 0 && i !=0) cout << "\n";
                cout << students[arrB[i]] << " :\t" << grades[arrB[i]] << " ";
            }
            cout << "\n" << "총인원 :\t" << gruapB <<"\n\n";
            cout << "==C==" << endl;
            for(int i = 0 ; i<gruapC ; i++){
                if(i%5 == 0 && i !=0) cout << "\n";
                cout << students[arrC[i]] << " :\t" << grades[arrC[i]] << " ";
            }
            cout << "\n" << "총인원 :\t" << gruapC <<"\n\n";
        }
        else if(choi == 3){
            string namee;
            cout << "학생 이름 : ";
            cin >> namee;
            int id;
            for(int i = 0 ; i < 33 ; i++){
                if(namee == students[i]){
                    cout << students[i] << " :\t" << grades[i] << endl;
                    id = i;
                    break;
                }
            }
            if (grades[id] >= 20) {
                cout << "담당교수 피드백 : U deserve it!" <<endl;
            } else if (grades[id] >= 10) {
                cout << "담당교수 피드백 : Well done" <<endl;
            } else {
                cout << "담당교수 피드백 : Good" <<endl;
            }
        }
        else if(choi == 4){
            break;
        }else{
            cout << "올바른 숫자를 입력해주세요." << endl;
            continue;
        }
    }

    delete[] arrA;
    delete[] arrB;
    delete[] arrC;
    return 0;
}

