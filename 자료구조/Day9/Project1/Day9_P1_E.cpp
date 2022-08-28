#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum direction {MIN = 1, MAX = -1};

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

	void insert(int e) {
		v.push_back(e);
		heap_size++;
		upHeap(size());
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

};


int main() {
	int N = 0;
	cin >> N;
	string s = "";
	int x = 0;

	Heap H(MIN);

	for (int i = 0; i < N; i++)
	{
		cin >> s;

		if (s == "isEmpty")
		{
			cout << H.isEmpty() << "\n";
		}

		if (s == "size")
		{
			cout << H.size() << "\n";
		}

		if (s == "print")
		{
			H.print();
		}

		if (s == "insert")
		{
			cin >> x;
			H.insert(x);
		}
	}

}