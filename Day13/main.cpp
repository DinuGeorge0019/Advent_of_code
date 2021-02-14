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


long long  get_bus_time(long long  bus_time, long long target)
{
	
	for (int i = 1; ; i++)
	{
		long long temp_time = bus_time * i;

		if (temp_time >= target)
		{
			bus_time = temp_time;
			break;
		}
		
	}


	return bus_time;
}




int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	in_file.open("input.txt", ios::in);

	long long time;
	string bus;
	in_file >> time;
	in_file >> bus;

	vector<long long> data;

	for (int i = 0; i < bus.size(); i++)
	{
		if (isdigit(bus[i]))
		{
			string num;
			int j;
			for (j = i; j < bus.size(); j++)
			{
				if (bus[j] == ',')
					break;

				num += bus[j];
			}
			i = j;
			data.push_back(stoi(num));
		}
	}


	vector<pair<long long, long long>> res;
	for (int i = 0; i < data.size(); i++)
	{
		res.push_back({data[i] ,get_bus_time(data[i], time) });
	}

	sort(res.begin(), res.end(), [&](auto p1, auto p2)
		{
			return p1.second < p2.second;
		});

	for (auto i : res)
		cout << i.first << " " << i.second << endl;
	cout << endl;


	long long departure_time = (*res.begin()).second;

	long long bus_id = (*res.begin()).first;

	cout << (departure_time - time ) * bus_id;





	return 0;

}

