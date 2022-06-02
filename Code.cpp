#include "Code.h"


string get_path() {
	string path;
	cout << "Введите полный путь до файла, который желаете сжать:" << endl;
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

bool check_for_void(fstream &file) {
	//функция для проверки файла на наличие символов. 
	return true;
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
		cout << i << ")Буква " << it->first << " встречалась " << it->second << " раз" << endl;
	}
	*size_of_simbs = dict_count.size();
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
			el.p = nullptr;
			els.push_back(el);
		}

	return els;
}

void sort_elems(list<elem> *tree) {
	elem temp;
	bool flag = true;
	
	list<elem>::iterator it;
	list<elem>::iterator jt =  tree->begin();

}

bool check_for_max(list<elem> *tree, int size_of_simbs) {
	bool flag = false;
	list<elem>::iterator it = tree->begin();
	for (; it != tree->end(); it++) {
		if (it->simb.size() == size_of_simbs) {
			return true;
		}
	}
	show_infos(*tree);
	return false;
}

void make_node(list<elem> *tree, int size_of_simbs) {
		show_infos(*tree);
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
					predmin =
					minim = it->counter;
					minim_p = &(*it);
			}
			if (it->mark == false) {
				count += 1;
			}
		}
		it = tree->begin();
		list<elem>::iterator jt = tree->begin();
		if (count == 2) {
			jt++;
			for (; it != tree->end(); it++) {
				for (; jt != tree->end(); jt++) {
					if (it->mark == false and jt->mark == false) {
						if (it->mark == false and jt->mark == false) {
							if (it->counter > jt->counter) {
								minim_p = &(*jt);
								predmin_p = &(*it);
							}
							if (it->counter > jt->counter) {
								predmin_p = &(*jt);
								minim_p = &(*it);
							}
						}
					}
				}
				jt = tree->begin();
			}
		}
		for (it = tree->begin(); it != tree->end(); it++) {
			if ((minim_p->counter == it->counter) and (minim_p->simb != it->simb)) {
				predmin_p = &(*it);
			}
		}
		minim_p->mark = true;
		predmin_p->mark = true;
		new_elem.counter = minim_p->counter + predmin_p->counter;
		new_elem.simb = minim_p->simb + predmin_p->simb;
		new_elem.l = &(*minim_p);
		new_elem.r = &(*predmin_p);
		//cout << "New simb: " << new_elem.simb << "||Counter: " << new_elem.counter << "||L parent:" << new_elem.l->simb << "||R parent: " << new_elem.r->simb << endl;
		tree->push_back(new_elem);

}

void show_infos(list<elem> tree) {
	list<elem>::iterator it = tree.begin();
	for (; it != tree.end(); it++) {
		cout << it->simb << "||" << it->counter << "||" << it->mark << endl;
		cout << "___________________________________" << endl;
	}
}













//
//void show_infos(list<elem> infos) {
//	list <elem>::iterator it = infos.begin();
//}
//
//list <elem> make_new_node(list<elem> tree) {
//	elem new_elem;
//	list<elem>::iterator it = tree.begin();
//	int minim = INT_MAX;
//	int predmin = INT_MAX;
//	list<elem>::iterator minim_p;
//	list<elem>::iterator predmin_p;
//	for (; it != tree.end(); it++) {
//		if (it->counter < minim and it->rebro == 2) {
//			minim = it->counter;
//			minim_p = it;
//		}
//	}
//	minim_p->rebro = 0;
//	list<elem>::iterator jt = tree.begin();
//	for (; jt != tree.end(); jt++) {
//		if (jt->counter > minim_p->counter and jt->counter < predmin and jt->rebro == 2) {
//			predmin = jt->counter;
//			predmin_p = jt;
//		}
//	}
//	predmin_p->rebro = 1;
//	new_elem.counter = minim_p->counter + predmin_p->counter;
//	new_elem.simb = minim_p->simb + predmin_p->simb;
//	new_elem.left = &(minim_p->rebro);
//	new_elem.right = &(predmin_p->rebro);
//	tree.push_back(new_elem);
//	return tree;
//}


