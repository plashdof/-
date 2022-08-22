#include <iostream>
#include <string>
#include <vector>
using namespace std;

int F[10001] = { 0 };	// Failure Function �� �迭�� �����Ͽ���
vector<int> result;		// �����ϴ� ������ �����ϴ� ���� index�� vector�� �����Ͽ���

 void failureFunction(string P) {	// failure Function�� ������
	 
	 int i = 1;
	 int j = 0;

	 while (i < P.size()) {	// P�� �ڱ��ڽŰ� ���Ѵ�
		 if (P[i] == P[j]) {	
			 F[i] = j + 1;
			 i++;
			 j++;
		 }
		 else if (j > 0) {    // ����ġ�ϰ�, j �� 0���� Ŭ��
			 j = F[j - 1];
		 }	
		 else {				// ����ġ�ϰ�, j �� 0�϶�
			 F[i] = 0;
			 i++;
		 }
	 }
}

 void KMP(string T, string P) {
	 failureFunction(P);		// FailureFunction ��ó��
	 int i = 0;
	 int j = 0;
	 while (i < T.size()) {
		 if (T[i] == P[j]) {
			 if (j == P.size() - 1) {	//  match �߻���
				 result.push_back(i - j);	// �ش� ���� index�� result vector�� ����
				 j = F[j];					// j �� �ش� Failure function ������ �ʱ�ȭ
				 cout << P.size() - j<< " ";
				 // ��ġ��, ���Ӱ� �����ϴ� ����̹Ƿ�, �� Pattern�� ���̿���, F[j]�� ũ�⸸ŭ ���ְ� �ȴ�.
				 // �׸��� �� ������� j��, �ٽ� KMP�� �����ϰ� �ȴ�
				 
				 i++;	
				 continue;
			 }
				 
			 i++;
			 j++;
		 }
		 else if (j > 0) {
			 cout << j - F[j - 1] << " ";
			 j = F[j - 1];
		 }
		 else {
			 i++;
			 cout << "1" << " ";
		 }
	 }

 }



int main() {

	string T = "";
	string P = "";
	cin >> T >> P;

	KMP(T, P);

	cout << "\n";

	if (!result.empty()) {	// Text�� ��ġ�ϴ� Pattern�� ���°��, ����ó��
		for (int i = 0; i < result.size(); i++)
			cout << result[i] << " ";
	}
	




}