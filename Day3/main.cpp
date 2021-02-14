#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	in_file.open("input.txt", ios::in);

	vector<string> my_map;

	string temp;
	while (getline(in_file, temp))
	{
		my_map.push_back(temp);
	}





	int n = my_map.size();
	int m = my_map[0].size();

	vector<int> res;

	vector<vector<int>> dir = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

	for (int i = 0; i < 5; i++)
	{
		int dir_c = dir[i][0];
		int dir_r = dir[i][1];

		int count = 0;
		int row = 0;
		int col = 0;

		while (row < n - 1)
		{

			row = row + dir_r;
			col = (col + dir_c) % m;

			if (my_map[row][col] == '#')
			{
				count++;
			}
		}

		res.push_back(count);
	}


	long long p = 1;
	for (int i = 0; i < res.size(); i++)
	{
		cout << res[i] << endl;
		p = p * res[i];
	}


	cout << p;

	return 0;
}