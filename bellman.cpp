#include "bellman.h"

void BF(int G[20][20], int n, char start, int BFValue[], int BFPrev[]) {
	int startIndex = start - 'A';

	BFValue[startIndex] = (BFValue[startIndex] == -1) ? 0 : BFValue[startIndex];
	int* BFnewValue = new int[20];
	for (int i = 0; i < n; i++) {
		BFnewValue[i] = BFValue[i];
	}

	for (int u = 0; u < n; u++) {
		for (int v = 0; v < n; v++) {
			if (G[u][v] != 0 && BFValue[u] != -1 && (BFValue[u] + G[u][v] < BFnewValue[v] || BFnewValue[v] == -1)) {
				BFnewValue[v] = BFValue[u] + G[u][v];
				BFPrev[v] = u;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		BFValue[i] = BFnewValue[i];
	}
	delete[] BFnewValue;
}

string verToString(int a) {
	char m = char(a + 'A');
	string s(1, m);
	return s;
}

string BF_Path(int G[20][20], int n, char start, char end) {
	string s(1, start);
	if (start == end) {
		return s;
	}

	int endIndex = end - 'A';
	int startIndex = start - 'A';

	int BFValue[20];
	int BFPrev[20];
	for (int i = 0; i < n; i++) {
		BFValue[i] = -1;
		BFPrev[i] = -1;
	}
	for (int i = 0; i < n; i++) {
		BF(G, n, start, BFValue, BFPrev);
	}
	string m(1,end);

	while (endIndex != startIndex) {
		endIndex = BFPrev[endIndex];
		m += " " + verToString(endIndex);
	}

	reverse(m.begin(), m.end());
	return m;
}
