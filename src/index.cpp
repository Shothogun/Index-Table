#include "index.hpp"
#include <iostream>
#include <fstream>

using namespace std;

inverted_list::inverted_list()
{
	secondary_key_file.head = NULL;
	label_id_file.head = NULL;

}

inverted_list::~inverted_list()
{
	delete_secondary_key_file(secondary_key_file.head);
	delete_label_id_file(label_id_file.head);	
}

void inverted_list::delete_secondary_key_file(secondary_key_pointer node)
{
	if (node != NULL)
	{
		delete_secondary_key_file(node->next);
		delete node;
	}
}

void inverted_list::delete_label_id_file(label_id_pointer node)
{
	if (node != NULL)
	{
		delete_label_id_file(node->next);
		delete node;
	}
}


/*
void inverted_list::insert_data(student_data data)
{
	if(head == NULL)
	{
		head = new node;

	}


}
*/

string primary_key_creator(string line, string line_ws)
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

int primary_index_file_creator(string file_name)
{
	string name = "indices_";
	string identifier = file_name;
	string extension = ".ind";

	int counter=0;

	// Get the last character of the name, without the extension of normaly 4 characters
	while (counter < 4)
	{
		identifier.pop_back();

		counter ++;
	}
	identifier = identifier.back();

	// Name of the generated file
	name += identifier + extension;

	// Identifies that the current line is a header
	const char header_indicator = '#';

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
	primary_index.open(name, ios::out | ios::trunc);

	while(getline(database, line))
	{
		// Verifies if the line is the header of the archive
		if (line[0] == header_indicator)
		{
			line_number++;
			continue;
		}
		cout << "1";
		line_ws = primary_key_creator(line,line_ws);

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

int file_header_creator (string file_name, string new_file_name)
{
	// Identifies that the current line is a header
	const char header_indicator = '#';

	int counter;

	ifstream database;
	ofstream new_database;

	string tmp_register;

	database.open(file_name);
	new_database.open(new_file_name, ios::out | ios::trunc);

	// Verify if the header already exists
	if (database.get() == header_indicator)
	{
		return 1;
	}
		// Go to the beginning 
	database.seekg(0, database.beg);

	// Header
	new_database << header_indicator;

	for (counter = 0; counter < 3; counter++)
	{
		new_database << ' ';  
	}
	new_database << '\n';

	// Copy the registers to the other file
	while(getline(database,tmp_register))
	{
		new_database << tmp_register << "\n";
	}

	database.close();
	new_database.close();

	return 0;
}