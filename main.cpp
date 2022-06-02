#include "Code.h"
using namespace std;

int main() {
	setlocale(0, "rus");
	bool flag = false;
	int size_of_simbs; //изначальное кол-во символов
	string path = get_path();
	fstream file;
	file = get_file(path);
	list<elem> tree = make_sluzheb_info(file, path, &size_of_simbs);
	for (int i = 0; i < size_of_simbs-1; i++) {
		make_node(&tree, size_of_simbs);
	}
	list<elem>::iterator it = tree.end();
	it--;
	cout << "Корень дерева: " << it->simb << endl;
	cout << "Левый родитель: " << it->l->simb << endl;
	cout << "Правый родитель: " << it->r->simb << endl;
	cout << "Левый родитель левого родителя: " << it->l->l->simb << endl;
	cout << "Правый родитель левого родителя: " << it->l->r->simb << endl;
};

