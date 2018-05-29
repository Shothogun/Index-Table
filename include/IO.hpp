#ifndef IO_H
#define IO_H

#include <string>
#include "lists.hpp"

using namespace std;

void show_primary_index (string file_name);

void show_secondary_index (string file_name_keys, string file_name_labels);

void show_registers (string file_name);

void primary_key_list_creator (primary_list* list);

void primary_key_file_updater (primary_list* list);

#endif