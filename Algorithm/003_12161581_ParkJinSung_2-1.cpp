#include <iostream>
#include <string>
#include <vector>
using namespace std;

int F[10001] = { 0 };	// Failure Function 을 배열로 구현하였다
vector<int> result;		// 좋아하는 구문이 존재하는 시작 index를 vector에 저장하였다

 void failureFunction(string P) {	// failure Function의 구현부
	 
	 int i = 1;
	 int j = 0;

	 while (i < P.size()) {	// P를 자기자신과 비교한다
		 if (P[i] == P[j]) {	
			 F[i] = j + 1;
			 i++;
			 j++;
		 }
		 else if (j > 0) {    // 불일치하고, j 가 0보다 클때
			 j = F[j - 1];
		 }	
		 else {				// 불일치하고, j 가 0일때
			 F[i] = 0;
			 i++;
		 }
	 }
}

 void KMP(string T, string P) {
	 failureFunction(P);		// FailureFunction 전처리
	 int i = 0;
	 int j = 0;
	 while (i < T.size()) {
		 if (T[i] == P[j]) {
			 if (j == P.size() - 1) {	//  match 발생시
				 result.push_back(i - j);	// 해당 시작 index를 result vector에 저장
				 j = F[j];					// j 는 해당 Failure function 값으로 초기화
				 cout << P.size() - j<< " ";
				 // 일치후, 새롭게 시작하는 경우이므로, 총 Pattern의 길이에서, F[j]의 크기만큼 빼주게 된다.
				 // 그리고 그 결과값의 j로, 다시 KMP를 시작하게 된다
				 
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

	if (!result.empty()) {	// Text에 일치하는 Pattern이 없는경우, 예외처리
		for (int i = 0; i < result.size(); i++)
			cout << result[i] << " ";
	}
	




}