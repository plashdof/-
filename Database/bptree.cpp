#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct leaf {
	int key;
	int value;
};

struct non_leaf {
	int key;
	int NextLevelBID;
};

bool comp1(leaf a, leaf b)
{
	return a.key < b.key;
}

bool comp2(non_leaf a, non_leaf b)
{
	return a.key < b.key;
}

class BPTree {
private:
	int block_size;
	const char* filename;
	int rootBID = 0;
	int block_id = 0;
	int entry_number = 0;
	int depth = 0;
	vector<int> parent_node;

public:
	BPTree(const char* _filename, int _block_size) {
		block_size = _block_size;
		filename = _filename;
	}

	void create(const char* _filename, int _block_size) {
		ofstream writeFile;
		filename = _filename;
		block_size = _block_size;
		int* header = new int[3];
		header[0] = block_size;
		header[1] = 0; // rootBID
		header[2] = 0; // depth

		writeFile.open(filename, ios::binary | ios::out);
		if (writeFile.is_open()) {
			for(int i=0; i<3; i++)
				writeFile.write((char*)&header[i], sizeof(header[i]));
			writeFile.close();
		}
		delete[] header;
	}

	bool insert(const char* filename, int key, int value)
	{
		block_id = search(filename, key); // data 을 넣을 leaf_node 찾기

		if (block_id == -1) // file_open error
			return false;
		else if (block_id == 0) // bptree is empty
		{
			fstream file;

			rootBID = 1; // make root_node
			leaf* leaf_node = new leaf[entry_number + 1];
			leaf_node[0].key = key;
			leaf_node[0].value = value;
			for (int i = 1; i <= entry_number; i++)
			{
				leaf_node[i].key = 0;
				leaf_node[i].value = 0;
			}

			file.open(filename, ios::binary | ios::in | ios::out);
			if (file.is_open())
			{
				file.seekp(4, ios::beg);
				file.write((char*)&rootBID, sizeof(int)); // header update
				file.seekp(12, ios::beg);
				for (int i = 0; i < entry_number; i++)
				{
					file.write((char*)&leaf_node[i].key, sizeof(int));
					file.write((char*)&leaf_node[i].value, sizeof(int));
				}
				file.write((char*)&leaf_node[entry_number].key, sizeof(int)); // == NextBID; 
				file.close();
				delete[] leaf_node;
				return true;
			}
			else
			{
				cout << "file open error\n";
				return false;
			}
		}
		else // bptree is not empty
		{
			int flag = insert_to_leaf(filename, key, value, block_id);
			return flag;
		}
	}

