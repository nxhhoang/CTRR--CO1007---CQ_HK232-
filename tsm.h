#ifndef _TSM_H_
#define _TSM_H_

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
#include <vector>

using namespace std;

class HeldKarp {
private:
    int visited; //flag danh dau dinh
    int n; //the number of vertices
    char start; //the starting vertex
    int** dp;  //array uses for value memorization
    int** vertex;  //array uses for path memorization
    int** Graph;  // a changed graph
    const int INF = INT_MAX; 
public:
    HeldKarp(int G[20][20], int n, char start);
    void process();
    int findLastNode() const;
    string findPath(int lastNode) const;
    ~HeldKarp();
};
int** newGraph(int G[20][20], int n, int start);

void changeGraph(int** Graph, int n);

string Traveling(int G[20][20], int n, char start);

string MverToString(int a);

#endif //_TSM_H_
