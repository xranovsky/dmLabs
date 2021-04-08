#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cmath>
#include <list>
#include <algorithm>
#include <stdio.h>

using namespace std;

static int it = 0;
int F = 0;

void print(int** f, int n) {
	it++;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%-5d ", f[i][j]);
		}
		cout << endl;
	}
}

bool dfs(int** c, int** f, int u, int t, list<pair<int, int>>& path, list<int>& visited, int n) {
	if (u == t) {
		cout << "Ми дiйшли до притока, завершуємо пошук шляху" << endl;
		return true;
	}
	if (find(visited.begin(), visited.end(), u) != visited.end()) {
		cout << "Цей вузол вже вiдвiданий, повертаємось назад" << endl;
		return false;
	}
	cout << "Заходимо в вузол " << u + 1 << endl;
	visited.push_back(u);
	for (int v = 0; v < n; v++) {
		if (c[u][v] - f[u][v] <= 0) continue;
		cout << "Перевiряємо вузол " << v + 1 << " залишкова пропускна здатнiсть: " << c[u][v] - f[u][v] << " > 0" << endl;
		if (dfs(c, f, v, t, path, visited, n)) {
			path.push_front({ u, v });
			return true;
		}
	}
	cout << "вiдкат, виходимо з вузла:  " << u + 1 << endl;
	return false;
}

void fordFulkerson(int** c, int** f, int s, int t, int n) {
	while (true) {
		list<pair<int, int>> path;
		list<int> visited;
		cout << "Пошук шляху, Витiк: " << s+1 << ", приток: " << t+1  << endl;
		if (!dfs(c, f, s, t, path, visited, n)) {
			cout << "Шлях не знайдено, завершуємо алгоритм, пiдсумкова матриця потокiв:" << endl;
			print(f, n);
			cout << "F = " << F << endl;
			break;
		}

		int cMin = INT_MAX;

		for (auto e : path) {
			cMin = min(cMin, c[e.first][e.second] - f[e.first][e.second]);
		}
		cout << "Мiнiмальна залишкова пропускна здатнiсть на шляху: " << cMin << endl;

		cout << "Оновлюємо матрицю потокiв" << endl;

		for (auto e : path) {
			f[e.first][e.second] += cMin;
			f[e.second][e.first] -= cMin;
		}
		print(f, n);
		F += cMin;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	freopen("l4-2.txt", "r", stdin);
	int n;
	cin >> n;
	int s = 0, t = n - 1;
	bool* visited = new bool[n];
	int** c = new int* [n], ** f = new int* [n];
	for (int i = 0; i < n; i++) {
		c[i] = new int[n];
		f[i] = new int[n];
		visited[i] = false;
		for (int j = 0; j < n; j++) {
			cin >> c[i][j];
			f[i][j] = 0;
		}
	}
	fordFulkerson(c, f, s, t, n);
}