	bool insert_to_leaf(const char* filename, int key, int value, int BID)
	{
		ifstream readFile;
		fstream file;

		int offset = 12 + (BID - 1) * block_size;   // 해당 BID 읽어오기
		leaf* leaf_node = new leaf[entry_number + 1];
		readFile.open(filename, ios::binary | ios::in);
		if (readFile.is_open())
		{
			readFile.seekg(offset, ios::beg);
			for (int i = 0; i < entry_number; i++)
			{
				readFile.read((char*)&leaf_node[i].key, sizeof(int));
				readFile.read(((char*)&leaf_node[i].value), sizeof(int));
			}
			readFile.read((char*)&leaf_node[entry_number].key, sizeof(int)); // NEXTBID
			readFile.close();
		}
		else
		{
			cout << "file open error\n";
			return false;
		}

		int entry_count = 0;
		for (int i = 0; i < entry_number; i++)
		{
			if (leaf_node[i].key != 0)
				entry_count++;
			else
				break;
		}

		if (entry_count < entry_number) // not full
		{
			leaf_node[entry_count].key = key;
			leaf_node[entry_count].value = value;
			entry_count++;
			sort(leaf_node, leaf_node + entry_count, comp1);
			file.open(filename, ios::binary | ios::out | ios::in);
			offset = 12 + (BID - 1) * block_size;
			if (file.is_open())
			{
				file.seekp(offset, ios::beg);
				for (int i = 0; i < entry_number; i++)
				{
					file.write((char*)&leaf_node[i].key, sizeof(int));
					file.write((char*)&leaf_node[i].value, sizeof(int));
				}
				file.write((char*)&leaf_node[entry_number].key, sizeof(int));
				file.close();
				delete[] leaf_node;
			}
			else
			{
				cout << "file open error\n";
				return false;
			}
		}
		else // full spilt 필요
		{
			leaf* new_leaf_node = new leaf[entry_number+1];
			int spilt_idx = 0;
			if (entry_count % 2 == 0) // entry_number 가 짝수 
			{
				spilt_idx = entry_count / 2;
				for (int i = spilt_idx; i < entry_number; i++)
				{
					new_leaf_node[i - spilt_idx].key = leaf_node[i].key;
					leaf_node[i].key = 0;
					new_leaf_node[i - spilt_idx].value = leaf_node[i].value;
					leaf_node[i].value = 0;
				}
				for (int i = spilt_idx; i < entry_number; i++)
				{
					new_leaf_node[i].key = 0;
					new_leaf_node[i].value = 0;
				}
				new_leaf_node[entry_number].key = leaf_node[entry_number].key;
			}
			else // entry_number 가 홀수 
			{
				spilt_idx = entry_count / 2 + 1;
				for (int i = spilt_idx; i < entry_number; i++)
				{
					new_leaf_node[i - spilt_idx].key = leaf_node[i].key;
					leaf_node[i].key = 0;
					new_leaf_node[i - spilt_idx].value = leaf_node[i].value;
					leaf_node[i].value = 0;
				}
				for (int i = spilt_idx - 1; i < entry_number; i++)
				{
					new_leaf_node[i].key = 0;
					new_leaf_node[i].value = 0;
				}
				new_leaf_node[entry_number].key = leaf_node[entry_number].key;
			}

			long long size;
			int new_block_id = 0;
			readFile.open(filename, ios::binary | ios::in);
			if (readFile.is_open())
			{
				readFile.seekg(0, ios::end);
				size = readFile.tellg();
				new_block_id = ((size - 12) / block_size) + 1;
				readFile.close();
			}
			else
			{
				cout << "error\n";
				return false;
			}
			leaf_node[entry_number].key = new_block_id;

			if (key < new_leaf_node[0].key)
			{
				leaf_node[spilt_idx].key = key;
				leaf_node[spilt_idx].value = value;
				sort(leaf_node, leaf_node + (spilt_idx + 1), comp1);
			}
			else
			{
				if (entry_count % 2 == 0)
				{
					new_leaf_node[spilt_idx].key = key;
					new_leaf_node[spilt_idx].value = value;
					sort(new_leaf_node, new_leaf_node + (spilt_idx + 1), comp1);
				}
				else
				{
					new_leaf_node[spilt_idx - 1].key = key;
					new_leaf_node[spilt_idx - 1].value = value;
					sort(new_leaf_node, new_leaf_node + spilt_idx, comp1);
				}
			}

			file.open(filename, ios::binary | ios::out | ios::in);
			if (file.is_open())
			{
				offset = 12 + (BID - 1) * block_size;
				file.seekp(offset, ios::beg);
				for (int i = 0; i < entry_number; i++)
				{
					file.write((char*)&leaf_node[i].key, sizeof(int));
					file.write((char*)&leaf_node[i].value, sizeof(int));
				}
				file.write((char*)&leaf_node[entry_number].key, sizeof(int));

				offset = 12 + (new_block_id - 1) * block_size;
				file.seekp(offset,ios::beg);
				for (int i = 0; i < entry_number; i++)
				{
					file.write((char*)&new_leaf_node[i].key, sizeof(int));
					file.write((char*)& new_leaf_node[i].value, sizeof(int));
				}
				file.write((char*)&new_leaf_node[entry_number].key, sizeof(int));
				file.close();
			}
			else
			{
				cout << "error\n";
				return false;
			}
			int insert_key = new_leaf_node[0].key;
			int insert_BID = new_block_id;
			delete[] new_leaf_node;
			delete[] leaf_node;
			if (parent_node.size() != 0) // parent node 가 존재 
				insert_to_non_leaf(filename, insert_key, insert_BID, parent_node.back()); // non_leaf_node 에 insert
			else  // parent node 가 없다. //parent node 만들어주기 
				add_non_leaf_node(filename, BID, insert_key, insert_BID);
		}
		return true;
	}

