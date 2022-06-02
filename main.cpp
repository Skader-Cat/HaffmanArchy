#include "Code.h"
using namespace std;

int main() {
	setlocale(0, "rus");
	bool flag = false;
	int size_of_simbs; //����������� ���-�� ��������
	string path = get_path();
	fstream file;
	file = get_file(path);
	list<elem> tree = make_sluzheb_info(file, path, &size_of_simbs);
	for (int i = 0; i < size_of_simbs-1; i++) {
		make_node(&tree, size_of_simbs);
	}
	list<elem>::iterator it = tree.end();
	it--;
	cout << "������ ������: " << it->simb << endl;
	cout << "����� ��������: " << it->l->simb << endl;
	cout << "������ ��������: " << it->r->simb << endl;
	cout << "����� �������� ������ ��������: " << it->l->l->simb << endl;
	cout << "������ �������� ������ ��������: " << it->l->r->simb << endl;
};

