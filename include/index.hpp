#ifndef INDEX_HPP
#define INDEX_HPP

#include <string>
using namespace std;

typedef struct secondary_key_index_file_node *secondary_key_pointer;
typedef struct label_id_index_file_node *label_id_pointer;

typedef struct student_data
{
	string nome;
	string matricula;
	string curso;
	string turma;
	string OP;
	string NRR;
	
} student_data;


typedef struct secondary_key_index_file_node
{
	string secondary_key;

	// Next node in the secondary key list
	secondary_key_pointer next;

	// First node in label list
	label_id_pointer first;

	int id;

} secondary_key_index_file_node;

typedef struct label_id_index_file_node
{

	string primary_key;

	// Next primary key in the label file
	label_id_pointer next;

	// Same secondary key primary key pointer
	label_id_pointer brother;

	// NRR in the data file

	string NRR;
	int id;

} label_id_index_file_node;



typedef struct secondary_key_index_file 
{
	secondary_key_pointer head, tail;
	int total;

} secondary_key_index_file;

typedef struct label_id_index_file
{
	label_id_pointer head, tail;
	int total;

} label_id_index_file;



class inverted_list
{

	public:
		inverted_list();
		~inverted_list();
		void insert_data(student_data data);
		int remove_data(string input_primary_key, string input_secondary_key);
		//int update_data();

	private:
		void create_inverted_list();
		void delete_secondary_key_file(secondary_key_pointer node);
		void delete_label_id_file(label_id_pointer node);

		secondary_key_index_file secondary_key_file;		
		label_id_index_file label_id_file;

		// Indicates the data file name
		string data_file;
};

int primary_index_file_creator(string file_name);
string primary_key_creator(string line, string line_ws);
int file_header_creator (string file_name, string new_file_name);








#endif 
