#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;




struct Field
{
	string name;

	long long  start1;
	long long  end1;
	long long  start2;
	long long  end2;
};

class Ticket
{
private:

	vector<Field> fields;
	vector<long long> my_ticket;
	vector<vector<long long>> tickets;
	vector<unordered_set<long long>> possibleFields;
	unordered_map<string, vector<int> > field_positions;


public:

	Ticket(const string file)
	{
		read_data(file);
	}

	void read_data(string file)
	{

		fstream in_file;
		in_file.open(file, ios::in);


		//get fields

		string line;
		while (getline(in_file, line) && line != "")
		{
			string name = line.substr(0, line.find(":"));

			string temp = line.substr(line.find(":") + 1);
			replace(temp.begin(), temp.end(), '-', ' ');
			
			stringstream ss(temp);
			vector<string> field_data((istream_iterator<string>(ss)), istream_iterator<string>());
			
			Field new_field;
			new_field.name = name;
			new_field.start1 = stoll(field_data[0]);
			new_field.end1 = stoll(field_data[1]);
			new_field.start2 = stoll(field_data[3]);
			new_field.end2 = stoll(field_data[4]);

			fields.push_back(new_field);
		}

		//get my ticket
		getline(in_file, line);
		getline(in_file, line);
		
		replace(line.begin(), line.end(), ',', ' ');
		stringstream ss(line);
		long long temp_int;
		while (ss>>temp_int)
		{
			my_ticket.push_back(temp_int);
		}

		//get nearby tickets

		getline(in_file, line);
		getline(in_file, line);

		while (getline(in_file, line) && line != "")
		{
			replace(line.begin(), line.end(), ',', ' ');
			stringstream ss(line);
			vector<string> temp_ticket((istream_iterator<string>(ss)), istream_iterator<string>());
			vector<long long> ticket;
			for (auto i : temp_ticket)
			{
				ticket.push_back(stoll(i));
			}
			tickets.push_back(ticket);
		}

		in_file.close();
	}

	long long get_sum_of_invalid_numbers()
	{

		//vector<long long> invalid_numbers;
		long long sum = 0;

		for (auto& ticket : tickets)
		{
			for (auto& number : ticket)
			{

				for (auto& field : fields)
				{
					if (number < field.start1 || number > field.end2)
					{
						sum += number;
						//invalid_numbers.push_back(number);
						break;
					}

					if (number > field.end1 && number < field.start1)
					{
						sum += number;
						//invalid_numbers.push_back(number);
						break;
					}

				}
			}
		}

		return sum;
		
	}

	void erase_tickets()
	{
		//Cleanup invalid tickets
		tickets.erase(
			remove_if(tickets.begin(), tickets.end(), [&](vector<long long>& ticket) 
				{
					for (auto& number : ticket)
					{
						for (auto& field : fields)
						{
							if (number < field.start1 || number > field.end2)
							{
								return true;
							}

							if (number > field.end1 && number < field.start1)
							{
								return true;
								break;
							}

						}
					}

					return false;


				}), tickets.end());

	}

	// Checks if a field is possible for a given colomn of all tickets
	bool isFieldPossible(int ticketCol, int field) {
		for (int i = 0; i < tickets.size(); i++) {
			if ((tickets[i][ticketCol] < fields[field].start1) || ((tickets[i][ticketCol] > fields[field].end1) && (tickets[i][ticketCol] < fields[field].start2)) || (tickets[i][ticketCol] > fields[field].end2))
				return false;
		}
		return true;
	}

	// Maps every column of ticket values to fields they could possibly be
	void mapPossibleFields() {
		possibleFields.resize(fields.size());
		for (int ticketCol = 0; ticketCol < fields.size(); ticketCol++) {
			for (int field = 0; field < fields.size(); field++) {
				if (isFieldPossible(ticketCol, field)) {
					possibleFields[ticketCol].insert(field);
				}
			}
		}
	}

	// Removes a field from all sets except the passed exception
	void removeFieldFromSets(int field, int exception) {
		for (int i = 0; i < fields.size(); i++) {
			if (i != exception) {
				possibleFields[i].erase(field);
			}
		}
	}

	long long process_data()
	{

		erase_tickets();

		vector<int> processed(fields.size());
		// First map all the possible fields
		mapPossibleFields();
		// Then narrow down each possibleField to one field
		for (int i = 0; i < fields.size(); i++) {
			// Find the set with size 1 that hasn't been processed
			for (int j = 0; j < possibleFields.size(); j++) {
				if (possibleFields[j].size() == 1 && !processed[j]) {
					// Remove this field from every other possibleFields set and set the current possibleField as processed
					removeFieldFromSets(*possibleFields[j].begin(), j);
					processed[j] = true;
					break;
				}
			}
		}

		// Get all the departure fields
		vector<int> departureFields;
		for (int i = 0; i < possibleFields.size(); i++)
			if (*possibleFields[i].begin() < 6)
				departureFields.push_back(i);

		// Finally, multiply all the departure fields together to get our ticket value
		long long ticketVal = 1;
		for (int i = 0; i < departureFields.size(); i++) {
			ticketVal *= my_ticket[departureFields[i]];
		}

		return ticketVal;



	}





};


int main()
{



	Ticket t1("input.txt");

	cout << "part 1 : " << t1.get_sum_of_invalid_numbers() << endl;
	cout << "part 2 : " << t1.process_data();







	return 0;
}