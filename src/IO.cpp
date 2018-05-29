#include "IO.hpp"

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

student_data get_register (string& formated_register)
{
	int bar_counter = 0; // Conta quantas barras (/) foram localizadas na string.
	unsigned int position_register = 0, position_student; // Posicoes atuais nas respectivas strings.
	unsigned int data_size [5] = {7, 48, 52, 61, 62};
	string student;
	string primary_key;
	string f_register;
	student_data data;
	cout << "\n>>>>>> Escreva todos os dados do registro separados por barras (/).\n";
	cout << "\n>>>>>> Ordem dos dados: (Matricula/Nome/Op/Curso/Turma).\n\n";

	// Captura os dados do terminal
	getline (cin, student);

	for(position_student = 0; position_student < student.size(); position_student ++)
	{
		if (student[position_student] == '/')
		{
			while (position_register < data_size[bar_counter])
			{
				f_register += ' ';
				position_register ++;
			}

			bar_counter ++;
		}

		else 
		{
			f_register += student[position_student];
			position_register ++;

			switch (bar_counter)
			{
				case 0:
					data.matricula.push_back(student[position_student]);
					break;

				case 1:
					data.nome.push_back(student[position_student]);
					break;

				case 2:
					data.OP.push_back(student[position_student]);
					break;

				case 3:
					data.curso.push_back(student[position_student]);
					break;

				case 4:
					data.turma.push_back(student[position_student]);
					break;
			}
		}
	}
	primary_key = primary_key_creator(f_register, primary_key);

	data.primary_key = primary_key;

	formated_register = f_register;

	return data;
} // get_register


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

void inverted_list_creator (inverted_list* list, string label_file, string secondary_file)
{
	const int line_number_lenght = 3;
	const int secondary_key_lenght = 2;
	const int primary_key_lenght = 30;
	const int label_line_size = primary_key_lenght + line_number_lenght + 2;

	int counter;
	int line_number;
	string tmp_secondary_key;
	string tmp_primary_key;
	string tmp_number;
	char tmp_line_number [line_number_lenght];

	student_data tmp_student;

	ifstream labels_index;
	ifstream secondary_index;

	labels_index.open(label_file);
	secondary_index.open(secondary_file);


	// Secondary key

	while(getline(secondary_index, tmp_secondary_key))
	{
		tmp_number.clear();

		tmp_secondary_key.copy(tmp_line_number, line_number_lenght, secondary_key_lenght + 1);
		tmp_secondary_key = tmp_secondary_key.erase(secondary_key_lenght, line_number_lenght + 1);

		for(counter = 0; counter < line_number_lenght; counter ++)
		{
			tmp_number += tmp_line_number[counter];
		}

		line_number = stoi(tmp_number);

		// Labels
		while(line_number != -1)
		{
			tmp_student.curso = tmp_secondary_key;
			tmp_student.label_line = line_number;

			labels_index.seekg(line_number * label_line_size, labels_index.beg);
			getline(labels_index, tmp_primary_key);

			tmp_number.clear();

			tmp_primary_key.copy(tmp_line_number, line_number_lenght, primary_key_lenght + 1);
			tmp_primary_key = tmp_primary_key.erase(primary_key_lenght, line_number_lenght + 1);

			for(counter = 0; counter < line_number_lenght; counter ++)
			{
				tmp_number += tmp_line_number[counter];
			}

			line_number = stoi(tmp_number);

			tmp_student.primary_key = tmp_primary_key;

			list->insert_data(tmp_student);
		}

	}

	labels_index.close();
	secondary_index.close();
}

void inverted_list_files_updater (inverted_list* list, string label_file, string secondary_file)
{
	const int line_number_lenght = 3;
	const int primary_key_lenght = 30;
	const int label_line_size = primary_key_lenght + line_number_lenght + 2; 

	string tmp_secondary_key;
	string tmp_primary_key;
	int next_line_number;

	ofstream labels_index;
	ofstream secondary_index;

	labels_index.open(label_file, ios::out | ios::trunc);
	secondary_index.open(secondary_file, ios::out | ios:: trunc);

	secondary_key_pointer current_key;
	label_id_pointer current_label;

	// Secondary key
	current_key = list->secondary_key_list.head;
	while (current_key != NULL)
	{
		current_label = current_key->first;
		tmp_secondary_key = current_key->secondary_key;
		next_line_number = current_label->line_number;

		secondary_index << tmp_secondary_key << ' ';

		if (next_line_number < 0)
		{
			next_line_number *= -1;
			secondary_index << "-0" << next_line_number << "\n";
		}

		else if (next_line_number < 10)
			secondary_index << "00" << next_line_number << "\n";

		else if (next_line_number < 100)
			secondary_index << "0" << next_line_number << "\n";

		else
			secondary_index  << next_line_number << "\n";

		// Labels
		while (current_label != NULL)
		{

			labels_index.seekp(next_line_number * label_line_size, labels_index.beg);

			if (current_label->brother == NULL)
			{
				next_line_number = -1;
			}

			else 
			{
				next_line_number = current_label->brother->line_number;
			}

			tmp_primary_key = current_label->primary_key;

			labels_index << tmp_primary_key << ' ';

			if (next_line_number < 0)
			{
				next_line_number *= -1;
				labels_index << "-0" << next_line_number << "\n";
			}

			else if (next_line_number < 10)
				labels_index << "00" << next_line_number << "\n";

			else if (next_line_number < 100)
				labels_index << "0" << next_line_number << "\n";

			else
				labels_index  << next_line_number << "\n";

			current_label = current_label->brother;
		}
		current_key = current_key->next;
	}

	labels_index.close();
	secondary_index.close();
}