#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include <iterator>


using namespace std;


struct Instruction 
{

	long long value;
	long long location;
	string bitmask;

};

class Program
{
private:
	vector<Instruction> program;
	unordered_map<long long, long long> memory;
public:

	Program(const string file)
	{
		read_data(file);
	}
	void read_data(string file)
	{

		fstream in_file;
		in_file.open(file, ios::in);

		long long value = 0;
		long long location = 0;
		string bitmask;

		string line;
		while (getline(in_file, line))
		{
			istringstream ss(line);
			
			vector<string> results((istream_iterator<string>(ss)), istream_iterator<string>());

			if (results[0][1] == 'a')
			{
				bitmask = results[2];
			}
			else if(results[0][1] == 'e')
			{
				location = stoll(results[0].substr(4, results[0].end() - results[0].begin() - 1));
				value = stoll(results[2]);

				Instruction new_instruction;
				new_instruction.bitmask = bitmask;
				new_instruction.location = location;
				new_instruction.value = value;

				program.push_back(new_instruction);

			}
		}

		in_file.close();
	}

	string dec_to_bin(long long dec)
	{
		string bin = "";
		for (int i = 35; i >= 0; i--)
		{

			if (pow(2, i) <= dec)
			{
				bin += '1';
				dec -= pow(2, i);
			}
			else
			{
				bin += '0';
			}
		}

		return bin;
	}


	long long bin_to_dec(string bin)
	{

		long long dec = 0;
		for (int i = 35; i >= 0; i--)
		{
			if (bin[i] == '1')
			{
				dec += pow(2, 35 - i);
			}
		}

		return dec;
	}


	void apply_mask(string& bin, string bitmask)
	{
		for (int i = 35; i >= 0; i--)
		{
			if (bitmask[i] != 'X')
			{
				bin[i] = bitmask[i];
			}
		}
	}

	long long process_data()
	{

		for (auto instruction : program)
		{
			string bin_value = dec_to_bin(instruction.value);
			apply_mask(bin_value, instruction.bitmask);

			memory[instruction.location] = bin_to_dec(bin_value);
		}

		long long sum = 0;
		for (auto& i : memory)
		{
			sum += i.second;
		}

		return sum;
	}

	void apply_maskV2(string& bin, string bitmask)
	{
		for (int i = 35; i >= 0; i--)
		{
			if (bitmask[i] == '0')
				continue;

			bin[i] = bitmask[i];
				
		}
	}

	void assing_memory(string bin_location, long long value)
	{

		int poz = -1;
		for (int i = 0; i < bin_location.size(); i++)
		{
			if (bin_location[i] == 'X')
			{
				poz = i;
				break;
			}
		}

		if (poz == -1)
		{
			memory[bin_to_dec(bin_location)] = value;
			return;
		}

		bin_location[poz] = '1';
		assing_memory(bin_location, value);
		bin_location[poz] = '0';
		assing_memory(bin_location, value);

	}

	long long process_data_v2()
	{

		for (auto instruction : program)
		{
			string bin_location = dec_to_bin(instruction.location);
			apply_maskV2(bin_location, instruction.bitmask);

			assing_memory(bin_location, instruction.value);
		}

		long long sum = 0;
		for (auto& i : memory)
		{
			sum += i.second;
		}

		return sum;
	}


};



int main()
{

	Program data1("input.txt");
	Program data2("input.txt");

	cout << data1.process_data() << endl;
	cout << data2.process_data_v2();


	return 0;
}