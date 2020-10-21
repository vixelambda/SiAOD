#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
	int kod;
	string name;
	Node(int kod, string name) {
		this->kod = kod;
		this->name = name;
	}
	void output() {
		cout << "   " << this->kod << " " << this->name<< endl;
	}
};

template<typename T>
class HashTable {
	vector<list<T>> table;
	int size = 100;
	int hash(const T& t) {
		return t.kod % size;
	}
	int hash(int v) {
		return v % size;
	}
public:
	HashTable() {
		table.resize(size);
	}
	void add(const T& t) {
		table[hash(t)].push_back(t);
		if (table[hash(t)].size() > 3) rehash();
	}
	void out() {
		for (int i = 0; i < size; ++i) {
			if (!table[i].empty()) {
				cout << hash(table[i].front()) << " : ";
			}
			for (T q : table[i]) {
				q.output();
			}
		}
	}
	T find(int v) {
		for (T q : table[v % size]) {
			if (q.kod == v) return q;
		}
		return T(0, "Не найдено");
	}
	void del(int v) {
		table[hash(v)].erase(remove_if(table[hash(v)].begin(), table[hash(v)].end(), [v](const T t) {
			return t.kod==v;
			}), table[hash(v)].end());
	}
	void rehash() {
		queue<T> o;
		for (int i = 0; i < size; ++i) {
			for (T q : table[i]) {
				o.push(q);
			}
		}
		size = size * 2 + 5;
		table.clear();
		table.resize(size);
		while (!o.empty()) {
			this->add(o.front());
			o.pop();
		}
	}
};

int main() {
	setlocale(0,"rus");
	HashTable<Node> table;
	table.add(Node(90304, "ИИТ"));
	table.add(Node(345304, "КПСП"));
	table.add(Node(380310, "ИЭП"));
	table.add(Node(540810, "КПСП"));
	table.add(Node(190301, "ИТХТ"));
	table.add(Node(190345, "ИТХТ"));
	cout << "Университет с кодом специальности: 90304 - " << table.find(90304).name << endl;
	cout << "Университет с кодом специальности: 380305 - " << table.find(380305).name << endl;
	cout << endl;
	cout << "Хэш-таблица: " << endl;
	table.out(); cout << endl;
	table.del(380310);
	cout << "Хэш-таблица: " << endl;
	table.out();
}