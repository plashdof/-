#include <iostream>
#include <vector>
using namespace std;

#define MAX 353333
#define AVAILABLE 2

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

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N;

		vector<int> v;


		for (int j = 0; j < N; j++)
		{
			cin >> x;
			h = hashfunc(x);
			int probe = 1;

			while (probe <= MAX)
			{


				if (HashArr[h].flag == 0)
				{
					HashArr[h].key = x;
					HashArr[h].flag = 1;
					v.push_back(h);
					break;
				}

				h = (h + 1) % MAX;
				probe++;
			}
		}

		cin >> M;

		for (int j = 0; j < M; j++)
		{
			cin >> x;
			int probe = 1;
			h = hashfunc(x);

			while (probe <= MAX)
			{

				if (HashArr[h].key == x)
				{
					cout << "1 " << probe << "\n";
					HashArr[h].key = -1;
					HashArr[h].flag = AVAILABLE;
					break;
				}
				else if (HashArr[h].flag == 0 || probe == MAX)
				{
					cout << "0 " << probe << "\n";
					break;
				}
				

				h = (h + 1) % MAX;
				probe++;
			}
		}

		tableClear(v);
		v.clear();
	}

	return 0;
}