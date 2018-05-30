#include "index.hpp"
#include "IO.hpp"
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
	secondary_key_list.head = NULL;
	label_id_list.head = NULL;

}

inverted_list::~inverted_list()
{
	delete_label_id_list(label_id_list.head);	
	delete_secondary_key_list(secondary_key_list.head);
}

void inverted_list::delete_secondary_key_list(secondary_key_pointer node)
{
	if (node != NULL)
	{
		delete_secondary_key_list(node->next);
		delete node;
	}
}

void inverted_list::delete_label_id_list(label_id_pointer node)
{
	if (node != NULL)
	{
		delete_label_id_list(node->next);
		delete node;
	}
}

void inverted_list::insert_data(student_data data)
{
	label_id_pointer input_node_label = new label_id_index_list_node;
	secondary_key_pointer input_node_secondary = new secondary_key_index_list_node;

	input_node_secondary->id = secondary_key_list.total;
	input_node_label->id = label_id_list.total;
	label_id_list.total++;

	input_node_secondary->secondary_key = data.curso;

	input_node_label->line_number = data.label_line;
	input_node_label->primary_key = data.primary_key;

	// Both head should be set NULL at the initial conditions
	if( (label_id_list.head == NULL) != (secondary_key_list.head == NULL) )
	{
		cout << "ERROR(index.cpp:52)  Erro na contrução da estrutura" << endl;
	}

	// If the list is empty
	else if(label_id_list.head == NULL && secondary_key_list.head == NULL)
	{

		// Secondary's key head and tail creation
		input_node_label->brother = NULL;
		input_node_label->next = NULL;
		label_id_list.head = input_node_label;
		label_id_list.tail = input_node_label;
	

		// Secondary's key head and tail creation
		input_node_secondary->first = input_node_label;
		input_node_secondary->next = NULL;
		secondary_key_list.head = input_node_secondary;
		secondary_key_list.tail = input_node_secondary;

		secondary_key_list.total++;
	}

	// List is not empty
	else
	{

		secondary_key_pointer prev_secondary;
		secondary_key_pointer current_secondary = secondary_key_list.head;

		while(input_node_secondary->secondary_key.compare(current_secondary->secondary_key) > 0
					&& current_secondary != secondary_key_list.tail)
		{
			prev_secondary = current_secondary;
			current_secondary = prev_secondary->next;
		}

		// If the secondary key already exist
		if(input_node_secondary->secondary_key.compare(current_secondary->secondary_key) == 0)
		{

			// Seek the right position between the brother list
			label_id_pointer prev_label;
			label_id_pointer current_label = current_secondary->first;

			while(input_node_label->primary_key.compare(current_label->primary_key) > 0
						&& current_label->brother != NULL)
			{
				prev_label = current_label;
				current_label = prev_label->brother;
			}

			// If the primary key doesn't exist yet and its position is middle
			if(input_node_label->primary_key.compare(current_label->primary_key) < 0)
			{
				if(current_secondary->first == current_label)
				{
					input_node_label->brother = current_secondary->first;
					current_secondary->first = input_node_label;
				}
				else
				{
					prev_label->brother = input_node_label;
					input_node_label->brother = current_label;
				}
			}

			else if(input_node_label->primary_key.compare(current_label->primary_key) == 0)
			{
				cout << "Esse estudante ja existe. Por favor, insira outro." << endl;
				return ;
			}

			// If the primary key doesn't exist yet and is the greatest value for the brother's list(i.e. last in the list)
			else 
			{
				current_label->brother = input_node_label;
				input_node_label->brother = NULL;
			}
		}

		// If the secondary key doesn't exist yet and its position is middle
		else if(input_node_secondary->secondary_key.compare(current_secondary->secondary_key) < 0)
		{

			// Set primary key
			input_node_secondary->first = input_node_label;
			input_node_label->brother = NULL;

			if(current_secondary == secondary_key_list.head)
			{
				input_node_secondary->next = secondary_key_list.head;
				secondary_key_list.head = input_node_secondary;
			}

			else
			{
				prev_secondary->next = input_node_secondary;
				input_node_secondary->next = current_secondary;
			}

			secondary_key_list.total++;
		}

		// If the secondary key doesn't exist yet and is the greatest value of the secondary key list 
		else if(current_secondary == secondary_key_list.tail)
		{
			// Set primary key
			input_node_secondary->first = input_node_label;
			input_node_label->brother = NULL;

			secondary_key_list.tail->next = input_node_secondary;
			secondary_key_list.tail = input_node_secondary;
			input_node_secondary->next = NULL;

			secondary_key_list.total++;
		}

		else
		{

			cout << "Erro(index.cpp:179) no processo de insercao" << endl;
			return ;	
		}


		// Insert primary key in primary key file

		label_id_list.tail->next = input_node_label;
		input_node_label->next = NULL;
		label_id_list.tail = input_node_label;		
	}
}

