#include <iostream>
#include <vector>
using namespace std;

vector <vector<int>> arr;
struct Node {
	int num;
	vector <pair<Node*, int>> sv;
	Node(int num);
};
Node::Node(int num) {
	this->num = num;
}
vector <Node*> gr;
void graph() {
	gr.resize(arr.size());
	for (int i = 0; i < arr.size(); i++) gr[i] = new Node(i+1);
}

void create() {
	bool* b = new bool[arr.size()];
	for (int i = 1; i < arr.size(); i++) b[i] = false;
	b[0] = true;
	int min, num_par, num_ch;
	for (int k = 0; k < gr.size() - 1; k++) {
		min = 10000000000;
		for (int i = 0; i < arr.size(); i++) {
			if (b[i]==true) {
				for (int j = 0; j < arr[i].size(); j++) {
					if (!b[j] and arr[i][j] != 0 and arr[i][j] < min) {
						num_par = i;
						num_ch = j;
						min = arr[i][j];
					}
				}
			}
		}
		gr[num_par]->sv.push_back(make_pair(gr[num_ch], min));
		gr[num_ch]->sv.push_back(make_pair(gr[num_par], min));
		b[num_ch] = true;
	}
}

void input() {
	int n, k, number, length;
	cout << "Кол-во вершин графа: ";
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < arr.size(); i++) {
		arr[i].resize(n);
		for (int j = 0; j < arr[i].size(); j++) arr[i][j] = 0;
	}
	for (int i = 0; i < arr.size() - 1; ++i) {
		cout << "Кол-во связей у вершины " << i + 1 << " (без повторений): ";
		cin >> k;
		for (int j = 0; j < k; j++) {
			cout << j + 1 << " связь:" << endl;
			cout << "\tНомер вершины, к которой идёт связь: ";
			cin >> number;
			cout << "\tДлина связи: ";
			cin >> length;
			arr[i][number - 1] = length;
			arr[number - 1][i] = length;
		}
	}
}

void print() {
	vector <vector<int>> ost_tree;
	ost_tree.resize(arr.size());
	for (int i = 0; i < ost_tree.size(); i++) {
		ost_tree[i].resize(ost_tree.size());
		for (int j = 0; j < ost_tree[i].size(); j++) ost_tree[i][j] = 0;
	}
	for (int i = 0; i < gr.size(); i++) {
		for (int j = 0; j < gr[i]->sv.size(); j++) {
			ost_tree[gr[i]->num - 1][gr[i]->sv[j].first->num - 1] = gr[i]->sv[j].second;
			ost_tree[gr[i]->sv[j].first->num - 1][gr[i]->num - 1] = gr[i]->sv[j].second;
		}
	}
	cout << endl;
	cout << "   ";
	for (int i = 0; i < ost_tree.size(); i++) cout << i + 1 << " ";
	cout << endl << endl;
	for (int i = 0; i < ost_tree.size(); i++) {
		cout << i + 1 << "  ";
		for (int j = 0; j < ost_tree[i].size(); j++) {
			cout << ost_tree[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	setlocale(0, "rus");
	//№ 14.1.2
	/*arr = { 
		{0,7,0,2,0,4},
		{7,0,1,2,0,0},
		{0,1,0,2,3,0},
		{2,2,2,0,6,1},
		{0,0,3,6,0,8},
		{4,0,0,1,8,0} 
	};*/
	input();
	graph();
	create();
	print();
}