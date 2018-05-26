#include "index.hpp"
#include <iostream>
#include <fstream>

using namespace std;


/*

A fazer:

	-	Remover registro
	-	Atualizar registro
	- Merge de arquivos
	- Passar o linked list em arquivo indice e arquivo principal(mem. principal em mem. secundaria)
		- Vice-versa

*/

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

void inverted_list::insert_data(student_data data)
{
	label_id_pointer input_node_label = new label_id_index_file_node;
	secondary_key_pointer input_node_secondary = new secondary_key_index_file_node;
	const int primary_key_length = 30;
	label_id_file.total++;

	input_node_secondary->secondary_key = data.curso;

	input_node_label->NRR = data.NRR;
	input_node_label->primary_key = data.matricula;
	input_node_label->primary_key += data.nome;


	// Set the 30 characters primary key
	if(input_node_label->primary_key.length() > primary_key_length)
	{
		input_node_label->primary_key.erase(input_node_secondary->secondary_key.begin()+29,
																						input_node_secondary->secondary_key.end());
	}

	// Both head should be set NULL at the initial conditions
	if( (label_id_file.head == NULL) != (secondary_key_file.head == NULL) )
	{
		cout << "ERROR(index.cpp:52)  Erro na contrução da estrutura" << endl;
	}

	// If the list is empty
	else if(label_id_file.head == NULL && secondary_key_file.head == NULL)
	{
		// Secondary's key head and tail creation
		input_node_label->brother = NULL;
		label_id_file.head = input_node_label;
		label_id_file.tail = input_node_label;
		label_id_file.head->next = NULL;
		label_id_file.tail->next = NULL

		// Secondary's key head and tail creation
		input_node_secondary->first = NULL;
		secondary_key_file.head = input_node_secondary;
		secondary_key_file.tail = input_node_secondary;
		secondary_key_file.head->next = NULL;
		secondary_key_file.tail->next = NULL;

	}


}

int inverted_list::remove_data(string input_primary_key, string input_secondary_key)
{



}


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