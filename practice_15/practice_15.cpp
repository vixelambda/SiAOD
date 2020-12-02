#include <iostream>
#include <vector>
using namespace std;

void multiply(vector<int> vec) {
	int n = vec.size() - 1;
	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
		arr[i][i] = 0;
	}
	for (int q = 1; q < n; q++) {
		for (int i = 0; i < n - q; i++) {
			int j = i + q;
			arr[i][j] = INT_MAX;
			for (int k = i; k < j; k++) {
				arr[i][j] = min(arr[k + 1][j] + arr[i][k] + vec[i] * vec[j + 1] * vec[k + 1], arr[i][j]);
			}
		}
	}
	cout << arr[0][n - 1];
}

int main() {
	setlocale(0, "rus");
	vector<int> vec = {5, 10, 3, 12, 5, 50, 6};
	cout << "Минимальное кол-во скалярных умножений - ";
	multiply(vec);
	cout << endl;
	cout << "Оценка сложности - О(n^3)" << endl;
	return 0;
}