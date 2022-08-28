#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum direction { MIN = 1, MAX = -1 };

class Heap {
private:

	vector<int> v;
	int heap_size;
	int roodt_index;
	int direction;




public:

	Heap(int direction) {
		v.push_back(-1);
		this->heap_size = 0;
		this->roodt_index = 1;
		this->direction = direction;
	}



	int size() {
		return heap_size;
	}




	int isEmpty() {
		if (size() == 0)
		{
			return 1;
		}
		else {
			return 0;
		}
	}




	void swap(int idx1, int idx2) {
		int s = v[idx1];
		v[idx1] = v[idx2];
		v[idx2] = s;
	}




	void upHeap(int idx) {
		int index = idx;
		int par_idx = 0;

		while (index != 1)
		{
			par_idx = index / 2;
			if (v[index] < v[par_idx])
			{
				swap(index, par_idx);
			}
			else {
				break;
			}

			index = par_idx;
		}
	}



	void downHeap(int idx) {
		int index = idx;
		int chi_idx = 0;

		while (index * 2 + 1 <= size()) {



			if (v[index * 2] > v[index * 2 + 1])
			{
				chi_idx = index * 2 + 1;
			}
			else if (v[index * 2] <= v[index * 2 + 1])
			{
				chi_idx = index * 2;
			}

			if (v[index] > v[chi_idx])
			{
				swap(index, chi_idx);
				index = chi_idx;
			}
			else {
				break;
			}
		}

		if (index * 2 == size())
		{
			chi_idx = index * 2;

			if (v[index] > v[chi_idx])
			{
				swap(index, chi_idx);
			}
		}
	}

	void insert(int e) {
		v.push_back(e);
		heap_size++;
		upHeap(size());
	}

	void pop() {
		if (isEmpty())
		{
			cout << "-1\n";
		}
		else {
			swap(1, size());
			v.erase(v.end() - 1);
			heap_size--;
			downHeap(1);
		}
	}



	void top() {
		if (isEmpty())
		{
			cout << "-1\n";
		}
		else {
			cout << v[1] << "\n";
		}
	}



	void print() {
		if (isEmpty())
		{
			cout << "-1\n";
		}
		else {
			for (int i = 1; i < v.size(); i++)
			{
				cout << v[i] << " ";
			}
			cout << "\n";
		}
	}


	int seek(int idx) {			//   힙에서 idx 번째 원소 반환
		return v[idx];
	}

};


int main() {
	int T = 0;
	int N = 0;
	int p = 0;
	int x = 0;

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N >> p;

		Heap H(MIN);

		for (int j = 0; j < N; j++)
		{
			cin >> x;
			H.insert(x);
		}

		cout << H.seek(p) << "\n";


		for (int j = 1; j < p; j++)
		{
			H.pop();
		}

		H.top();
	}

	return 0;
}