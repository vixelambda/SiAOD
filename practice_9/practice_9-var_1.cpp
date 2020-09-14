#include <iostream>
#include <queue>
using namespace std;

void input(int a[], int n);
void output(int a[], int n);
int razryad(int x, int r);
void sort(int a[], int n);

int main() {
	setlocale(0,"rus");
	int n;
	cout << "Введите кол-во элементов массива: ";
	cin >> n;
	int* a = new int[n];
	input(a, n);
	sort(a, n);
	cout << "Отсортированный массив: ";
	output(a, n);
	return 0;
}

void input(int a[], int n) {
	cout << "Заполните массив: ";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

void output(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int razryad(int x, int r) {
	int z;
	for (int i = 0; i < r; i++) {
		z = x % 10;
		x = x / 10;
	}
	return z;
}

void sort(int a[], int n) {
	int max = a[0], maxd = 0;
	for (int i = 1; i < n; i++) {
		if (a[i] > max) max = a[i];
	}
	while (max > 0) {
		max = max / 10;
		maxd++;
	}
	queue<int> q[10];
	for (int i = 0; i < maxd; i++) {
		for (int j = 0; j < n; j++) {
			q[razryad(a[j], i+1)].push(a[j]);
		}
		for (int j = 0, c = 0; j < 10; j++) {
			while (!q[j].empty()) {
				a[c] = q[j].front();
				q[j].pop();
				c++;
			}
		}
	}
}