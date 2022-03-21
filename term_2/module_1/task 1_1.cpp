/*Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
Вариант 2. Для разрешения коллизий используйте двойное хеширование.
https://contest.yandex.ru/contest/35212/problems/
66286934*/

#include <iostream>
#include <vector>
using namespace std;
 
 
int Hash(string str, int m) {
  int hash = 0;
	int a = m - 1;
	for (auto i: str) {
		hash = (hash * a + i) % m;
	}
	return hash;
}
 
int step(int j) {
	return j * j;
}
 
class HashTable {
private:
	int cells;
	double added = 0;
	vector<pair <string, int>> table;
	double LoadFactor(){
		return added / cells;
	}
public:
	HashTable() {
		cells = 8;
		table.resize(cells);
	}
	bool Add(string s){
		int hash = Hash(s, cells);
		int j = 1;
		while(table[hash].first != "" || table[hash].second == 1) {
			if (table[hash].first == s) {
				return false;
			}
			hash += step(j);
			j++;
			hash %= cells;
		}
		table[hash].first = s;
		added++;
		if (LoadFactor() > 0.75) {
			recalc();
		}
		return true;
	}
	void recalc() {
		cells *= 2;
		vector<string> allelems;
		for (auto elem : table) {
			if (elem.first != "") {
				allelems.push_back(elem.first);
			}
		}
		table.clear();
		table.resize(cells);
    	added = 0;
		for (auto elem : allelems) {
			Add(elem);
		}
		added = allelems.size();
	}
	bool Find(string s) {
		int hash = Hash(s, cells);
		int j = 1;
		while(table[hash].first != "" || table[hash].second == 1) {
			if (table[hash].first == s) {
				return true;
			}
			hash += step(j);
			j++;
			hash %= cells;
		}
		return false;
	}
	bool Remove(string s) {
		int hash = Hash(s, cells);
		int j = 1;
		while(table[hash].first != "" || table[hash].second == 1) {
			if (table[hash].first == s) {
				table[hash].first = "";
				table[hash].second = 1;
				return true;
			}
			hash += step(j);
			j++;
			hash %= cells;
		}
		return false;
	}
};
 
int main() {
	HashTable htvector;
	char command;
	string str;
	while (cin >> command >> str) {
		if (command == '+') {
			cout << (htvector.Add(str) ? "OK" : "FAIL") << endl;
		}
		else if (command == '?') {
			cout << (htvector.Find(str) ? "OK" : "FAIL") << endl;
		}
		else if (command == '-') {
			cout << (htvector.Remove(str) ? "OK" : "FAIL") << endl;
		}
	}
}
