#ifndef INDEX_HPP
#define INDEX_HPP

#include <string>
using namespace std;

typedef struct secondary_key_index_file_node *secondary_key_pointer;
typedef struct label_id_index_file_node *label_id_pointer;

typedef struct student_data
{
	string nome;
	int matricula;
} student_data;


typedef struct secondary_key_index_file_node
{
	string secondary_key;
	secondary_key_pointer next;

} secondary_key_index_file_node;

typedef struct label_id_index_file_node
{
	string primary_key;
	label_id_pointer next;

} label_id_index_file_node;



typedef struct secondary_key_index_file 
{
	secondary_key_pointer first;

} secondary_key_index_file;

typedef struct label_id_index_file
{
	label_id_pointer first;

} label_id_index_file;



class inverted_list
{

	public:
		inverted_list();
		~inverted_list();
		int insert_data();
		//int remove_data();
		//int update_data();

	private:
		int create_inverted_list();
		int delete_inverted_list();
		int insert_data();
		//int remove_data();
		//int update_data();

		secondary_key_index_file secondary_key_file;		
		label_id_index_file label_id_file;
		
};

int primary_index_creator(string file_name);
string concatenate_line(string line, string line_ws);








#endif 
