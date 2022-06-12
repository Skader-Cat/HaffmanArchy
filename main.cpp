#include "Code.h"
using namespace std;

int main() {
	setlocale(0, "rus");
	bool flag = false;
	int size_of_simbs; //изначальное кол-во символов
	string path = get_path("”кажите путь до файла, который желаете сжать!");
	fstream file;
	file = get_file(path);
	list<elem> tree = make_sluzheb_info(file, path, &size_of_simbs);
	for (int i = 0; i < size_of_simbs - 1; i++) {
		make_node(&tree, size_of_simbs);
	}
	show_infos(&tree);
	list<elem>::iterator it = tree.begin();
	it->p = "koren";
	elem* elem = &(*it);
	obhod(elem);
	show_codes_table();
	make_output(file, path);
};

