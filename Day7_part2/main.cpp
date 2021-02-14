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

using namespace std;

int solve(unordered_map<string, vector<pair<int, string>>> map, string s)
{
	int n = 0;

	for (int i = 0; i < map[s].size(); i++)
	{
		n += map[s][i].first + (map[s][i].first * solve(map, map[s][i].second));
	}

	return n;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	in_file.open("input.txt", ios::in);

	unordered_map<string, vector<pair<int, string>>> map;

	string temp;
	while (getline(in_file, temp))
	{

		string source = temp.substr(0, temp.find("bags") - 1);

		vector<pair<int, string>> destination;

		for (int i = 0; i < temp.size(); i++)
		{
			if (isdigit(temp[i]))
			{	
				int weight = stoi(temp.substr(i, 1));
				for (int j = i + 1; j < temp.size(); j++)
				{
					if (temp[j] == 'b' && temp[j + 1] == 'a' && temp[j + 2] == 'g')
					{
						string dest = temp.substr(i + 2, j - i - 3);
						destination.push_back({weight, dest });
						i = j + 1;
						break;
					}

				}

			}
		}

		map.insert(make_pair(source, destination));

	}



	string t = "shiny gold";
	cout << solve(map, t) << endl;

	in_file.close();

	return 0;
}
