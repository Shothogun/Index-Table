#ifndef INDEX_HPP
#define INDEX_HPP

#include <string>
using namespace std;

typedef struct secondary_key_index_list_node *secondary_key_pointer;
typedef struct label_id_index_list_node *label_id_pointer;

typedef struct student_data
{
	string nome;
	string matricula;
	string curso;
	string turma;
	string OP;
	string NRR;
	string data_file;
	string primary_key;
	
} student_data;


typedef struct secondary_key_index_list_node
{
	string secondary_key;

	// Next node in the secondary key list
	secondary_key_pointer next;

	// First node in brothers label list(same secondary key)
	label_id_pointer first;

	int id;

} secondary_key_index_list_node;

typedef struct label_id_index_list_node
{

	string primary_key;

	// NRR in the data file

	string NRR;
	
	// Next primary key in the label file
	label_id_pointer next;

	// Same secondary key primary key list
	label_id_pointer brother;

	int id;

} label_id_index_list_node;



typedef struct secondary_key_index_list 
{
	secondary_key_pointer head, tail;
	int total = 0;

} secondary_key_index_list;

typedef struct label_id_index_list
{
	label_id_pointer head, tail;
	int total = 0;

} label_id_index_list;



class inverted_list
{

	public:
		inverted_list();
		~inverted_list();
		void insert_data(student_data data);
		int remove_data(string input_primary_key, string input_secondary_key);
		label_id_pointer get_head_label();
		secondary_key_pointer get_head_secondary();
		secondary_key_index_list get_secondary_key_list();
		label_id_index_list get_label_id_list();
		void set_data_file_title(string file_name);
		string get_data_file_title();

		//int update_data();

	private:
		void create_inverted_list();
		void delete_secondary_key_list(secondary_key_pointer node);
		void delete_label_id_list(label_id_pointer node);

		secondary_key_index_list secondary_key_list;		
		label_id_index_list label_id_list;

		// Indicates the data file name
		string data_file = "none";
};

string primary_index_file_creator(string file_name);
string primary_key_creator(string line, string line_ws);
int file_header_creator (string file_name, string new_file_name);
int secondary_index_files_creator(string file_name);
string secondary_key_creator(string line, string secondary_key);








#endif 
