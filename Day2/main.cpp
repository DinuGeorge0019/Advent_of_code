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


	vector<int> data;
	string password;

	int count = 0;

	while (getline(in_file, password))
	{
		replace(password.begin(), password.end(), '-', ' ');
		replace(password.begin(), password.end(), ':', ' ');
		stringstream ss(password);
		vector<string> elements;
		string temp;
		while (ss>>temp)
		{
			elements.push_back(temp);
		}

		int mini = stoi(elements[0]);
		int maxi = stoi(elements[1]);
		char c = elements[2][0];
		string p = elements[3];

		if ((p[mini - 1] == c && p[maxi - 1] != c) || (p[mini - 1] != c && p[maxi - 1] == c))
		{
			count++;
		}

	}

	cout << count << endl;


	return 0;
}