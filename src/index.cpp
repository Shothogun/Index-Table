#include "index.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <ctype.h>


using namespace std;

int primary_index_creator(string file_name)
{
	ifstream database;
	ofstream primary_index;

	string line;
	string line_ws;
	int line_number = 0;
	int size, position;
	const int line_size = 62;				
	const int key_info = 30;					// Último elemento interessante para a chave

	database.open(file_name);
	primary_index.open("saida.txt", ios::out | ios::trunc);

	while(getline(database, line))
	{
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
	

		//line.erase((line.begin() + key_info) , line.end());
		//primary_index << line << endl;

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