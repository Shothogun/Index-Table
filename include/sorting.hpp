#ifndef SORTING_H
#define SORTING_H

#include <vector>

using namespace std;

void insertion_sort (vector <int> &unsorted_values);

void insertion_sort_inclusion (vector <int> &sorted_values);

void heapsort (vector <int> &unsorted_values);

void max_heapfy (vector<int> &unsorted_values, int current_node, int size);

void create_max_heap (vector<int> &unsorted_values);

#endif