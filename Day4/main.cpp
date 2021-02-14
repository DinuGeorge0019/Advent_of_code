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

	int count = 0;


	string temp;
	stringstream ss;
	while (getline(in_file, temp))
	{
		ss << " ";
		ss << temp;

		if (in_file.peek() == '\n')
		{
			stringstream new_ss;
			new_ss << ss.rdbuf();
			string passport = new_ss.str();

			if (passport.find("ecl") != string::npos && passport.find("pid") != string::npos &&
				passport.find("eyr") != string::npos && passport.find("hcl") != string::npos &&
				passport.find("byr") != string::npos && passport.find("iyr") != string::npos &&
				passport.find("hgt") != string::npos)
			{

				vector<string> bag_of_words;
				string word;
				while (new_ss >> word)
				{
					bag_of_words.push_back(word);
				}

				bool flag = false;
				for (int i = 0; i < bag_of_words.size(); i++)
				{
					size_t poz = bag_of_words[i].find(":");
					string first = bag_of_words[i].substr(0, poz);
					string second = bag_of_words[i].substr(poz + 1);


					if (first == "ecl")
					{
						string colors = "amb blu brn gry grn hzl oth";
						if (colors.find(second) == string::npos)
						{
							flag = true;
							break;
						}
					}
					else if (first == "pid")
					{
						if (second.size() != 9)
						{
							flag = true;
							break;
						}
					}
					else if (first == "eyr")
					{
						if (second.size() != 4)
						{
							flag = true;
							break;
						}

						int num = stoi(second);
						if (num < 2020 || num > 2030)
						{
							flag = true;
							break;
						}
					}
					else if (first == "hcl")
					{
						if (second[0] != '#')
						{
							flag = true;
							break;
						}

						if (second.size() != 7)
						{
							flag = true;
							break;
						}

						string letters = "0 1 2 3 4 5 6 7 8 9 a b c d e f";
						for (int i = 1; i < second.size(); i++)
						{
							if (letters.find(second[i]) == string::npos)
							{
								flag = true;
								break;
							}
						}
					}
					else if (first == "byr")
					{

						if (second.size() != 4)
						{
							flag = true;
							break;
						}

						int num = stoi(second);
						if (num < 1920 || num > 2002)
						{
							flag = true;
							break;
						}

					}
					else if (first == "iyr")
					{
						if (second.size() != 4)
						{
							flag = true;
							break;
						}

						int num = stoi(second);
						if (num < 2010 || num > 2020)
						{
							flag = true;
							break;
						}
					}
					else if (first == "hgt")
					{
						if (second.find("cm") != string::npos)
						{
							string height = second.substr(0, second.find("cm"));
							int h = stoi(height);
							if (h < 150 || h > 193)
							{
								flag = true;
								break;
							}
						}
						else if (second.find("in") != string::npos)
						{
							string height = second.substr(0, second.find("in"));
							int h = stoi(height);
							if (h < 59 || h > 76)
							{
								flag = true;
								break;
							}
						}
						else
						{
							flag = true;
							break;
						}
					}
				}


				if (flag == true)
				{
					ss.str(std::string());
					continue;
				}



				count++;
				ss.str(std::string());
			}
			else
			{

				ss.str(std::string());

				continue;
			}

		}
	}

	cout << count << endl;


	return 0;
}