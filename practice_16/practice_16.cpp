#include <iostream>
#include <queue>
using namespace std;

//Вещь, помещаемая в рюкзак
struct Element {
	double dimen;
	int price;
};

//Узел с информацией
struct Node {
	int step, cost, limit;
	double dimen;
};

//Функция сравнения
bool compare(Element x, Element y) {
	double a = (double)x.price / x.dimen;
	double b = (double)y.price / y.dimen;
	return a > b;
}

//Подсчёт границы
int limit(Node node, int n, int backpackDimen, Element x[]) {
	if (node.dimen >= backpackDimen) return 0;
	int costlimit = node.cost;
	int j = node.step + 1;
	int totaldimen = node.dimen;
	while ((totaldimen + x[j].dimen <= backpackDimen) && (j < n)) {
		totaldimen += x[j].dimen;
		costlimit += x[j].price;
		j++;
	}
	if (j < n) costlimit += (backpackDimen - totaldimen) * x[j].price / x[j].dimen;
	return costlimit;
}

//Основная функция
int backpack(int maxDimen, Element x[], int n) {
	sort(x, x + n, compare);
	queue<Node> order;
	Node node, m;
	node.step = -1;
	node.cost = 0;
	node.dimen = 0;
	order.push(node);
	int maxcost = 0;
	while (!order.empty()) {
		node = order.front();
		order.pop();
		if (node.step == -1) m.step = 0;
		if (node.step == n - 1) continue;
		m.step = node.step + 1;
		m.dimen = node.dimen + x[m.step].dimen;
		m.cost = node.cost + x[m.step].price;
		if (m.cost > maxcost && m.dimen <= maxDimen) maxcost = m.cost;
		m.limit = limit(m, n, maxDimen, x);
		if (m.limit > maxcost) order.push(m);
		m.dimen = node.dimen;
		m.cost = node.cost;
		m.limit = limit(m, n, maxDimen, x);
		if (m.limit > maxcost) order.push(m);
	}
	return maxcost;
}

int main() {
	setlocale(0,"rus");
	int max = 9;
	Element x[] = { {3, 6},{4, 3},{5, 2},{6, 5},{7, 5},{8, 1} }; //пары (вес-цена)
	int n = sizeof(x) / sizeof(x[0]);
	cout << "Рассчитанная стоимость: " << backpack(max, x, n);
	return 0;
}