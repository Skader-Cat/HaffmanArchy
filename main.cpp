#include "Code.h"
using namespace std;

int main() {
	setlocale(0, "rus");
	int ans, ans_2 = 1;
	fstream file;
	fstream output_file;

	cout << "�������� ����� ������, ����� ��������������� �����: \n1 - �����������\n2 - ������������� \n�����: ";
	cin >> ans;
	if (ans == 1) {
			bool flag = false;
			int size_of_simbs; //����������� ���-�� ��������
			string path = get_path("������� ���� �� �����, ������� ������� �����!");
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
			show_table(&codes_table);
			make_output(file, path, output_file);
	}
	else if(ans == 2) {
			string output_path = get_path("������� ���� � �����, ������� ���������� ������������!");
			table_decode(output_file, output_path);
			show_table(&decode_table);
			make_decode(output_file, output_path);
	}
};

