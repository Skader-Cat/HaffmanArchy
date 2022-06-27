#include "Code.h"


string get_path(string phrase) {
	string path;
	cout << phrase << endl;
	cin >> path; //надо бы ввести защиту от плохих форм путей
	return path;
}

string replace(string path) {
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == '\\') {
			path[i] = '/';	
		}
	}
	return path;
}

fstream get_file(string path){
	fstream file;
	file.open(path, ios::app | ios::binary);
	if (file.is_open()){ //есть проблема. Если путь не имеет форму пути, то пишет, что всё окей
		cout << "Файл открыт" << endl;
		//тут должна быть проверка на пустоту при помощи функции проверки))
		//if (check_for_void(file) == true) {
		//	cout << "Файл в норме. Готов к сжатию!" << endl;
		//	cout << check_for_void(file) << endl; 
		//}
		//else {
		//	cout << "Файл пуст или повреждён" << endl;
		//}
	}
	else {
		cout << "Файл по заданному пути не обнаружен" << endl;
	}
	file.close();
	return file;
}

list <elem> make_sluzheb_info(fstream& file, string path, int* size_of_simbs) {
	char simb;
	file.open(path);
	//весьма перспективная штука, если доработать
	string s = "iconv -t WINDOWS-1251 -f UTF-8 " + path + "> 1.tmp && move 1.tmp " + path; //команда для конвертации в ANSI кодировку, чтобы работать с русскими символами
	const char* sw = s.c_str();              //складывать удобнее строки, поэтому до этого я работал с ними. Но system, который выполнит мою команду, принимает только чары
	system(sw); //используем команду конвертации
	cout << "Подсчитаем кол-во символов!" << endl;
	map <string, int> dict_count;
	while (file.read((char*)&simb, sizeof(char))) {
		if (simb != ' ') {
			dict_count[string(sizeof(simb) / sizeof(char), simb)]++; //здесь я записываю в словарь строки, потому что в дальнейшем удобно работать именно в этом формате
		}
	}
	//отладка для вывода элементов

	map <string, int> ::iterator it = dict_count.begin();
	for (int i = 0; it != dict_count.end(); it++, i++) {
		cout << i << ")Символ " << it->first << " встречался " << it->second << " раз" << endl;
	}
	*size_of_simbs = dict_count.size();
	file.close();
	return dict_to_list(dict_count);
}

list <elem> dict_to_list(map <string, int> dict) {
	list<elem> els;
		map <string, int> ::iterator it = dict.begin();
		for (int i = 0; it != dict.end(); it++, i++) {
			elem el;
			el.simb = it->first;
			el.counter = it->second;
			el.l = nullptr;
			el.r = nullptr;
			el.p = "exit";
			els.push_back(el);
		}

	return els;
}

void make_node(list<elem> *tree, int size_of_simbs) {
		//show_infos(*tree);
	    elem new_elem;
		list<elem>::iterator it = tree->begin();
		int minim = INT_MAX;
		int predmin = INT_MAX;
		elem* minim_p = new elem;
		elem* predmin_p = new elem;


		int count = 0;
		for (; it != tree->end(); it++) {
			if (it->counter < minim and it->mark == false) {
					predmin_p = minim_p;
					minim = it->counter;
					minim_p = &(*it);
			}
		}
		it = tree->begin();
		list<elem>::iterator jt = tree->begin();
		minim_p->mark = true;
		for (; jt != tree->end(); jt++) {
			if (jt->counter < predmin and jt->mark == false) {
				predmin = jt->counter;
				predmin_p = &(*jt);
			}
		}
		predmin_p->mark = true;
		new_elem.counter = minim_p->counter + predmin_p->counter;
		new_elem.simb = minim_p->simb + predmin_p->simb;
		new_elem.l = &(*minim_p);
		new_elem.r = &(*predmin_p);
		if (new_elem.l != nullptr) {
			cout << new_elem.simb << " ||левый родитель: " << new_elem.l->simb << endl;
		}
		if (new_elem.r != nullptr) {
			cout << new_elem.simb << " ||правый родитель: " << new_elem.r->simb << endl;
		}
		new_elem.p = "norm";
		//cout << new_elem.l->simb << " " << new_elem.l->counter << endl;
		//cout << new_elem.r->simb << " " << new_elem.r->counter << endl;
		//cout << "New simb: " << new_elem.simb << "||Counter: " << new_elem.counter << "||L parent:" << new_elem.l->simb << "||R parent: " << new_elem.r->simb << endl;
		tree->push_front(new_elem);

}

