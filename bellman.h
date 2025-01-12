#ifndef _BELLMAN_H_
#define _BELLMAN_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//G[20][20]
void BF(int G[20][20], int n, char start, int BFValue[], int BFPrev[]);

string verToString(int a);

string BF_Path(int G[20][20], int n, char start, char end);
#endif //_BELLMAN_H_
