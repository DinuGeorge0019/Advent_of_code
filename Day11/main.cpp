#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <queue>
using namespace std;

bool check(int r, int c, int row, int col)
{

	if (r < 0 || r >= row || c < 0 || c >= col)
	{
		return false;
	}

	return true;
}

bool help_1(vector<string>& data, int row, int col)
{
	bool change = false;

	vector<string> data_copy = data;

	vector<vector<int>> dir = { {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1},{1, 0}, {1, -1}, {0, -1} };


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			if (data[i][j] == '.')
				continue;

			bool flag = true;
			if (data[i][j] == 'L')
			{
				for (int k = 0; k < 8; k++)
				{
					int new_r = i + dir[k][0];
					int new_c = j + dir[k][1];

					if (check(new_r, new_c, row, col) && data[new_r][new_c] == '#')
					{
						flag = false;
						break;
					}
				}
			}

			if (flag == true)
			{
				data_copy[i][j] = '#';
				change = true;
				continue;
			}
		}
	}

	data = data_copy;

	return change;

}

bool help_2(vector<string>& data, int row, int col)
{
	vector<string> data_copy = data;


	vector<vector<int>> dir = { {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1},{1, 0}, {1, -1}, {0, -1} };

	bool change = false;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			if (data[i][j] == '.')
				continue;

			if (data[i][j] == '#')
			{
				int count = 0;
				for (int k = 0; k < 8; k++)
				{
					int new_r = i + dir[k][0];
					int new_c = j + dir[k][1];

					if (check(new_r, new_c, row, col) && data[new_r][new_c] == '#')
					{
						count++;
					}

					if (count >= 4)
					{
						data_copy[i][j] = 'L';
						change = true;
						break;
					}
				}
			}
		}
	}


	data = data_copy;

	return change;

}

void solve(vector<string>& data)
{

	int row = data.size();
	int col = data[0].size();

	while (true)
	{
		if (help_1(data, row, col) == false)
			break;

		if (help_2(data, row, col) == false)
			break;
	}

	int count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			if (data[i][j] == '#')
				count++;
		}
	}

	cout << count << endl;





}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	fstream out_file;

	in_file.open("input.txt", ios::in);

	vector<string> data;

	string line;
	while (getline(in_file, line))
	{
		data.push_back(line);
	}

	
	solve(data);

}