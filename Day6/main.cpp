#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	in_file.open("input.txt", ios::in);

	int total = 0;

	string temp;
	stringstream ss;
	while (getline(in_file, temp))
	{
		ss << " ";
		ss << temp;

		if (in_file.peek() == '\n')
		{
			stringstream new_ss;
			new_ss << ss.rdbuf();

			vector<string> group;
			string person;
			while (new_ss >> person)
			{
				group.push_back(person);
			}

			if (group.size() == 1)
			{
				total += group[0].size();
				cout << total << endl;
				ss.str(std::string());
				continue;
			}

			vector<vector<int>> count(group.size(), vector<int>(26));

			for (int i = 0; i < group.size(); i++)
			{
				for (int j = 0; j < group[i].size(); j++)
				{
					count[i][group[i][j] - 'a']++;
				}
			}

			for (int j = 0; j < 26; j++)
			{
				for (int i = 0; i < count.size(); i++)
				{
					if (count[i][j] == 0)
					{
						break;
					}

					if (count[i][j] == 1 && i == count.size() - 1)
					{
						total++;
					}
				}
			}

			cout << total << endl;

			ss.str(std::string());

		}
	}

	

	return 0;
}