	void add_non_leaf_node(const char* filename, int befor_BID, int key, int after_BID) // after_BID 가 추가된 BID == 마지막 block
	{
		non_leaf* non_leaf_node = new non_leaf[entry_number + 1];
		non_leaf_node[0].NextLevelBID = befor_BID;
		non_leaf_node[1].key = key;
		non_leaf_node[1].NextLevelBID = after_BID;
		for (int i = 2; i <= entry_number; i++)
		{
			non_leaf_node[i].key = 0;
			non_leaf_node[i].NextLevelBID = 0;
		}
		// find last BID;
		long long size;  
		int new_BID = 0;
		ifstream readFile;
		readFile.open(filename, ios::binary | ios::in);
		if (readFile.is_open())
		{
			readFile.seekg(0, ios::end);
			size = readFile.tellg();
			new_BID = ((size - 12) / block_size) + 1;
			readFile.close();
		}
		else
		{
			cout << "error\n";
			return;
		}

		int offset = 12 + (new_BID - 1) * block_size;
		fstream file;
		file.open(filename, ios::binary | ios::in | ios::out);
		if (file.is_open()) {
			file.seekp(offset, ios::beg);
			file.write((char*)&non_leaf_node[0].NextLevelBID, sizeof(int));
			for (int i = 1; i <= entry_number; i++)
			{
				file.write((char*)&non_leaf_node[i].key, sizeof(int));
				file.write((char*)&non_leaf_node[i].NextLevelBID, sizeof(int));
			}
			rootBID = new_BID;
			depth++;
			file.seekp(4, ios::beg);
			file.write((char*)&rootBID, sizeof(int));
			file.write((char*)&depth, sizeof(int));

			delete[] non_leaf_node;
			file.close();
			return;
		}
		else
		{
			cout << "error\n";
			delete[] non_leaf_node;
			return;
		}
	}

