#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <string>
#include "lists.hpp"

using namespace std;

void insertion_sort (vector <generic_register> &unsorted_values);

void insertion_sort_inclusion (vector <generic_register> &sorted_values, int number_insertions);

void heapsort (vector <generic_register> &unsorted_values);

void max_heapfy (vector<generic_register> &unsorted_values, int current_node, int size);

void create_max_heap (vector<generic_register> &unsorted_values);

#endif