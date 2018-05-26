#include "index.hpp"

using namespace std;

int main()
{
	primary_index_file_creator("../listas/lista1.txt");
	primary_index_file_creator("../listas/lista2.txt");
	file_header_creator ("../listas/lista1.txt","registros1.txt");
	file_header_creator ("../listas/lista1.txt","registros2.txt");

	return 0;
}