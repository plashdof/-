#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

string students[]{
        "���μ�", "��ΰ�", "�躸��", "�輺��", "�輼��", "�迵��", "�迵��", "������", "��Ǫ��", "�ڼ���",
        "������", "������", "���³�", "�ݿ���", "������", "����ȯ", "��ġ��", "�ɿ���", "������", "���ο�",
        "������", "������", "�̰�", "��ä��", "������", "������", "�ְ���", "������", "������", "�ϴ���",
        "������", "�ѿ���", "Ȳ����"
};

int score[33] = { 0, }; // �л��� ���� ������ �迭
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
            cout << "   �̸�:" << students[i] << " " << "����:" << score[i];
            if (score[i] < 10)cout << " ";
            if (students[i] == "�̰�")cout << " ";
            sum += score[i];
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "�� �ο�: " << 33;
        cout << endl << "���:" << sum / 32 << endl;
    }
    else if (case_num == 2)
    {
        cout << "AŬ����" << endl;
        for (int i = 0; i < anum; i++)
        {
            cout << "   �̸�:" << students[Aclass[i]] << " " << "����:" << score[Aclass[i]];
            if (score[i] < 10)cout << " ";
            if (students[Aclass[i]] == "�̰�")cout << " ";
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "A�׷� �ѿ�:" << anum << endl << endl;

        cout << "BŬ����" << endl;
        for (int i = 0; i < bnum; i++)
        {
            cout << "   �̸�:" << students[Bclass[i]] << " " << "����:" << score[Bclass[i]];
            if (score[i] < 10)cout << " ";
            if (students[Bclass[i]] == "�̰�")cout << " ";
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "B�׷� �ѿ�:" << bnum << endl << endl;

        cout << "CŬ����" << endl;
        for (int i = 0; i < cnum; i++)
        {
            cout << "   �̸�:" << students[Cclass[i]] << " " << "����:" << score[Cclass[i]];
            if (score[i] < 10)cout << " ";
            if (students[Cclass[i]] == "�̰�")cout << " ";
            if (i % 5 == 4)cout << endl;
        }
        cout << endl << "C�׷� �ѿ�:" << cnum << endl << endl;
    }
}


int main() {
    default_random_engine eng(static_cast<unsigned int>(time(nullptr)));

    uniform_int_distribution<int> dist(0, 30);

    for (int i = 0; i < 32; i++)    //0~30 ������ ���� �Ҵ�
    {
        score[i] = dist(eng);
    }


    for (int i = 0; i < 33; i++)        //�����뺰 ��� Ȯ��
    {
        if (score[i] >= 20)anum++;
        else if (score[i] >= 10)bnum++;
        else if (score[i] < 10)cnum++;
    }

    Aclass = new int[anum];        //Ŭ������ �����Ҵ�
    Bclass = new int[bnum];
    Cclass = new int[cnum];

    for (int i = 0; i < 33; i++)       // ������ Ŭ���� �з�(�ε�����)
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
        cout << endl<<"�޴� ����" << endl;
        cout << "1��: ��ü����   2��: �׷캰����    3��: ��ȸ   4��: ����" << endl;

        int choice = 0;
        cin >> choice;          //�޴� ����

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
            cout << "�л��̸��� �Է����ּ���" << endl;
            string tmp;
            int find_idx = 0;
            cin >> tmp;

            for (int i = 0; i < 33; i++)
            {
                if (tmp == students[i])
                {
                    find_idx = i;
                    cout << "�̸�: " << tmp << " ����: " << score[i] << endl;
                }
            }

            if (score[find_idx] >= 20)cout << "�����ǵ��: " << "U deserve it" << endl;
            else if (score[find_idx] >= 10)cout << "�����ǵ��: " << "Well done" << endl;
            else if (score[find_idx] < 10)cout << "�����ǵ��: " << "Good" << endl;
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "�ùٸ� ���ڸ� �Է����ּ���." << endl;
        }

    }

    delete[] Aclass;
    delete[] Bclass;
    delete[] Cclass;



    return 0;
}
