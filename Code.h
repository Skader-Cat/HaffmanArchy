#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

struct elem //структура данных. Пока ещё не конечный её вид
{
	string simb;
	elem* l;
	elem* r;
	int mark = false;
	int counter;
};

string get_path(); //получает путь
string replace(string path); //меняет символы, на которые винда ругается


bool check_for_void(fstream& file); //не реализовано
fstream get_file(string path); //инициализирует файл и по хорошему тут должны выполняться функции проверок. Но у меня таких нет пока что ха-ха-ха)))

list <elem> dict_to_list(map<string, int> dict); //функция для преобразования из словаря в список. Используется ниже
list <elem> make_sluzheb_info(fstream &file, string path, int* size_of_simbs); //тут идёт чтение из файла, создание словаря. Тут же он преобразуется в список
void show_infos(list<elem> tree); //отладочная функция. Рисует дерево 
void make_node(list<elem> *tree, int size_of_simbs); //создает новый узел. size_of_simbs использовался в прошлом и являлся изначальным кол-вом символов в словаре
//но потом я нашёл лучший способ!
