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

	vector<long long> seat;

	string s;
	while (getline(in_file, s))
	{
		int r_low = 0;
		int r_up = 127;
		int c_low = 0;
		int c_up = 7;
		int row = 0;
		int col = 0;


		for (int i = 0; i < s.size(); i++)
		{
			if (i <= 6)
			{
				int r_mid = floor((r_up - r_low) / 2.0) + r_low;
				if (s[i] == 'F')
				{
					r_up = r_mid;
				}
				else if (s[i] == 'B')
				{
					r_low = r_mid + 1;
				}

				if (r_low == r_up)
				{
					row = r_up;
				}

			}
			else
			{
				int c_mid = floor((c_up - c_low) / 2.0) + c_low;
				if (s[i] == 'L')
				{
					c_up = c_mid;
				}
				else
				{
					c_low = c_mid + 1;
				}

				if (c_low == c_up)
				{
					col = c_up;
				}
			}
		}

		long long p = row * 8 + col;

		seat.push_back(p);

	}

	sort(seat.begin(), seat.end());

	for (int i = 1; i < seat.size(); i++)
	{
		if (seat[i] - seat[i - 1] > 1)
		{
			cout << seat[i] -1  << endl;
		}
	}






	return 0;
}