int inverted_list::remove_data(string input_primary_key, string input_secondary_key)
{

	secondary_key_pointer prev_secondary;
	secondary_key_pointer current_secondary = secondary_key_list.head;

	// First, seek the secondary key in the secondary key file
	while(input_secondary_key.compare(current_secondary->secondary_key) != 0
				&& current_secondary != secondary_key_list.tail)
	{
		prev_secondary = current_secondary;
		current_secondary = prev_secondary->next;
	}


	// If does the second key does exist, the seek proceed in the primary keys
	// brothers list
	if(input_secondary_key == current_secondary->secondary_key)
	{
		label_id_pointer prev_label;
		label_id_pointer current_label = current_secondary->first;

		while(input_primary_key.compare(current_label->primary_key)
					&& current_label->brother != NULL)
		{
			prev_label = current_label;
			current_label = prev_label->brother;
		}

		// Found the searched data
		if(input_primary_key == current_label->primary_key)
		{

			current_label->primary_key[0] = '*';
			return 1;
		}

		// Primary key doesn't exist
		else
		{
			cout << "Chave primaria inexistente. Por favor, insira outra" << endl;
			return 0;
		}		
	}

	else
	{
		cout << "Chave secundaria inexistente. Por favor, insira outra"<< endl;	
		return 0;
	}
}

label_id_pointer inverted_list::get_head_label()
{
	return label_id_list.head;
}

secondary_key_pointer inverted_list::get_head_secondary()
{
	return secondary_key_list.head;
}

void inverted_list::set_data_file_title(string file_name)
{
	data_file = file_name;
}

string inverted_list::get_data_file_title()
{
	return data_file;
}

secondary_key_index_list inverted_list::get_secondary_key_list()
{
	return secondary_key_list;
}

