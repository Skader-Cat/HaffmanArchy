#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

struct elem
{
	string simb;
	elem* p;
	elem* l;
	elem* r;
	int mark = false;
	int counter;
};

string get_path();
string replace(string path);


bool check_for_void(fstream& file);
bool check_for_max(list<elem>* tree, int size_of_simbs);

fstream get_file(string path);

list <elem> dict_to_list(map<string, int> dict);
list <elem> make_sluzheb_info(fstream &file, string path, int* size_of_simbs);
void show_infos(list<elem> infos);

list <elem> make_new_node(list<elem> infos);

bool check_infos(list<elem> infos, int size_of_simbs);

void make_node(list<elem> *tree, int size_of_simbs);

void sort_elems(list<elem>* tree);

