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



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	fstream in_file;
	fstream out_file;

	in_file.open("input.txt", ios::in);

	map<char, int> directions;
	directions['E'] = 0;
	directions['W'] = 0;
	directions['N'] = 0;
	directions['S'] = 0;

	map<char, int> waypoint;
	waypoint['E'] = 10;
	waypoint['W'] = 0;
	waypoint['N'] = 1;
	waypoint['S'] = 0;


	pair<char, char> face = {'E', 'N'};   // first = E / W and second = N / S 

	string line;
	while (getline(in_file, line))
	{
		char direction = line[0];
		string size(line.begin() + 1, line.end());
		int val = stoi(size);
		
		if (direction == 'F')
		{

			if (face.first == 'E' && face.second == 'N')
			{
				directions['E'] += val * abs(waypoint['E'] - waypoint['W']);
				directions['N'] += val * abs(waypoint['N'] - waypoint['S']);
			}
			else if (face.first == 'W' && face.second == 'N')
			{
				directions['W'] += val * abs(waypoint['E'] - waypoint['W']);
				directions['N'] += val * abs(waypoint['N'] - waypoint['S']);
			}
			else if (face.first == 'W' && face.second == 'S')
			{
				directions['W'] += val * abs(waypoint['E'] - waypoint['W']);
				directions['S'] += val * abs(waypoint['N'] - waypoint['S']);
			}
			else if (face.first == 'E' && face.second == 'S')
			{
				directions['E'] += val * abs(waypoint['E'] - waypoint['W']);
				directions['S'] += val * abs(waypoint['N'] - waypoint['S']);
			}
			
			continue;
		}

		if (direction == 'R' || direction == 'L')
		{
			if (val == 270)
			{
				if (direction == 'R')
				{

					if (face.first == 'E' && face.second == 'N')
					{
						int temp_E = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_E;

					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'N')
					{
						int temp_W = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'S')
					{
						int temp_W = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'E' && waypoint.first.second == 'S')
					{
						int temp_E = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_E;
					}

				}
				else if (direction == 'L')
				{
					if (waypoint.first.first == 'E' && waypoint.first.second == 'N')
					{
						int temp_E = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_E;

					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'N')
					{
						int temp_W = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'S')
					{
						int temp_W = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'E' && waypoint.first.second == 'S')
					{
						int temp_E = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_E;
					}
				}
				
				continue;
			}

			if (val == 180)
			{

				if (waypoint.first.first == 'E' && waypoint.first.second == 'N')
				{
					int temp_E = waypoint.second.first;
					int temp_N = waypoint.second.second;
					waypoint.first.first = 'W';
					waypoint.second.first = temp_E;
					waypoint.first.second = 'S';
					waypoint.second.second = temp_N;

				}
				else if (waypoint.first.first == 'W' && waypoint.first.second == 'N')
				{
					int temp_W = waypoint.second.first;
					int temp_N = waypoint.second.second;
					waypoint.first.first = 'E';
					waypoint.second.first = temp_W;
					waypoint.first.second = 'S';
					waypoint.second.second = temp_N;
				}
				else if (waypoint.first.first == 'W' && waypoint.first.second == 'S')
				{
					int temp_W = waypoint.second.first;
					int temp_S = waypoint.second.second;
					waypoint.first.first = 'E';
					waypoint.second.first = temp_W;
					waypoint.first.second = 'N';
					waypoint.second.second = temp_S;
				}
				else if (waypoint.first.first == 'E' && waypoint.first.second == 'S')
				{
					int temp_E = waypoint.second.first;
					int temp_S = waypoint.second.second;
					waypoint.first.first = 'W';
					waypoint.second.first = temp_E;
					waypoint.first.second = 'N';
					waypoint.second.second = temp_S;
				}

				continue;
			}

			if (val == 90)
			{
				if (direction == 'R')
				{

					if (waypoint.first.first == 'E' && waypoint.first.second == 'N')
					{
						int temp_E = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_E;

					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'N')
					{
						int temp_W = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'S')
					{
						int temp_W = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'E' && waypoint.first.second == 'S')
					{
						int temp_E = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_E;
					}

				}
				else if (direction == 'L')
				{
					if (waypoint.first.first == 'E' && waypoint.first.second == 'N')
					{
						int temp_E = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_E;

					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'N')
					{
						int temp_W = waypoint.second.first;
						int temp_N = waypoint.second.second;
						waypoint.first.first = 'W';
						waypoint.second.first = temp_N;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'W' && waypoint.first.second == 'S')
					{
						int temp_W = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'S';
						waypoint.second.second = temp_W;
					}
					else if (waypoint.first.first == 'E' && waypoint.first.second == 'S')
					{
						int temp_E = waypoint.second.first;
						int temp_S = waypoint.second.second;
						waypoint.first.first = 'E';
						waypoint.second.first = temp_S;
						waypoint.first.second = 'N';
						waypoint.second.second = temp_E;
					}
				}

				continue;
			}

		}


		if (direction == 'N')
		{
			waypoint['N'] += val;
		}
		else if (direction == 'S')
		{
			waypoint['S'] += val;
		}
		else if (direction == 'W')
		{
			waypoint['W'] += val;
		}
		else if (direction == 'E')
		{
			waypoint['E'] += val;
		}
		
	}

	cout << abs(directions['W'] - directions['E']) + abs(directions['S'] - directions['N']) << endl;

	

}