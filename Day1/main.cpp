#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void solve(vector<long long>& data)
{

	for (int i = 0; i < data.size() - 2; i++)
	{
		for (int j = i + 1; j < data.size() - 1; j++)
		{
			for (int k = j + 1; k < data.size(); k++)
			{
				if (data[i] + data[j] + data[k] == 2020)
				{
					cout << data[i] * data[j] * data[k];
					return;
				}


			}

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

    vector<long long> data;
    long long temp;
    while (in_file >> temp)
    {
        data.push_back(temp);
    }

    solve(data);


    return 0;
}