#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main()
{
	vector<long long> data = { 6,4,12,1,20,0,16 };
	unordered_map<long long, long long> m; // data - turn

	for (int i = 0; i < data.size() - 1; i++)
	{
		m[data[i]] = i + 1;
	}

	int turn = data.size() + 1;

	while (turn != 30000001)
	{
		long long last = data.back();

		if (m.count(last))
		{

			data.push_back(turn - 1 - m[last]);
			m[last] = turn - 1;

			turn++;
		}
		else
		{

			data.push_back(0);
			m[last] = turn - 1;
			turn++;
		}

	}

	cout << data.back();


	return 0;
}