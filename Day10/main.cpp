#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;


void part1(vector<int>& data)
{
	int conect_1 = 0;
	int conect_3 = 0;


	for (int i = 0; i < data.size(); i++)
	{
		auto next_1 = find(data.begin(), data.end(), data[i] + 1);
		if (next_1 != data.end())
		{
			i = next_1 - data.begin();
			i--;
			conect_1++;
			continue;
		}

		auto next_2 = find(data.begin(), data.end(), data[i] + 2);

		if (next_2 != data.end())
		{
			i = next_2 - data.begin();
			i--;
			continue;
		}

		auto next_3 = find(data.begin(), data.end(), data[i] + 3);

		if (next_3 != data.end())
		{
			i = next_3 - data.begin();
			i--;
			conect_3++;
			continue;
		}

	}


	cout << conect_1 << " " << conect_3 << endl;
	cout << conect_1 * conect_3;
}

void part2(vector<int>& data)
{

	vector<long long> path_memo(data.size(), 0);

	path_memo.at(path_memo.size() - 1) = 1;


	for (int idx1 = path_memo.size() - 1; idx1 >= 0; --idx1) {

		size_t idx2 = idx1;

		while (++idx2 < data.size() && data[idx2] - data[idx1] <= 3) 
		{
			path_memo[idx1] += path_memo[idx2];
		}

	}


	std::cout << path_memo[0] << endl;


}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	fstream out_file;

	in_file.open("input.txt", ios::in);

	vector<int> data;

	int temp;
	while (in_file>>temp)
	{
		data.push_back(temp);
	}

	data.push_back(0);

	sort(data.begin(), data.end());
	data.push_back(data.back() + 3);
	
	//part1(data);

	part2(data);


	return 0;
}