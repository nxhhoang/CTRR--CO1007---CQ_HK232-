#include "tsm.h"

string MverToString(int a) { // Change node to vertex
	char m = char(a + 'A');
	string s(1, m);
	return s;
}

int** newGraph(int G[20][20], int n, int start) { // swap start vertex with A vertex 
	int** Graph = new int* [n]; // create a new matrix
	for (int i = 0; i < n; i++) {
		Graph[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Graph[i][j] = G[i][j];
		}
	}


	if (start == 0) return Graph;
	for (int i = 0; i < n; i++) {
		int temp = Graph[i][0];
		Graph[i][0] = Graph[i][start];
		Graph[i][start] = temp;
	}

	for (int i = 0; i < n; i++) {
		int temp = Graph[0][i];
		Graph[0][i] = Graph[start][i];
		Graph[start][i] = temp;
	}

	int temp = Graph[0][0];
	Graph[0][0] = Graph[start][start];
	Graph[start][start] = Graph[0][0];
	return Graph;
}

void changeGraph(int** Graph, int n) { // Create a new matrix by changing zero value to maxvalue * n
	int max_value = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (Graph[i][j] > max_value && i != j) {
				max_value = Graph[i][j];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (Graph[i][j] == 0 && i != j) {
				Graph[i][j] = max_value * n;
			}
		}
	}
}

HeldKarp::HeldKarp(int G[20][20], int n, char start) {
	this->n = n;
	this->start = start;
	int two_pow_n = pow(2, n);

	this->visited = two_pow_n - 1;  // 2^n - 1

	this->dp = new int* [n];
	this->vertex = new int* [n];
	for (int i = 0; i < n; i++) {
		dp[i] = new int[two_pow_n];
		vertex[i] = new int[two_pow_n];
		for (int j = 0; j < two_pow_n; j++) { // assign initial value for dp and vertex
			dp[i][j] = INF;
			vertex[i][j] = -1;
		}
	}
	int startIndex = start - 'A';
	this->Graph = newGraph(G, n, startIndex);
	changeGraph(this->Graph, n);

	// Base case: the cost to reach each node from the starting node
	for (int i = 0; i < n; i++) {
		if (i == 0) continue;
		int first_last = (1 << i) | 1;
		this->dp[i][first_last] = Graph[0][i];
		this->vertex[i][first_last] = 0; // The parent of i when starting from 0 is 0
	}
}

void HeldKarp::process() {
	for (int Sset = 1; Sset < (1 << n); Sset += 2) {
		for (int u = 1; u < n; u++) {
			if (!(Sset & (1 << u))) continue;  // If u is not in the set, skip //!((Sset >> u) &1) 
			for (int v = 1; v < n; v++) {
				if (Sset & (1 << v) && u != v) { // If v is in the set and u != v
					int new_cost = dp[v][Sset ^ (1 << u)] + Graph[v][u];
					if (new_cost < dp[u][Sset]) {
						dp[u][Sset] = new_cost;
						vertex[u][Sset] = v; // Update parent for reconstruction
					}
				}
			}
		}
	}
}

int HeldKarp::findLastNode() const {
	int result = INF;
	int lastNode = -1;
	for (int i = 1; i < n; i++) {
		if (dp[i][visited] + Graph[i][0] < result) { // Find the last node through the smallest weighted circuit
			result = dp[i][visited] + Graph[i][0];
			lastNode = i;
		}
	}
	return lastNode;
}

string HeldKarp::findPath(int lastNode) const {
	string path = "";
	int mask = visited;
	int node = lastNode;

	while (node != -1) {
		if (node == this->start - 'A') path = char('A') + path;
		else path = MverToString(node) + path;
		int next_node = vertex[node][mask];
		mask = mask ^ (1 << node); // Remove the node from the mask
		node = next_node;
	}

	path = path + (1, start); // Add the starting node at the beginning
	string ans(1, start);

	for (int i = 1; i < n + 1; i++) { // Add some spaces for path
		ans += " ";
		ans += path[i];
	}
	return ans;
}

HeldKarp::~HeldKarp() {
	for (int i = 0; i < n; i++) {
		delete[] Graph[i];
		delete[] dp[i];
		delete[] vertex[i];
	}
	delete[] Graph;
	delete[] dp;
	delete[] vertex;
}

string Traveling(int G[20][20], int n, char start) {
	HeldKarp* tsp = new HeldKarp(G, n, start);
	tsp->process();
	string answer = tsp->findPath(tsp->findLastNode());
	delete tsp;
	return answer;
}