label_id_index_list inverted_list::get_label_id_list()
{
	return label_id_list;
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

string primary_index_file_creator(string file_name)
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

	// Identifies that the current line was deleted
	const char deleted_indicator = '*';

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

	if (!(database.is_open()))
	{
		cout<< "Error: The program did not find "<< file_name << ".\n"; 
		return "none";
	}

	primary_index.open(name, ios::out | ios::trunc);

	while(getline(database, line))
	{
		// Verifies if the line is the header of the archive or if the line was erased
		if (line[0] == header_indicator || line[0] == deleted_indicator)
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

	return name;

}

int file_header_creator (string file_name, string new_file_name)
{
	// Identifies that the current line is a header
	const char header_indicator = '#';

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
	new_database << header_indicator << "-01\n";

	// Copy the registers to the other file
	while(getline(database,tmp_register))
	{
		new_database << tmp_register << "\n";
	}

	database.close();
	new_database.close();

	return 0;
}

int secondary_index_files_creator(string file_name)
{
	string name_sec = "indices_sec_";
	string name_label = "labels_";
	string identifier = file_name;
	string extension = ".ind";

	uint counter=0;
	int found;

	// Get the last character of the name, without the extension of normaly 4 characters
	while (counter < 4)
	{
		identifier.pop_back();

		counter ++;
	}
	identifier = identifier.back();

	// Name of the generated files
	name_sec += identifier + extension;
	name_label += identifier + extension;

	// Identifies that the current line is a header
	const char header_indicator = '#';

	// Identifies that the current line was deleted
	const char deleted_indicator = '*';

	// Original database file
	ifstream database;

	// Index databases files 
	ofstream secondary_index;
	ofstream labels_index;

	// Database file line 
	string line;

	// Database file line without space
	string line_ws;

	// Register "curso" and number of line of the last label
	generic_register major;

	// Existent classes and number of the line of the last label
	vector <generic_register> existent_classes;

	// Line position in label file
	int line_number_label = 0;				

	database.open(file_name);

	if (!(database.is_open()))
	{
		cout<< "Error: The program did not find "<< file_name << ".\n"; 
		return 0;
	}

	secondary_index.open(name_sec, ios::out | ios::trunc);
	labels_index.open(name_label, ios::out | ios::trunc);

	while(getline(database, line))
	{
		// Verifies if the line is the header of the archive or if the line was erased
		if (line[0] == header_indicator || line[0] == deleted_indicator)
		{
			continue;
		}
		major.key= secondary_key_creator(line,major.key);

		line_ws = primary_key_creator(line,line_ws);

		found = 0;
		for (counter = 0; counter < existent_classes.size() && found == 0; counter ++)
		{
			if (major.key.compare(existent_classes[counter].key) == 0)
			{
				found = 1;
				// Atualizando os indicadores da lista
				major.position = existent_classes[counter].position;
				existent_classes[counter].position = line_number_label;
			}
		}

		if (found == 0)
		{
			major.position = line_number_label;

			existent_classes.push_back(major);

			major.position = -1;
		}


		labels_index << line_ws << " ";

		if (major.position < 0)
		{
			major.position *= -1;
			labels_index << "-0" << major.position << "\n";
		}

		else if (major.position < 10)
			labels_index << "00" << major.position << "\n";

		else if (major.position < 100)
			labels_index << "0" << major.position << "\n";

		else
			labels_index  << major.position << "\n";

		line_number_label++;
	}

	for (counter = 0; counter < existent_classes.size(); counter++)
	{
		secondary_index << existent_classes[counter].key << " ";

		if (existent_classes[counter].position < 10)
			secondary_index << "00" << existent_classes[counter].position << "\n";

		else if (existent_classes[counter].position < 100)
			secondary_index << "0" << existent_classes[counter].position << "\n";

		else
			secondary_index  << existent_classes[counter].position << "\n";
	}

	labels_index.close();
	secondary_index.close();
	database.close();

	return 0;
}

string secondary_key_creator(string line, string secondary_key)
{
	/* 
		Key_position is a variable that refers to the character location from the line
		of database file.
	*/
	int counter;
	const int key_position = 52;
	const int key_size = 2;		

	secondary_key.clear();
	
	for (counter = key_position; counter < key_position + key_size; counter ++)
	{
		secondary_key.push_back(line[counter]);
	}

	return secondary_key;
}

void add_student (primary_list* prim_list, inverted_list* inv_list, string register_file)
{
	const int header_lenght = 4;
	const int line_number_lenght = 3;
	const int register_lenght = 62;

	int counter;

	student_data data;
	string full_register;
	string header;
	string deleted;
	string number;
	string tmp_register;
	char tmp_number [line_number_lenght];

	int line_number;

	fstream main_file;

	main_file.open(register_file, ios::out | ios::in);

	data = get_register(full_register);

	getline(main_file, header);

	main_file.seekp(0,main_file.end);

	// PED
	if (header[0] == '#' && header[1] != '-')
	{
		header.copy(tmp_number, line_number_lenght, 1);

		for(counter = 0; counter < line_number_lenght; counter ++)
		{
			number += tmp_number[counter];
		}

		line_number = stoi(number);

		main_file.seekg((header_lenght+1) + ((line_number-1) * (register_lenght+2)), main_file.beg);

		getline(main_file, deleted);

		number.clear();

		deleted.copy(tmp_number, line_number_lenght, 1);
		for(counter = 0; counter < line_number_lenght; counter ++)
		{
			number += tmp_number[counter];
		}

		main_file.seekp(0, main_file.beg);

		main_file << '#' << number << '\n';

		main_file.seekp((header_lenght+1) + ((line_number-1) * (register_lenght+2)), main_file.beg);
	}

	main_file << full_register;

	prim_list->insert_data(data.primary_key, prim_list->last_line + 1);

	data.label_line = inv_list->label_id_list.total;

	inv_list->insert_data(data);

	main_file.close();
}

void remove_student (primary_list* prim_list, inverted_list* inv_list, string primary_key, string register_file)
{	
	const int header_lenght = 4;
	const int line_number_lenght = 3;
	const int register_lenght = 62;

	int counter;

	primary_key_pointer* pointer;
	vector <generic_register> vector_of_list;
	int file_NRR;
	string tmp_register;
	string header;
	string number_header;
	char tmp_number [line_number_lenght];
	string secondary_key;

	fstream main_file;

	main_file.open(register_file);

	prim_list->list2vector(vector_of_list);

	pointer = prim_list->find_key(vector_of_list, primary_key);

	file_NRR = (*pointer)->file_NRR;

	main_file.seekg((header_lenght+1) + ((file_NRR-1) * (register_lenght+2)), main_file.beg);

	getline(main_file, tmp_register);

	// Atualizando a PED

		// Mudando header
	main_file.seekg(0, main_file.beg);

	getline(main_file, header);

	header.copy(tmp_number, line_number_lenght, 1);

	for(counter = 0; counter < line_number_lenght; counter ++)
	{
		number_header += tmp_number[counter];
	}

	main_file.seekp(1, main_file.beg);

	if (file_NRR < 10)
		main_file << "00" << file_NRR << "\n";

	else if (file_NRR < 100)
		main_file << "0" << file_NRR << "\n";

	else
		main_file  << file_NRR << "\n";

		// "Deletando" o espaco
	main_file.seekp((header_lenght+1) + ((file_NRR-1) * (register_lenght+2)), main_file.beg);

	main_file << '*' << number_header << ' ';

	prim_list->remove_data(pointer);

	secondary_key = secondary_key_creator(tmp_register, secondary_key);

	inv_list->remove_data(primary_key, secondary_key);
}