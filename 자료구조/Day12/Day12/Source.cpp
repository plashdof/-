#include <iostream>
#include <vector>
using namespace std;

#define MAX 353333

class arr {
public:
	int key;
	int flag;

	arr() {
		key = -1;
		flag = 0;
	}
};

arr HashArr[MAX];
int sz = 0;

int hashfunc(int idx) {
	return idx % MAX;
}

void tableClear(vector<int>& v) {

	for (int i = 0; i < v.size(); i++)
	{
		HashArr[v[i]].key = -1;
		HashArr[v[i]].flag = 0;
	}
}

int main() {
	int T = 0;
	int N = 0;
	int M = 0;
	int h = 0;
	int x = 0;

	vector<int> v;

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N;
		

		for (int j = 0; j < N; j++)
		{
			cin >> x;
			h = hashfunc(x);

			if (HashArr[h].flag == 0)		//  �ش� �ε����� ����ִٸ�
			{
				HashArr[h].key = x;
				HashArr[h].flag = 1;		//  ����

				v.push_back(h);
				
			}
			else {							//  �ش� �ε����� ���ִٸ�
				while (HashArr[h].flag == 1)	// Linear probing ����
				{
					h = (h + 1) % MAX;
				}

				HashArr[h].key = x;
				HashArr[h].flag = 1;

				v.push_back(h);
			}
			
		}

		cin >> M;

		for (int j = 0; j < M; j++)
		{
			cin >> x;
			int probe = 1;
			h = hashfunc(x);

			if (HashArr[h].flag == 0)		// �ش� �ε����� ����ִٸ�, ������� ���
			{
				cout << "0 1\n";
			}
			else {
				while (HashArr[h].key != x)		// �ش� �ε����� �������� key �� ����ġ �� ��� Linear probing ����
				{
					h = (h + 1) % MAX;
					probe++;

					if (probe == MAX + 1)
					{
						probe--;
						break;
					}
						
				}

				cout << "1 " << probe << "\n";
			}
		}

		tableClear(v);
		v.clear();
	}

	return 0;
}