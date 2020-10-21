#include <iostream>
using namespace std;
int m; bool b=true;

struct node {
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { 
		key = k;
		left = 0;
		right = 0;
		height = 1;
	}
};

unsigned char height(node* p) {
	if (p) return p->height;
	else return 0;
}

int balancefactor(node* p) {
	return height(p->right) - height(p->left);
}

void fixheight(node* p) {
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	if (hl > hr) p->height = hl + 1;
	else p->height = hr + 1;
}

node* rotateright(node* p) {
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) {
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) {
	fixheight(p);
	if (balancefactor(p) == 2)
	{
		if (balancefactor(p->right) < 0) p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (balancefactor(p) == -2)
	{
		if (balancefactor(p->left) > 0) p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

node* insert(node* p, int k) {
	if (!p) return new node(k);
	if (k < p->key) p->left = insert(p->left, k);
	else p->right = insert(p->right, k);
	return balance(p);
}

node* find_min(node* p) {
	if (p->left) return find_min(p->left);
	else return p;
}

node* remove_min(node* p) {
	if (p->left == 0) return p->right;
	p->left = remove_min(p->left);
	return balance(p);
}

node* remove(node* p, int k) {
	if (!p) return 0;
	if (k < p->key) p->left = remove(p->left, k);
	else if (k > p->key) p->right = remove(p->right, k);
	else {
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = find_min(r);
		min->right = remove_min(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void print_tree(node* t, int n) {
	for (int i = 0; i < n; i++) {
		cout << " ";
	}
	if (n != 0) {
		if (b) cout << "R-";
		else cout << "L-";
	}
	else cout << "K-";
	cout << t->key << endl;
	if (t->right != NULL) {
		m = n + 3;
		b = true;
		print_tree(t->right, m);
	}
	if (t->left != NULL) {
		m = n + 3;
		b = false;
		print_tree(t->left, m);
	}
}

int main() {
	setlocale(0, "rus");
	cout << "Кол-во элементов: ";
	int n;
	cin >> n;
	cout << "Введите последовательность: ";
	int* a = new int[n];
	cin >> a[0];
	node* root = insert(NULL, a[0]);
	for (int i = 1; i < n; i++) {
		cin >> a[i];
		root = insert(root, a[i]);
	}
	print_tree(root, 0);
	insert(root,30);
	print_tree(root, 0);
	return 0;
}