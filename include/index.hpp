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
	secondary_key_pointer next;
	label_id_pointer first;
	int id;

} secondary_key_index_file_node;

typedef struct label_id_index_file_node
{
	string primary_key;
	label_id_pointer next;
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
		//int remove_data();
		//int update_data();

	private:
		void create_inverted_list();
		void delete_secondary_key_file(secondary_key_pointer node);
		void delete_label_id_file(label_id_pointer node);
		//int remove_data();
		//int update_data();

		secondary_key_index_file secondary_key_file;		
		label_id_index_file label_id_file;
};

int primary_index_file_creator(string file_name);
string primary_key_creator(string line, string line_ws);








#endif 