	void insert_to_non_leaf(const char* filename, int key, int BID, int parent_BID)
	{
		parent_node.pop_back();
		int offset;
		non_leaf* non_leaf_node = new non_leaf[entry_number+1];
		ifstream readFile;
		fstream writeFile;
		// read parent_BID;
		readFile.open(filename, ios::binary | ios::in);
		if (readFile.is_open())
		{
			offset = 12 + (parent_BID - 1) * block_size;
			readFile.seekg(offset, ios::beg);
			readFile.read((char*)&non_leaf_node[0].NextLevelBID, sizeof(int));
			for (int i = 1; i <= entry_number; i++)
			{
				readFile.read((char*)&non_leaf_node[i].key, sizeof(int));
				readFile.read((char*)&non_leaf_node[i].NextLevelBID, sizeof(int));
			}
			readFile.close();
		}
		else
		{
			cout << "error\n";
			delete[] non_leaf_node;
			return;
		}

		int entry_count = 0;
		for (int i = 1; i <= entry_number; i++)
		{
			if (non_leaf_node[i].key == 0)
				break;
			entry_count++;
		}

		if (entry_count < entry_number)  // not full insert key and BID to non_leaf_node;
		{
			non_leaf_node[entry_count + 1].key = key;
			non_leaf_node[entry_count + 1].NextLevelBID = BID;
			entry_count++;
			sort(non_leaf_node, non_leaf_node + (entry_count+1), comp2);

			offset = 12 + (parent_BID - 1) * block_size;
			writeFile.open(filename, ios::binary | ios::in | ios::out);
			if (writeFile.is_open())
			{
				writeFile.seekp(offset, ios::beg);
				writeFile.write((char*)&non_leaf_node[0].NextLevelBID, sizeof(int));
				for (int i = 1; i <= entry_number; i++)
				{
					writeFile.write((char*)&non_leaf_node[i].key, sizeof(int));
					writeFile.write((char*)&non_leaf_node[i].NextLevelBID, sizeof(int));
				}
				
				delete[] non_leaf_node;
				writeFile.close();
				return;
			}
			else
			{
				cout << "error\n";
				return;
			}
		}
		else  //  parent_BID  full -> need spilt
		{
			int insert_key;  //  non_leaf_node 가 쪼개지면서 parent_BID 에게 추가해야할 값들
			int insert_BID;
			int spilt_idx;

			non_leaf* new_non_leaf_node = new non_leaf[entry_number + 1];
			if (entry_count % 2 == 0)
			{
				spilt_idx = entry_count / 2 + 1;
				insert_key = non_leaf_node[spilt_idx].key;
				non_leaf_node[spilt_idx].key = 0;

				new_non_leaf_node[0].NextLevelBID = non_leaf_node[spilt_idx].NextLevelBID;
				non_leaf_node[spilt_idx].NextLevelBID = 0;
	
				for (int i = spilt_idx + 1 ; i <= entry_number; i++)
				{
					new_non_leaf_node[i - spilt_idx].key = non_leaf_node[i].key;
					non_leaf_node[i].key = 0;
					new_non_leaf_node[i - spilt_idx].NextLevelBID = non_leaf_node[i].NextLevelBID;
					non_leaf_node[i].NextLevelBID = 0;
				}
				for (int i = spilt_idx - 1; i <= entry_number; i++)
				{
					new_non_leaf_node[i].key = 0;
					new_non_leaf_node[i].NextLevelBID = 0;
				}
			}
			else // entry 개수가 홀수개
			{
				spilt_idx = entry_number / 2 + 1;
				insert_key = non_leaf_node[spilt_idx].key;
				non_leaf_node[spilt_idx].key = 0;

				new_non_leaf_node[0].NextLevelBID = non_leaf_node[spilt_idx].NextLevelBID;
				non_leaf_node[spilt_idx].NextLevelBID = 0;

				for (int i = spilt_idx + 1; i <= entry_number; i++)
				{
					new_non_leaf_node[i - spilt_idx].key = non_leaf_node[i].key;
					non_leaf_node[i].key = 0;
					new_non_leaf_node[i - spilt_idx].NextLevelBID = non_leaf_node[i].NextLevelBID;
					non_leaf_node[i].NextLevelBID = 0;
				}
				for (int i = spilt_idx; i <= entry_number; i++)
				{
					new_non_leaf_node[i].key = 0;
					new_non_leaf_node[i].NextLevelBID = 0;
				}
			}

			long long size = 0;
			int new_BID = 0;
			readFile.open(filename, ios::binary | ios::in);
			if (readFile.is_open())
			{
				readFile.seekg(0, ios::end);
				size = readFile.tellg();
				new_BID = ((size - 12) / block_size) + 1;
				readFile.close();
			}
			else
			{
				cout << "error\n";
				return;
			}
			insert_BID = new_BID;

			//insert non_leaf_node
			int idx = entry_count / 2 + 1;
			if (key < insert_key)
			{
				non_leaf_node[idx].key = key;
				non_leaf_node[idx].NextLevelBID = BID;
				idx++;
				sort(non_leaf_node, non_leaf_node + idx, comp2);
			}
			else
			{
				if (entry_count % 2 != 0)
				{
					new_non_leaf_node[idx].key = key;
					new_non_leaf_node[idx].NextLevelBID = BID;
					idx++;
					sort(new_non_leaf_node, new_non_leaf_node + idx, comp2);
				}
				else
				{
					idx--;
					new_non_leaf_node[idx].key = key;
					new_non_leaf_node[idx].NextLevelBID = BID;
					idx++;
					sort(new_non_leaf_node, new_non_leaf_node + idx, comp2);
				}
			}

			writeFile.open(filename, ios::binary | ios::in | ios::out);
			if (writeFile.is_open())
			{
				offset = 12 + (parent_BID - 1) * block_size;
				writeFile.seekp(offset, ios::beg);
				writeFile.write((char*)&non_leaf_node[0].NextLevelBID, sizeof(int));
				for (int i = 1; i <= entry_number; i++)
				{
					writeFile.write((char*)&non_leaf_node[i].key, sizeof(int));
					writeFile.write((char*)&non_leaf_node[i].NextLevelBID, sizeof(int));
				}

				offset = 12 + (new_BID - 1) * block_size;
				writeFile.seekp(offset, ios::beg);
				writeFile.write((char*)&new_non_leaf_node[0].NextLevelBID, sizeof(int));
				for (int i = 1; i <= entry_number; i++)
				{
					writeFile.write((char*)&new_non_leaf_node[i].key, sizeof(int));
					writeFile.write((char*)&new_non_leaf_node[i].NextLevelBID, sizeof(int));
				}
				writeFile.close();
				delete[] new_non_leaf_node;
				delete[] non_leaf_node;
			}
			else
			{
				cout << "error\n";
				return;
			}

			if (parent_node.size() != 0)
				insert_to_non_leaf(filename, insert_key, insert_BID, parent_node.back());
			else
				add_non_leaf_node(filename, parent_BID, insert_key, insert_BID);
			return;
		}
	}

