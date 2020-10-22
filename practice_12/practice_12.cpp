#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct library {
	int number;
	string surname;
	string name;
	string patronymic;
	string adres;
};
vector<library>l;

void print(library l) {
	cout << l.number << " " << l.surname << " " << l.name << " " << l.patronymic << " " << l.adres << endl;
}

void read_file() {
	library per;
	ifstream ifile("input.txt");
	while (!ifile.eof()) {
		ifile >> per.number >> per.surname >> per.name >> per.patronymic >> per.adres;
		l.push_back(per);
	}
}

void write_bin() {
	ofstream obin("bin.txt", ios::binary);
	for (int i = 0; i < l.size(); i++) {
		obin.write((char*)&l.at(i), sizeof(library));
	}
	obin.close();
}

void read_bin() {
	ifstream ibin("bin.txt", ios::binary);
	l.resize(l.size());
	for (int i = 0; i < l.size(); i++) {
		ibin.read((char*)&l.at(i), sizeof(library));
	}
	ibin.close();
}

void find() {
	cout << "Введите номер читательского билета: ";
	int x;
	cin >> x;
	for (int i = 0; i < l.size(); i++) {
		if (l[i].number == x) print(l[i]);
	}
}

void remove() {
	cout << "Введите номер читательского билета: ";
	int x;
	cin >> x;
	for (int i = 0; i < l.size(); i++) {
		if (l[i].number == x) {
			l.erase(l.begin() + i);
			cout << "Удаление выполнено" << endl;
		}
	}
	write_bin();
}

int main() {
	setlocale(0, "rus");
	read_file();
	write_bin();
	for (int i = 0; i < l.size(); i++) {
		print(l[i]);
	}
	find();
	remove();
	read_bin();
	for (int i = 0; i < l.size(); i++) {
		print(l[i]);
	}
}