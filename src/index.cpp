#include "index.hpp"
#include <iostream>
#include <fstream>

using namespace std;

string concatenate_line(string line, string line_ws)
{
	// Key's size 
	const int key_info = 30;

	/* Size is a variable related to the size of the line array that is being
		filled in the concatenate function.

		Position is a variable that refers to the character location from the line
		of database file. It's value is compared in the function.
	*/
	int size, position;		

	line_ws.clear();
		
	for (position = 0, size = 0; size < key_info; position++)
	{
		if(position > 46)
		{
			line_ws += ' ';
			size++;
		}

		else
		{
			if (line[position] != ' ')
			{
				line_ws += line[position];
				size ++;
			}	
		}
	}

	return line_ws;
}

int primary_index_creator(string file_name)
{

	// Original database file
	ifstream database;

	// Index database file 
	ofstream primary_index;

	// Database file line 
	string line;

	// Database file line without space
	string line_ws;

	// Line position in file
	int line_number = 0;				

	database.open(file_name);
	primary_index.open("saida.ind", ios::out | ios::trunc);

	while(getline(database, line))
	{
		line_ws = concatenate_line(line,line_ws);

		primary_index << line_ws << " ";

		if (line_number < 10)
			primary_index << "00" << line_number << "\n";

		else if (line_number < 100)
			primary_index << "0" << line_number << "\n";

		else
			primary_index  << line_number << "\n";

		line_number++;
	}


	primary_index.close();
	database.close();

	return 1;

}