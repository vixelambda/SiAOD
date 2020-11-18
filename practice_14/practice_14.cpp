#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cmath>
#include <algorithm>
using namespace std;

int dl;
string s;
struct Letter {
	char b;
	int k;
	string c;
	double freq;
	Letter* left;
	Letter* right;
	Letter(char b, int k) {
		this->b = b;
		this->k = k;
	}
	Letter(Letter* left, Letter* right) {
		b = 0;
		this->k = left->k + right->k;
		this->freq = left->freq + right->freq;
		this->left = left;
		this->right = right;
	}
};

vector<Letter*> alph;
vector<Letter*> tree;
void input() { //ввод исходной строки
	cout << "Введите ФИО: ";
	getline(cin, s);
	bool f;
	for (int i = 0; i < s.size(); i++) {
		f = false;
		for (int j = 0; j < alph.size(); j++) {
			if (s[i] == alph[j]->b) {
				f = true;
				alph[j]->k = alph[j]->k + 1;
			}
		}
		if (f == false) alph.push_back(new Letter(s[i], 1));
	}
	for (int i = 0; i < alph.size(); i++) alph[i]->freq = (double)alph[i]->k / s.size();
}

void make_kod(Letter* l) { //создание кода
	if (l->b == 0) {
		l->left->c = l->c + '0';
		l->right->c = l->c + '1';
		make_kod(l->left);
		make_kod(l->right);
	}
	else return;
}

void create_tree() { //создание дерева
	double min;
	int i_left, i_right;
	tree.resize(alph.size());
	for (int i = 0; i < tree.size(); i++) tree[i] = alph[i];
	while (tree.size() != 1) {
		min = 2;
		for (int i = tree.size() - 1; i >= 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				if (tree[i]->freq + tree[j]->freq < min) {
					min = tree[i]->freq + tree[j]->freq;
					i_left = j;
					i_right = i;
				}
			}
		}
		tree.push_back(new Letter(tree[i_left], tree[i_right]));
		tree.erase(tree.begin() + i_right);
		tree.erase(tree.begin() + i_left);
	}
	make_kod(tree[0]);
}

void output_kod(Letter* l) { //вывод кода
	if (l->b != 0) cout << l->b << ' ' << l->c << endl;
	else {
		output_kod(l->left);
		output_kod(l->right);
	}
}

void output_str() { //вывод строки
	cout << "Кодирование строки: " << endl;
	dl = 0;
	for (int i = 0; i < s.size(); ++i) {
		for (int j = 0; j < alph.size(); ++j) {
			if (alph[j]->b == s[i]) {
				cout << alph[j]->c << " ";
				dl += alph[j]->c.size();
			}
		}
	}
	cout << endl;
}

void raschet() { //функция необходимых рассчётов
	double koef_a = 8.0 * s.size() / dl;
	cout << "Коэффициент сжатия относительно кодировки ascii - " << koef_a << endl;
	int c = 0;
	for (int step = 1; step < alph.size(); step *= 2) c++;
	double koef_r = (double)(c * s.size()) / dl;
	cout << "Коэффициент сжатия относительно равномерного кода - " << koef_r << endl;
	double mid = (double)dl / s.size();
	cout << "Средняя длина кода - " << mid << endl;
	double d = 0;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < alph.size(); j++) {
			if (alph[j]->b == s[i]) {
				d += pow ((alph[j]->c.size() - mid), 2);
			}
		}
	}
	d = d / s.size();
	cout << "Дисперсия - " << d << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	input();
	create_tree();
	output_kod(tree[0]);
	cout << endl;
	output_str();
	raschet();
}