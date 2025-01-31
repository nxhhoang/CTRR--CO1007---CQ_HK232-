#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
#include "bellman.h"
#include "tsm.h"

using namespace std;

int main() {
    int G[20][20] = {
        {0, 12, 35, 48, 19, 56, 17, 29, 83, 76, 39, 27, 64, 91, 58, 32, 46, 55, 73, 61},
        {12, 0, 47, 92, 53, 28, 84, 67, 15, 49, 62, 74, 31, 16, 89, 77, 52, 40, 22, 33},
        {35, 47, 0, 26, 81, 34, 23, 72, 19, 91, 55, 43, 78, 69, 50, 90, 28, 13, 77, 25},
        {48, 92, 26, 0, 37, 88, 15, 40, 61, 70, 32, 94, 52, 21, 73, 18, 36, 47, 53, 20},
        {19, 53, 81, 37, 0, 50, 27, 68, 44, 30, 85, 57, 63, 89, 11, 64, 29, 71, 33, 46},
        {56, 28, 34, 88, 50, 0, 76, 45, 83, 55, 39, 92, 17, 58, 44, 27, 72, 91, 48, 36},
        {17, 84, 23, 15, 27, 76, 0, 65, 41, 22, 81, 53, 69, 14, 89, 31, 78, 25, 37, 67},
        {29, 67, 72, 40, 68, 45, 65, 0, 73, 11, 94, 60, 18, 52, 79, 36, 54, 41, 33, 20},
        {83, 15, 19, 61, 44, 83, 41, 73, 0, 32, 28, 85, 55, 46, 91, 37, 68, 59, 47, 22},
        {76, 49, 91, 70, 30, 55, 22, 11, 32, 0, 64, 29, 83, 57, 18, 75, 41, 23, 65, 48},
        {39, 62, 55, 32, 85, 39, 81, 94, 28, 64, 0, 71, 43, 59, 13, 26, 77, 31, 50, 72},
        {27, 74, 43, 94, 57, 92, 53, 60, 85, 29, 71, 0, 38, 61, 19, 80, 22, 47, 34, 15},
        {64, 31, 78, 52, 63, 17, 69, 18, 55, 83, 43, 38, 0, 26, 70, 41, 30, 12, 89, 57},
        {91, 16, 69, 21, 89, 58, 14, 52, 46, 57, 59, 61, 26, 0, 35, 78, 63, 45, 81, 34},
        {58, 89, 50, 73, 11, 44, 89, 79, 91, 18, 13, 19, 70, 35, 0, 33, 21, 62, 29, 25},
        {32, 77, 90, 18, 64, 27, 31, 36, 37, 75, 26, 80, 41, 78, 33, 0, 88, 49, 55, 42},
        {46, 52, 28, 36, 29, 72, 78, 54, 68, 41, 77, 22, 30, 63, 21, 88, 0, 19, 82, 57},
        {55, 40, 13, 47, 71, 91, 25, 41, 59, 23, 31, 47, 12, 45, 62, 49, 19, 0, 33, 74},
        {73, 22, 77, 53, 33, 48, 37, 33, 47, 65, 50, 34, 89, 81, 29, 55, 82, 33, 0, 17},
        {61, 33, 25, 20, 46, 36, 67, 20, 22, 48, 72, 15, 57, 34, 25, 42, 57, 74, 17, 0}
    };
    int BFValue[20];
    int BFPrev[20];
    int n = 20;
    for (int i = 0; i < n; i++) {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "Test for BF: " << endl;
    //////////////////////////BF//////////////////////////////
    for (int i = 0; i < n; i++) {
        BF(G, n, 'D', BFValue, BFPrev);
        cout << "step" << i + 1 << ":" << endl;
        for (int j = 0; j < n; j++) {
            cout <<setw(3) << BFValue[j] << " ";
        }
        cout << endl;
        for (int j = 0; j < n; j++) {
            cout << setw(3) <<  BFPrev[j] << " ";
        }
        cout << endl;
    }


    //////////////////////////BF_path/////////////////////////
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    char start = 'A';
    char end = 'D';
    cout << "Test for BF Path: ";
    cout << endl << "The smallest weighted path from "<<start<<" to "<<end<<" is: ";
    cout << BF_Path(G, n, start, end) << endl;



    //////////////////////////Traveling///////////////////////
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    string output = Traveling(G, n, 'A');
    int cost = 0;
    for (int i = 0; i < n + n; i += 2) {
        cost += G[output[i] - 'A'][output[i + 2] - 'A'];
    }
    double partile = 0.1;
    cout << "Test for Traveling: " << endl;
    cout << "Halmilton circuit: " << output << endl;
    cout << "Cost: " << cost << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    return 0;
}