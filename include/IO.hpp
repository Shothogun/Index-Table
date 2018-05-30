#ifndef IO_H
#define IO_H

#include <string>
#include "lists.hpp"
#include "index.hpp"

using namespace std;

void show_primary_index (string file_name);

void show_secondary_index (string file_name_keys, string file_name_labels);

void show_registers (string file_name);

void primary_key_list_creator (primary_list* list);

void primary_key_file_updater (primary_list* list);

student_data get_register (string& formated_register);

void inverted_list_creator (inverted_list* list, string label_file, string secondary_file);

void inverted_list_files_updater (inverted_list* list, string label_file, string secondary_file);

#endif