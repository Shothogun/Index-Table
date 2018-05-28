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
	const int primary_key_length = 30;

	input_node_secondary->id = secondary_key_list.total;
	input_node_label->id = label_id_list.total;
	label_id_list.total++;

	input_node_secondary->secondary_key = data.curso;

	input_node_label->NRR = data.NRR;
	input_node_label->primary_key = data.matricula;
	input_node_label->primary_key += data.nome;


	// Set the 30 characters primary key
	if(input_node_label->primary_key.length() > primary_key_length)
	{
		input_node_label->primary_key.erase(input_node_label->primary_key.begin()+30,
																						input_node_label->primary_key.end());
	}

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

			current_label->primary_key = "*";
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

/*

void inverted_list::remove_from_data_file(label_id_pointer node)
{
	string strNew = "*";
	string strTemp;
	string empty_PED = "#-1";
	string position;

	ifstream filein(data_file);
	ofstream fileout(data_file);

	if(!filein || !fileout)
	{
	  cout << "Error opening files!" << endl;
	  return ;
	}

	int i = 0;


	getline(filein, strTemp);

	// If PED is empty
	if(strTemp == empty_PED)
	{

		filein.seekg(0, filein.beg);

		while(filein >> strTemp)
	  {
	  	// Updates header
	  	if(i == 0)
	  	{
	  		if(strTemp == empty_PED)
	  		{
	  			strTemp = strNew;
	  			strTemp += node->NRR;
	  		}
	  	}

	  	//Erase data
	    if(to_string(i) == node->NRR)
	    {
	    	strTemp = strNew ;
	    	strTemp += "-1";
	    }

	    strTemp += "\n";
	    fileout << strTemp;

	    i++;
	  }
	}

	else
	{
		filein.seekg(0, filein.beg);

		while(filein >> strTemp)
	  {
	  	// Substitutes header
	  	if(i == 0)
	  	{
	  		if(empty_PED != strTemp)
	  		{
	  			strTemp.erase(0,1);

	  			// Former PED header
	  			position = strTemp;

			  	strTemp = strNew;
			  	strTemp += node->NRR;
	  		}
	  	}

	  	// Erases data
	    if(to_string(i) == node->NRR)
	    {
	    	strTemp = strNew;
	    	strTemp += position;
	    }

	    strTemp += "\n";
	    fileout << strTemp;

	    i++;
	  }
	}
	
	filein.close();
  fileout.close();
}

*/

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