	void print(const char* filename, const char* output_filename)
	{
		int offset = 0;
		vector<int> node_list;
		int idx = 0;
		ifstream readFile;
		fstream writeFile;

		if (read_header(filename))
		{
			leaf* leaf_node = new leaf[entry_number + 1];
			non_leaf* non_leaf_node = new non_leaf[entry_number + 1];
			if (depth == 0)
			{
				if (rootBID > 0)
				{
					offset = 12 + (rootBID - 1) * block_size;
					readFile.open(filename, ios::binary | ios::in);
					if (readFile.is_open())
					{
						readFile.seekg(offset, ios::beg);
						for (int i = 0; i < entry_number; i++)
						{
							readFile.read((char*)&leaf_node[i].key, sizeof(int));
							readFile.read((char*)&leaf_node[i].value, sizeof(int));
						}
						readFile.close();
					}
					else
					{
						cout << "error\n";
						return;
					}

					writeFile.open(output_filename, ios::out);
					if (writeFile.is_open())
					{
						writeFile << "<0>" << "\n";
						for (int i = 0; i < entry_number; i++)
						{
							if (leaf_node[i].key == 0)
								break;
							writeFile << to_string(leaf_node[i].key) << ", ";
						}
						writeFile.seekg(-2, ios::end);
						writeFile << "\n";
						writeFile.close();
					}
					else
					{
						cout << "fileopen error\n";
						return;
					}
				}
				else
				{
					cout << "bptree is empty\n";
					return;
				}
			}
			else
			{
				//read RootBlock
				offset = 12 + (rootBID - 1) * block_size;
				readFile.open(filename, ios::in);
				if (readFile.is_open())
				{
					readFile.seekg(offset, ios::beg);
					readFile.read((char*)&non_leaf_node[0].NextLevelBID, sizeof(int));
					for (int i = 1; i <= entry_number; i++)
					{
						readFile.read((char*)&non_leaf_node[i].key, sizeof(int));
						readFile.read((char*)&non_leaf_node[i].NextLevelBID, sizeof(int));
					}
					readFile.close();
				}
				else
				{
					cout << "error\n";
					return;
				}

				writeFile.open(output_filename, ios::out);
				node_list.push_back(non_leaf_node[0].NextLevelBID);
				if (writeFile.is_open())
				{
					writeFile << "<0>\n";
					for (int i = 1; i <= entry_number; i++)
					{
						if (non_leaf_node[i].key == 0)
							break;
						writeFile << to_string(non_leaf_node[i].key) << ", ";
						node_list.push_back(non_leaf_node[i].NextLevelBID);
					}
					writeFile.seekp(-2, ios::end);
					writeFile << "\n" << "<1>" << "\n";
					writeFile.close();
				}
				else
				{
					cout << "error\n";
					return;
				}

				if (depth == 1) 
				{
					idx = 0;
					while (idx < node_list.size())
					{
						offset = 12 + (node_list[idx] - 1) * block_size;
						idx++;
						readFile.open(filename, ios::binary | ios::in);
						if (readFile.is_open())
						{
							readFile.seekg(offset, ios::beg);
							for (int i = 0; i < entry_number; i++)
							{
								readFile.read((char*)&leaf_node[i].key, sizeof(int));
								readFile.read((char*)&leaf_node[i].value, sizeof(int));
							}
							readFile.close();
						}
						else
						{
							cout << "fileopen error\n";
							return;
						}

						writeFile.open(output_filename, ios::out | ios::app);
						if (writeFile.is_open())
						{
							for (int i = 0; i < entry_number; i++)
							{
								if (leaf_node[i].key == 0)
									break;
								writeFile << to_string(leaf_node[i].key) << ", ";
							}
							writeFile.close();
						}
						else
						{
							cout << "fileopen_error\n";
							return;
						}
					}
					writeFile.open(output_filename, ios::in | ios::out);
					if (writeFile.is_open())
					{
						writeFile.seekp(-2, ios::end);
						writeFile << "\n";
						writeFile.close();
					}
					else
					{
						cout << "fileopen error\n";
						return;
					}
				}
				else
				{
					idx = 0;
					while (idx < node_list.size())
					{
						offset = 12 + (node_list[idx] - 1) * block_size;
						idx++;
						readFile.open(filename, ios::binary | ios::in);
						if (readFile.is_open())
						{
							readFile.seekg(offset, ios::beg);
							readFile.read((char*)&non_leaf_node[0].NextLevelBID, sizeof(int));
							for (int i = 1; i <= entry_number; i++)
							{
								readFile.read((char*)&non_leaf_node[i].key, sizeof(int));
								readFile.read((char*)&non_leaf_node[i].NextLevelBID, sizeof(int));
							}
							readFile.close();
						}
						else
						{
							cout << "error\n";
							return;
						}

						writeFile.open(output_filename, ios::out | ios::app);
						if (writeFile.is_open())
						{
							for (int i = 1; i <= entry_number; i++)
							{
								if (non_leaf_node[i].key == 0)
									break;
								writeFile << to_string(non_leaf_node[i].key) << ", ";
							}

							writeFile.close();
						}
						else
						{
							cout << "fileopen error\n";
							return;
						}
					}
					writeFile.open(output_filename, ios::in | ios::out);
					if (writeFile.is_open())
					{
						writeFile.seekp(-2, ios::end);
						writeFile << "\n";
						writeFile.close();
					}
					else
					{
						cout << "fileopen error\n";
						return;
					}
				}
			}
			delete[] leaf_node;
			delete[] non_leaf_node;
			return;
		}
		else
		{
			cout << "error\n";
			return;
		}
	}

