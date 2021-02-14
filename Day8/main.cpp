#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <stack>
#include <unordered_set>

using namespace std;

bool check_infinite_cycle(vector<pair<string, int>>& container, bool flag, vector<int>& nops, vector<int>& jmps, int& acumulator)
{

	unordered_set<int> map;

	for (int i = 0; i < container.size(); i++)
	{
		if (container[i].first == "nop")
		{
			if (map.count(i))
			{
				return true;
			}
			if (flag == true)
			{
				nops.push_back(i);
			}

			map.insert(i);

		}
		else if (container[i].first == "acc")
		{
			if (map.count(i))
			{
				return true;
			}
			acumulator += container[i].second;
			map.insert(i);
		}
		else if (container[i].first == "jmp")
		{
			if (map.count(i))
			{
				return true;
			}
			if (flag == true)
			{
				jmps.push_back(i);
			}
			i += container[i].second - 1;
			map.insert(i);
		}
	}

	return false;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	in_file.open("input.txt", ios::in);


	vector<pair<string, int>> container;

	string temp;
	while (getline(in_file, temp))
	{
		string opcode = temp.substr(0, 3);
		string temp_data = temp.substr(4);
		int data = stoi(temp_data);
		container.push_back({ opcode, data });
	}

	int acumulator = 0;
	vector<int> nops;
	vector<int> jmps;

	check_infinite_cycle(container, true, nops, jmps, acumulator);
	
	bool pass = true;
	for (auto jmp : jmps)
	{
		container[jmp].first = "nop";
		acumulator = 0;
		bool cycle = check_infinite_cycle(container, false, nops, jmps, acumulator);

		if (cycle == false)
		{
			pass = true;
			break;
		}
		container[jmp].first = "jmp";
	}

	if (pass == false)
	{

		for (auto nop : nops)
		{
			container[nop].first = "jmp";
			acumulator = 0;
			bool cycle = check_infinite_cycle(container, false, nops, jmps, acumulator);

			if (cycle == false)
			{
				break;
			}
			container[nop].first = "nop";
		}
	}

	cout << acumulator << endl;

	in_file.close();


	return 0;
}