void show_infos(list<elem> *tree) {
	list<elem>::iterator it = tree->begin();
	for (; it != tree->end(); it++) {
		it->mark = false;
		cout << it->simb << "||" << it->counter << "||" << it->mark << endl;
		cout << "___________________________________" << endl;
	}
}

map<string, string> codes_table;
string sum;
void obhod(elem* elem){
	if (elem->p == "koren") {
		sum += "0";
		obhod(elem->r);
		sum += "1";
		obhod(elem->l);
	}
	if (elem->l != nullptr and elem->p != "koren" and elem->p != "exit") {
		cout << "Нахожусь в узле : " << elem->simb << " || на данный момент код: " << sum << endl;
		elem->mark = 1;
		sum += "1";
		obhod(elem->l);
	}
	if (elem->r != nullptr and elem->p != "koren" and elem->p != "exit") {
		sum += "0";
		obhod(elem->r);
	}
	if (elem->p == "exit" and sum.size() <= 8) {
		cout << "Нахожусь в узле : " << elem->simb << " || на данный момент код: " << sum << endl;
		codes_table[elem->simb] = sum;
	}
	if (sum.size() >= 1) {
		sum.pop_back();
	}
}

void show_table(map<string, string>* table) {
	map<string, string> ::iterator mit = table->begin();
	for (; mit != table->end(); mit++) {
		cout << mit->first << " " << mit->second << endl;
	}
}

string make_output(fstream& input_file, string path, fstream& output_file) {
	input_file.open(path);
	char simb;
	int ans;
	cout << "Сохранить сжатый файл по новому пути (введите 1) или по старому (введите 0)" << endl;
	cin >> ans;
	if (ans != 0) {
		path = get_path("Укажите путь, куда нужно сохранить сжатый файл: ");
	}
	else {
		path.replace(path.find("."), 1,  "_output.");
	}
	cout << path << endl;
	output_file = get_file(path);
	output_file.open(path);
	string bin_buff, converted_string;

	map<string, string> ::iterator mit = codes_table.begin();
	for (; mit != codes_table.end(); mit++) {
		output_file << mit->first << "Ђ" << mit->second << "Њ";
	}
	output_file << "}exit" << endl;

	while (input_file.read((char*)&simb, sizeof(char))) {
		if (simb != ' ') {
			if (codes_table.count(string(sizeof(simb) / sizeof(char), simb)) == 1) {
				converted_string += codes_table[string(sizeof(simb) / sizeof(char), simb)];
			}
			else {
				output_file << simb;
			}
		}

	}
	
	converted_string.push_back('&');
	int counter = 0;
	while (converted_string[counter] != '&') {
		if (bin_buff.size() < 8) {
			bin_buff += converted_string[counter];
			counter += 1;
		}
		else {
			cout << bin_buff << endl;
			output_file << char(bitset<8>(bin_buff).to_ulong());
			bin_buff = "";
		}
	}
	output_file.close();
	input_file.close();
	return path;
}

map<string, string> decode_table;

void table_decode(fstream& output_file, string path) {
	output_file.open(path);
	char simb;
	string second;
	string sub;
	while (output_file.read((char*)&simb, sizeof(char))) {
		if (sub != "}exit") {
			sub += simb;
			if (simb == 'Ђ') {
				sub.pop_back();
				second = sub;
				sub = "";
			}
			if (simb == 'Њ') {
				sub.pop_back();
				decode_table[sub] = second;
				sub = "";
			}
		}
	}
	output_file.close();
}

void make_decode(fstream& output_file, string path) {
	output_file.open(path);
	char simb;
	string converted_string;
	while (output_file.read((char*)&simb, sizeof(char))) {
		if (simb != ' ') {
			cout << bitset<8>(simb).to_ullong() << endl;
			simb;
		}

	}
}
