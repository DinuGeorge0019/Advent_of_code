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

bool dfs(unordered_map<string, vector<string>>& graph, string s, string t)
{
	if (t == s) return false;
	set<string> visited;

	stack<string> stack;
	stack.push(s);
	visited.insert(s);

	while (!stack.empty())
	{

		string u = stack.top();
		stack.pop();


		for(int v=0; v<graph[u].size(); v++)
		{
			if (visited.find(graph[u][v]) == visited.end())
			{
				stack.push(graph[u][v]);
				visited.insert(graph[u][v]);

				if (graph[u][v] == t)
					return true;

			}
		}

	}

	if (visited.count(t))
	{
		return true;
	}
	else
	{
		return false;
	}

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	in_file.open("input.txt", ios::in);

	unordered_map<string, vector<string>> map;

	string temp;
	while (getline(in_file, temp))
	{

		string source = temp.substr(0, temp.find("bags") -1 );

		vector<string> destination;

		for (int i = 0; i < temp.size(); i++)
		{
			if (isdigit(temp[i]))
			{
				for (int j = i + 1; j < temp.size(); j++)
				{
					if (temp[j] == 'b' && temp[j + 1] == 'a' && temp[j + 2] == 'g')
					{
						string dest = temp.substr(i + 2, j - i - 3);
						destination.push_back(dest);
						i = j + 1;
						break;
					}

				}

			}
		}

		map.insert(make_pair(source, destination));

	}

	for (auto i : map)
	{
		cout << i.first<<"-";
		for (auto j : i.second)
		{
			cout << j<<"-";
		}
		cout << endl;
	}

	string t = "shiny gold";


	int count = 0;
	for (auto i : map)
	{
		if (dfs(map, i.first, t))
		{
			count++;
		}

	}

	cout << count;


	in_file.close();

	return 0;
}
