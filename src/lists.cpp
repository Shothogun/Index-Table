#include "lists.hpp"
#include "sorting.hpp"

#include <iostream>

 // PRIMARY LIST
primary_list::primary_list ()
{
	primary_index_file = "none";

	// Creating the head node
	primary_key_list.start = new primary_index_list_node;
	primary_key_list.end = primary_key_list.start;
	primary_key_list.current = primary_key_list.end;

	primary_key_list.start->next = NULL;
	primary_key_list.start->primary_key = "none";
}

primary_list::primary_list (string file_name)
{
	primary_index_file = file_name;

	// Creating the head node
	primary_key_list.start = new primary_index_list_node;
	primary_key_list.end = primary_key_list.start;
	primary_key_list.current = primary_key_list.end;

	primary_key_list.start->next = NULL;
	primary_key_list.start->primary_key = "none";
}

primary_list::~primary_list ()
{
	delete_list();
	delete primary_key_list.start;
}

void primary_list::insert_data (string primary_key, int file_NRR)
{
	// Creating a new node in the end of the list
	primary_key_list.end->next = new primary_index_list_node;

	primary_key_list.end = primary_key_list.end->next;

	primary_key_list.end->next = NULL;

	// Giving the new node data
	primary_key_list.end->primary_key = primary_key;

	primary_key_list.end->file_NRR = file_NRR;
}

void primary_list::delete_list()
{
	while (primary_key_list.end != primary_key_list.start)
	{
		if (primary_key_list.start->next == primary_key_list.end)
		{
			primary_key_list.end = primary_key_list.start;
		}	
		remove_data(&(primary_key_list.start->next));	
	}
}
// node_pointer must be a pointer to a pre_allocated node
void primary_list::remove_data(primary_key_pointer* node_pointer)
{
	primary_key_pointer tmp_pointer;

	tmp_pointer = (*node_pointer)->next;
	delete *node_pointer;
	*node_pointer = tmp_pointer;
}

void primary_list::list2vector (vector<generic_register>& vector_of_list)
{
	generic_register tmp_register;

	vector_of_list.clear();

	primary_key_list.current = primary_key_list.start->next;
	while (primary_key_list.current != NULL)
	{
		tmp_register.key = primary_key_list.current->primary_key;
		tmp_register.position = primary_key_list.current->file_NRR;

		vector_of_list.push_back(tmp_register);

		primary_key_list.current = primary_key_list.current->next;
	}
}
// Vector must have the same size of the list
void primary_list::vector2list (vector<generic_register>& vector_of_list)
{
	int counter = 0;

	primary_key_list.current = primary_key_list.start->next;
	while (primary_key_list.current != NULL)
	{
		primary_key_list.current->primary_key = vector_of_list[counter].key;
		primary_key_list.current->file_NRR = vector_of_list[counter].position;

		primary_key_list.current = primary_key_list.current->next;

		counter ++;
	}
}

primary_key_pointer* primary_list::find_key(vector<generic_register>& vector_of_list, string primary_key)
{
	int position;
	int counter;

	insertion_sort(vector_of_list);

	position = binary_search(vector_of_list, primary_key, 0, vector_of_list.size() - 1);

	if (position == -1)
	{
		cout << "Key not found";
	}

	vector2list (vector_of_list);

	primary_key_list.current = primary_key_list.start;

	for (counter = 0; counter < position; counter++)
	{
		primary_key_list.current = primary_key_list.current->next;
	}

	return &(primary_key_list.current->next);
}

int binary_search (vector<generic_register>& vector_of_list, string primary_key, int start, int end)
{
	int middle;
	int position;

	middle = (start + end)/2;

	if (middle == start || middle == end)
	{
		if (primary_key.compare(vector_of_list[start].key) == 0)
			return start;

		else if (primary_key.compare(vector_of_list[end].key) == 0)
			return end;

		else 
			return -1;
	}

	if (primary_key.compare(vector_of_list[middle].key) < 0)
	{
		position = binary_search(vector_of_list, primary_key, start, middle - 1);
	} 
	else if (primary_key.compare(vector_of_list[middle].key) > 0)
	{
		position = binary_search(vector_of_list, primary_key, middle + 1, end);
	}
	else if (primary_key.compare(vector_of_list[middle].key) == 0)
	{
		position = middle;
	}
	return position;
}