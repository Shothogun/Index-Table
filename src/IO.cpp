#include "IO.hpp"
#include "index.hpp"

#include <iostream>
#include <fstream>

using namespace std;

// Nome e endereco do arquivo passado como parametro deve existir (endereco em relacao ao diretorio do executavel)

void show_primary_index (string file_name)
{
	string file_data;
	ifstream index;

	index.open (file_name);
	
	if (index.fail())
	{
		cout << "ERROR: Arquivo "<< file_name <<" nao encontrado. \n";
		return;
	}

	cout << "---Arquivo de chaves primarias: \n\n";

	while (getline (index, file_data))
	{
		cout << file_data << "\n";
	}

	index.close();
} // show_primary index

// Nome e endereco do arquivo passado como parametro deve existir (endereco em relacao ao diretorio do executavel)

void show_secondary_index (string file_name_keys, string file_name_labels)
{
	string file_data;
	ifstream secondary_keys, labels;

	secondary_keys.open (file_name_keys);
	
	if (secondary_keys.fail())
	{
		cout << "ERROR: Arquivo "<< file_name_keys <<" nao encontrado. \n";
		return;
	}

	labels.open (file_name_labels);

	if (labels.fail())
	{
		cout << "ERROR: Arquivo "<< file_name_labels <<" nao encontrado. \n";
		return;
	}


	cout << "\n---Arquivo de chaves secundarias: \n\n";

	while (getline (secondary_keys, file_data))
	{
		cout << file_data << "\n";
	}

	cout << "\n---Arquivo de identificadores: \n\n";

	while (getline (secondary_keys, file_data))
	{
		cout << file_data << "\n";
	}

	secondary_keys.close();
	labels.close();
} // show_secondary_index

// Nome e endereco o arquivo passado como parametro deve existir (endereco em relacao ao diretorio do executavel)

void show_registers (string file_name)
{
	string file_data;
	ifstream registers;

	registers.open (file_name);
	
	if (registers.fail())
	{
		cout << "ERROR: Arquivo "<< file_name <<" nao encontrado. \n";
		return;
	}

	cout << "---Arquivo de registros: \n\n";

	while (getline (registers, file_data))
	{
		cout << file_data << "\n";
	}

	registers.close();
} // show_registers

/*

int get_register (string& formated_register)
{
	int bar_counter; // Conta quantas barras (/) foram localizadas na string.
	unsigned int position_register, position_student; // Posicoes atuais nas respectivas strings.
	unsigned int data_size [5] = {7, 41, 3, 9, 1};
	string student;
	cout << "\n>>>>>> Escreva todos os dados do registro separados por barras (/).\n";
	cout << "\n>>>>>> Ordem dos dados: (Matricula/Nome/Op/Curso/Turma).\n\n";

	// Captura os dados do terminal
	getline (cin, student);
	getchar();

	for(position_student = 0; position_student < student.size(); position_student ++)
	{
		if (student[position_student] == '/')
		{
			while (position_register < data_size[bar_counter])
			{
				formated_register[position_register] = ' ';
				position_register ++;
			}

			bar_counter ++;
		}

		else 
		{
			formated_register[position_register] = student[position_student];
		}
	}

	if (bar_counter)

	return 0;
} // get_register

*/

void primary_key_list_creator (primary_list* list)
{
	int counter;

	const int line_number_lenght = 3;
	const int primary_key_lenght = 30;

	string tmp_primary_key;
	string tmp_number;
	char tmp_line_number[line_number_lenght];
	int line_number;

	ifstream primary_index;

	primary_index.open(list->primary_index_file);

	while(getline(primary_index, tmp_primary_key))
	{
		tmp_number.clear();

		tmp_primary_key.copy(tmp_line_number, line_number_lenght, primary_key_lenght + 1);
		tmp_primary_key = tmp_primary_key.erase(primary_key_lenght, line_number_lenght + 1);

		for(counter = 0; counter < line_number_lenght; counter ++)
		{
			tmp_number += tmp_line_number[counter];
		}

		line_number = stoi(tmp_number);

		list->insert_data(tmp_primary_key, line_number);
	}

	primary_index.close();
}


void primary_key_file_updater (primary_list* list)
{
	//const int primary_key_lenght = 30;

	ofstream primary_index;

	primary_index.open(list->primary_index_file, ios::out | ios::trunc);

	list->primary_key_list.current = list->primary_key_list.start->next;

	while (list->primary_key_list.current != NULL)
	{
		primary_index << list->primary_key_list.current->primary_key;

		if (list->primary_key_list.current->file_NRR < 10)
			primary_index << " 00" << list->primary_key_list.current->file_NRR << "\n";

		else if (list->primary_key_list.current->file_NRR < 100)
			primary_index << " 0" << list->primary_key_list.current->file_NRR << "\n";

		else
			primary_index  << ' ' <<list->primary_key_list.current->file_NRR << "\n";

		list->primary_key_list.current = list->primary_key_list.current->next;
	}
}
