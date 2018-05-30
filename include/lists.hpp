#ifndef LISTS_HPP
#define LISTS_HPP

#include <string>
#include <vector>

using namespace std;
 // GENERIC
typedef struct generic_register
{
	string key;

	int position;
} generic_register;

int binary_search (vector<generic_register>& vector_of_list, string primary_key, int start, int end);

 // PRIMARY_LIST
typedef struct primary_index_list_node *primary_key_pointer;

typedef struct primary_index_list_node
{
	string primary_key;

	// Next node in the primary key list
	primary_key_pointer next;

	// Register position in the main registers file 
	int file_NRR;

} primary_index_list_node;

typedef struct primary_index_list
{
	// Head of the list, dont have data
	primary_key_pointer start; 

	// Last node of the list
	primary_key_pointer end;

	// Current node of the list
	primary_key_pointer current;

} primary_index_list;

class primary_list
{

	public:
		primary_list();
		primary_list(string file_name);
		~primary_list();
		void insert_data(string primary_key, int file_NRR);
		void remove_data(primary_key_pointer* node_pointer);
		void list2vector(vector<generic_register>& vector_of_list);
		void vector2list(vector<generic_register>& vector_of_list);
		primary_key_pointer* find_key(vector<generic_register>& vector_of_list, string primary_key);

		primary_index_list primary_key_list;		

		// Indicates the data file name
		string primary_index_file;

		// Indicates the last line of the file stored
		int last_line;

	private:
		void delete_list();
};

#endif