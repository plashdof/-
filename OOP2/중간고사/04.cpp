#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

int TOTAL;
int A = 0, B = 0, C = 0;
int A_count = 0, B_count = 0, C_count = 0;
int *G_A, *G_B, *G_C;

void PrintList(string* student, int* score, int type) {
    
    double total = 0;
    
    switch(type) {
            
            // 전체출력
        case 0:
            
            for(int i = 0; i < TOTAL; i++) {
                
                cout << student[i] << " : " << score[i] << "\t";
                total += score[i];
                
                if( (i + 1) % 5 == 0)
                    cout << "\n";
            }
            
            printf("\n\n평균 : %.2f\n\n", total/TOTAL);
            
            break;
            
        case 1:
            
            cout << " ======== A ========" << endl;
            
            for(int i = 0; i < A; i++) {
                cout << student[G_A[i]] << " : " << score[G_A[i]] << "\t";
                
                if( (i + 1) % 5 == 0)
                    cout << "\n";

            }
            cout << "\n\n총인원 : " << A << "\n\n";
            
            
            cout << " ======== B ========" << endl;
            
            for(int i = 0; i < B; i++) {
                cout << student[G_B[i]] << " : " << score[G_B[i]] << "\t";
                
                if( (i + 1) % 5 == 0)
                    cout << "\n";

            }
            cout << "\n\n총인원 : " << B << "\n\n";
            
            
            cout << " ======== C ========" << endl;
            
            for(int i = 0; i < C; i++) {
                cout << student[G_C[i]] << " : " << score[G_C[i]] << "\t";
                
                if( (i + 1) % 5 == 0)
                    cout << "\n";

            }
            cout << "\n\n총인원 : " << C << "\n\n";
            
            
            break;
            
            // 스플릿출력
            
            
            
    }
    
}


// 동적 할당한 크기에, 값에 따라 인덱스 값을 넣어줌.
void divide(string* student, int* score) {
    
    for(int i = 0; i < TOTAL ; i++) {
        
        if(score[i] >= 20) {
            G_A[A_count++] = i;
        } else if (score[i] >= 10) {
            G_B[B_count++] = i;
        } else {
            G_C[C_count++] = i;
        }
    }
    
}

void search(string* student, int* score, string& name) {
    
    for(int i = 0; i < TOTAL; i++) {
        if(student[i] == name) {
            cout << student[i] << " : " << score[i] << endl;
            if(score[i] >= 20) {
                cout << "U deserve it!\n";
            } else if(score[i] >= 10) {
                cout << "Well done\n";
            } else {
                cout << "Good\n";
            }
        }
    }
    
}

int main() {
    
    int ran = 0;
    int input;
    string input_name;
    bool flag = false;
    
    string student[] = { "공민선", "김민경", "김보겸", "김성원", "김세희", "김영범", "김영인", "김지연", "김푸름", "박소현",
        "박준혁", "박진성", "박태남", "반웅재", "서동우", "서희환", "송치헌", "심원주", "안지현", "여민영",
        "오영주", "유영진", "이강", "이채은", "이태희", "정휘진", "최경일", "최준혁", "최찬규", "하대훈",
        "하지민", "한예원", "황태준" };
    
    TOTAL = sizeof(student)/sizeof(student[0]) ;
    
    int* score = new int[TOTAL];
    
    
    
    default_random_engine eng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> dist(0, 30);
    
    cout << TOTAL << endl;
    for(int i = 0; i < TOTAL ; i++) {
        ran = dist(eng);
        
        score[i] = ran;
        
        // 그룹 인원 체크하여 해당 크기만큼 동적할당 하기 위해.
        if(ran >= 20)
            A++;
        else if(ran >= 10)
            B++;
        else
            C++;
    }
    
    // 인덱스 번호를 부여하는 int 배열 그룹 세개 선언.
    G_A = new int[A];
    G_B = new int[B];
    G_C = new int[C];
    
    
    // 분류
    divide(student, score);
    
    
    
    cout << " 객체 지향 프로그래밍 성적" << endl;
    
    while(1) {
        cout << "1) 전체성적\t2) 그룹별 성적\t3) 조회\t4) 종료 : ";

        cin >> input;
        
        switch(input) {
                
            case 1:
                PrintList(student, score, 0);
                break;
                
            case 2:
                PrintList(student, score, 1);
                break;
                
            case 3:
                cout << "이름 : ";
                cin >> input_name;
                
                search(student, score, input_name);
                
                break;
                
            case 4:
                flag = true;
                break;
                
            default:
                cout << "올바른 숫자를 입력해주세요." << endl;
                break;
        }
        if(flag)
            break;
    }
    
    
    
    delete[] score;
    score = nullptr;
    
    delete[] G_A;
    G_A = nullptr;
    
    delete[] G_B;
    G_B = nullptr;
    
    delete[] G_C;
    G_C = nullptr;

    
    return 0;
    
    
}
