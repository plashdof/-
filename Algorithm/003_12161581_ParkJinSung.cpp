#include <iostream>
#include <vector>;
#include <algorithm>;
#include <stack>;
using namespace std;


vector<int> user[50001];	//  ������ �׷���
vector<int> userT[50001];	// ������ �׷���

int explored[50001] = {};			// �湮�ߴ��� ǥ��
int SCC_leader[50001];			// �� vertex �� SCC leader ǥ��

vector<int> priority_v;		// DFS�� �����ų ������ ���� vector

stack<int> finished;		// finished vertex �� stack �� ����
stack<int> for_print;




// ���׿����ڸ� �̿��Ͽ�, compare �Լ��� �����Ͽ���. 
// �ȷο����� ������, id�� �������� / �ȷο����� �ٸ���, �ȷο����� ��������


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

	finished.push(id);		// finished ������ vertex stack �� ����
	// cout << id << " ";		// ���Լ������ ����̹Ƿ�, ���
}




void DFS2(int id, int leader) {

	explored[id] = 1;
	SCC_leader[id] = leader;	// SCC leader �� � vertex ���� ����.

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

	for (int i = 1; i <= N; i++) {		//  �� �ȷ��� user ���� sorting.
		sort(user[i].begin(), user[i].end(), compare);
		
		sort(userT[i].begin(), userT[i].end(), compare);
	}


	for (int i = 1; i <= N; i++) {		// DFS �����ų ���� ���� vector ����
		priority_v.push_back(i);
	}
	sort(priority_v.begin(), priority_v.end(), compare);
	



	for (int i = 0; i < priority_v.size(); i++) {	// �ȷο��� ������������ DFS ����
		if (explored[priority_v[i]] == 0) {
			DFS(priority_v[i]);
		}
	}


	fill(explored, explored + 50002, 0);			// visited �迭 �ʱ�ȭ

	while (!finished.empty()) {		// finished stack ������ DFS2 ����

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