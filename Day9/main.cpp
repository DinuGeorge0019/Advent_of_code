#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;


int part1(vector<int>& data)
{
	int i_left = 0;
	for (int i = 25; i < data.size(); i++)
	{
		vector<int> left(data.begin() + i_left, data.begin() + i);


		i_left++;
		bool flag = false;
		for (int j = 0; j < left.size() - 1; j++)
		{
			for (int k = j + 1; k < left.size(); k++)
			{
				if (data[i] == left[j] + left[k])
				{
					flag = true;
					break;
				}
			}
		}



		if (flag == false)
		{
			return data[i];
			break;
		}

	}
}


void solve(vector<int>& data, int target)
{
	int i_left = 0;
	int sum = data[0];
	for (int i = 1; i < data.size(); i++)
	{

		if (sum < target)
		{
			sum += data[i];
		}


		while (sum > target)
		{
			sum -= data[i_left];
			i_left++;
		}


		if (sum == target)
		{
			int a = *max_element(data.begin() + i_left, data.begin() + i);
			int b = *min_element(data.begin() + i_left, data.begin() + i);
			cout << a + b << endl;
			break;
		}

	}


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
	while (in_file >> temp)
	{
		data.push_back(temp);
	}

	int target = part1(data);


	solve(data, target);



	return 0;
}