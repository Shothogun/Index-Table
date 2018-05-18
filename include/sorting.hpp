#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <string>

using namespace std;

void insertion_sort (vector <string> &unsorted_values);

void insertion_sort_inclusion (vector <string> &sorted_values, int number_insertions);

void heapsort (vector <string> &unsorted_values);

void max_heapfy (vector<string> &unsorted_values, int current_node, int size);

void create_max_heap (vector<string> &unsorted_values);

#endif