	int search(const char* filename, int key)
	{
		if (read_header(filename))
		{
			if (rootBID == 0) // bptree 가 empty
				block_id = rootBID;
			else  // bptree is not empty
			{
				ifstream readFile;
				if (parent_node.size() != 0)   // 찾고자하는 leaf node 의 parent node 들 정보
					parent_node.clear();

				int check_depth = 0;
				block_id = rootBID;

				while (check_depth < depth) // current level is not leaf then find until leaf
				{
					parent_node.push_back(block_id);
					non_leaf* non_leaf_node = new non_leaf[entry_number + 1];

					readFile.open(filename, ios::binary | ios::in);
					if (readFile.is_open())
					{
						int offset = 12 + ((block_id - 1) * block_size);
						readFile.seekg(offset, ios::beg); // read root block

						readFile.read((char*)&non_leaf_node[0].NextLevelBID, sizeof(int));
						for (int i = 1; i <= entry_number; i++)
						{
							readFile.read((char*)&non_leaf_node[i].key, sizeof(int));
							readFile.read((char*)&non_leaf_node[i].NextLevelBID, sizeof(int));
						}
						for (int i = 1; i <= entry_number; i++)
						{
							if (non_leaf_node[i].key == 0)
								break;

							if (non_leaf_node[i].key <= key)
							{
								block_id = non_leaf_node[i].NextLevelBID;
							}
							else
							{
								block_id = non_leaf_node[i - 1].NextLevelBID;
								break;
							}
						}
						check_depth++;
						readFile.close();
						delete[] non_leaf_node;
					}
					else
					{
						cout << "error\n";
						return -1;
					}
				}
			}
			return block_id;
		}
		else
		{
			cout << "error";
			return -1;
		}
	}// search leaf node

