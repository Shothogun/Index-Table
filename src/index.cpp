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

void inverted_list::insert_data(student_data data)
{
	label_id_pointer input_node_label = new label_id_index_file_node;
	secondary_key_pointer input_node_secondary = new secondary_key_index_file_node;
	const int primary_key_length = 30;

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

	input_node_label->next = NULL;
	input_node_secondary->next = NULL;


	// Both head should be set NULL at the initial conditions
	if( (label_id_file.head == NULL) != (secondary_key_file.head == NULL) )
	{
		cout << "ERROR(index.cpp:52)  Erro na contrução da estrutura" << endl;
	}

	// If the list is empty
	else if(label_id_file.head == NULL && secondary_key_file.head == NULL)
	{
		// Secondary's key head and tail creation
		label_id_file.head = input_node_label;
		label_id_file.tail = input_node_label;
		input_node_label = NULL;

		// Secondary's key head and tail creation
		secondary_key_file.head = input_node_secondary;
		secondary_key_file.tail = input_node_secondary;
		secondary_key_file.head->first = NULL;
		input_node_secondary = NULL;
	}

	// List is not empty 
	else 
	{
		/*
			Insert a new secondary key in the secondary key file
			if it doesn't exist yet. Else, only the label id file is modified
		*/

		secondary_key_pointer prev_secondary;
		secondary_key_pointer current_secondary = secondary_key_file.head;


		while(input_node_secondary->secondary_key.compare(current_secondary->secondary_key) > 0
						&& prev_secondary != secondary_key_file.tail)
		{
			prev_secondary = current_secondary;
			current_secondary = prev_secondary->next;
		}

		// There is a key like input
		if (input_node_secondary->secondary_key.compare(current_secondary->secondary_key) == 0)
		{
			
		}

		// If there isn't any key like input
		else
		{
			//Insert input node in the label id file
			label_id_file.tail = input_node_label;
			secondary_key_file.total++;

			// It's the smallest
			if(current_secondary == secondary_key_file.head)
			{
				input_node_secondary->next = secondary_key_file.head;
				secondary_key_file.head = input_node_secondary;
			}

			// It's the greatest
			else if(prev_secondary == secondary_key_file.tail)
			{
				secondary_key_file.tail->next = input_node_secondary;
				secondary_key_file.tail = input_node_secondary;
			}

			// It's in the middle
			else
			{
				prev_secondary->next = input_node_secondary;
				input_node_secondary->next = current_secondary;
			}
		}
	}
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