#include <iostream>
#include <vector>;
#include <algorithm>;
#include <stack>;
using namespace std;


vector<int> user[50001];	//  정방향 그래프
vector<int> userT[50001];	// 역방향 그래프

int explored[50001] = {};			// 방문했는지 표시
int SCC_leader[50001];			// 각 vertex 의 SCC leader 표시

vector<int> priority_v;		// DFS를 실행시킬 순서를 담은 vector

stack<int> finished;		// finished vertex 들 stack 에 저장
stack<int> for_print;




// 삼항연산자를 이용하여, compare 함수를 구현하였다. 
// 팔로워수가 같으면, id로 오름차순 / 팔로워수가 다르면, 팔로워수로 내림차순


bool compare(int a, int b) {		
	return (userT[a].size() == userT[b].size()) ? a < b : userT[a].size() > userT[b].size();
}



void DFS(int id) {

	explored[id] = 1;
	for (int i = 0; i < user[id].size(); i++) {
		int next_id = user[id][i];
		if (explored[next_id] == 0) {
			DFS(next_id);
		}
	}

	finished.push(id);		// finished 상태인 vertex stack 에 저장
	// cout << id << " ";		// 삽입순서대로 출력이므로, 출력
}




void DFS2(int id, int leader) {

	explored[id] = 1;
	SCC_leader[id] = leader;	// SCC leader 가 어떤 vertex 인지 저장.

	for (int i = 0; i < userT[id].size(); i++) {
		int next_id = userT[id][i];
		if (explored[next_id] == 0) {
			DFS2(next_id, leader);
		}
	}


}



int main() {

	int N = 0;
	int M = 0;
	int temp1 = 0;
	int temp2 = 0;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> temp1 >> temp2;
		user[temp1].push_back(temp2);
		userT[temp2].push_back(temp1);
	}

	for (int i = 1; i <= N; i++) {		//  각 팔로잉 user 들을 sorting.
		sort(user[i].begin(), user[i].end(), compare);
		
		sort(userT[i].begin(), userT[i].end(), compare);
	}


	for (int i = 1; i <= N; i++) {		// DFS 실행시킬 순서 담은 vector 생성
		priority_v.push_back(i);
	}
	sort(priority_v.begin(), priority_v.end(), compare);
	



	for (int i = 0; i < priority_v.size(); i++) {	// 팔로워수 내림차순으로 DFS 실행
		if (explored[priority_v[i]] == 0) {
			DFS(priority_v[i]);
		}
	}


	fill(explored, explored + 50002, 0);			// visited 배열 초기화

	while (!finished.empty()) {		// finished stack 순서로 DFS2 실행

		int id = finished.top();
		int temp = finished.top();
		for_print.push(temp);
		finished.pop();


		if (explored[id] == 1) {
			continue;
		}

		DFS2(id, id);
	}

	while (for_print.size() != 1) {
		cout << for_print.top() << " ";
		for_print.pop();
	}

	cout << for_print.top();

	cout << "\n";

	for (int i = 1; i < N; i++) {
		cout << SCC_leader[i] << " ";
	}
	cout << SCC_leader[N];
	



	return 0;
}