	int point_search(const char* filename,int key)
	{
		block_id = search(filename, key);

		int offset = 0;
		ifstream readFile;

		if (rootBID == 0)
		{
			cout << "bptree is empty\n";
			return 0;
		}
		else
		{
			leaf* leaf_node = new leaf[entry_number + 1];
			offset = 12 + (block_id - 1) * block_size;

			readFile.open(filename, ios::binary | ios::in);
			if (readFile.is_open())
			{
				readFile.seekg(offset, ios::beg);
				for (int i = 0; i < entry_number; i++)
				{
					readFile.read((char*)&leaf_node[i].key, sizeof(int));
					readFile.read((char*)&leaf_node[i].value, sizeof(int));
				}
				readFile.read((char*)&leaf_node[entry_number].key, sizeof(int));
				readFile.close();
			}
			else
			{
				cout << "error\n";
				return 0;
			}
			
			int value = 0;
			for (int i = 0; i < entry_number; i++)
			{
				if (leaf_node[i].key == 0)
					break;

				if (leaf_node[i].key == key)
				{
					value = leaf_node[i].value;
					break;
				}
			}
			delete[] leaf_node;
			return value;
		}
	}
	void range_search(const char* filename, const char* output_filename,int startRange, int endRange) // range search
	{
		block_id = search(filename, startRange);

		if (rootBID == 0)
			cout << "bptree is empty\n";
		else
		{
			leaf* leaf_node = new leaf[entry_number + 1];
			ifstream readFile;
			ofstream writeFile;
			int flag = true;

			while (flag)
			{
				int offset = 12 + (block_id - 1) * block_size;
				readFile.open(filename, ios::binary | ios::in);
				if (readFile.is_open())
				{
					readFile.seekg(offset, ios::beg);
					for (int i = 0; i < entry_number; i++)
					{
						readFile.read((char*)&leaf_node[i].key, sizeof(int));
						readFile.read((char*)&leaf_node[i].value, sizeof(int));
					}
					readFile.read((char*)&leaf_node[entry_number].key, sizeof(int));
					readFile.close();
				}
				else
				{
					cout << "error";
					return;
				}

				writeFile.open(output_filename, ios::app | ios::out);
				if (writeFile.is_open())
				{
					for (int i = 0; i < entry_number; i++)
					{
						if (startRange <= leaf_node[i].key)
						{
							if (leaf_node[i].key <= endRange)
							{
								writeFile << to_string(leaf_node[i].key) << ',' << to_string(leaf_node[i].value) << " ";
							}
							else
							{
								writeFile << "\n";
								flag = false;
								break;
							}
						}
					}
					writeFile.close();
					block_id = leaf_node[entry_number].key;
					if (block_id == 0)
						flag = false;
				}
				else
				{
					cout << "error\n";
					return;
				}
			}
			delete[] leaf_node;
			return;
		}
	}
	bool read_header(const char* filename)
	{
		ifstream readFile;
		readFile.open(filename, ios::binary | ios::in);
		if (readFile.is_open())
		{
			int* header = new int[3];
			for (int i = 0; i < 3; i++)
				readFile.read((char*)&header[i], sizeof(int));
			
			block_size = header[0];
			entry_number = (block_size - 4) / 8;
			rootBID = header[1];
			depth = header[2];

			readFile.close();
			delete[] header;
		}
		else
		{
			cout << "error\n";
			return false;
		}
		return true;
	}
};

int main(int argc, char* argv[]) {
	char command = argv[1][0];
	ifstream inputFile;
	ofstream outputFile;

	BPTree* myBPtree = new BPTree(NULL, 0);
	switch (command) {
	case 'c':
		myBPtree->create(argv[2], atoi(argv[3]));
		break;
	case 'i':
		inputFile.open(argv[3]);
		if (inputFile.is_open())
		{
			int key;
			int value;
			int index = 0;
			while (!inputFile.eof())
			{
				string str;
				getline(inputFile, str);
				if (str.size() == 0)
					break;
				for (int i = 0; i < str.size(); i++)
					if (str[i] == ',')
					{
						index = i;
						break;
					}
				key = stoi(str);
				value = stoi(str.substr(index + 1));
				if (!myBPtree->insert(argv[2], key, value))
				{
					cout << "input error\n";
					break;
				}
			}
			inputFile.close();
		}
		else
		{
			cout << "file open error\n";
		}
		break;
	case 's':  // point search
		inputFile.open(argv[3]);
		outputFile.open(argv[4]);
		int search_value;
		if (inputFile.is_open() && outputFile.is_open())
		{
			while (!inputFile.eof())
			{
				string str;
				getline(inputFile, str);
				if (str.size() == 0)
					break;

				int key = stoi(str);
				search_value = myBPtree->point_search(argv[2], key);
				outputFile << to_string(key) << ',' << to_string(search_value) << "\n";
			}
			inputFile.close();
			outputFile.close();
		}
		else
			cout << "fileopen_error\n";
		break;
	case 'r': // range search
		inputFile.open(argv[3]);
		if (inputFile.is_open())
		{
			int start_key;
			int end_key;
			int idx = 0;
			while (!inputFile.eof())
			{
				idx = 0;
				string str;
				getline(inputFile, str);
				if (str.size() == 0)
					break;

				for (int i = 0; i < str.size(); i++)
					if (str[i] == ',')
					{
						idx = i;
						break;
					}
				start_key = stoi(str);
				end_key = stoi(str.substr(idx + 1));
				myBPtree->range_search(argv[2], argv[4], start_key, end_key);
			}
			inputFile.close();
		}
		else
			cout << "fileopen_error\n";
		break;
	case 'p': 
		myBPtree->print(argv[2], argv[3]);
		break;
	}
	delete myBPtree;

	return 0;
}