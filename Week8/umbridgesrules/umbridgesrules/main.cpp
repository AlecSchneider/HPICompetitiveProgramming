//
//  main.cpp
//  umbridgesrules
//
//  Created by Alec Schneider on 22.06.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <math.h>


// Shortcuts for "common" data types in contests
typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;
typedef std::set<int> si;
typedef std::map<std::string, int> msi;

// To simplify repetitions/loops, Note: define your loop style and stick with it!
#define REP(i, a, b) \
for (int i = int(a); i <= int(b); i++) // a to b, and variable i is local!
#define TRvi(c, it) \
for (vi::iterator it = (c).begin(); it != (c).end(); it++)
#define TRvii(c, it) \
for (vii::iterator it = (c).begin(); it != (c).end(); it++)
#define TRmsi(c, it) \
for (msi::iterator it = (c).begin(); it != (c).end(); it++)
#define INF 2000000000 // 2 billion

// If you need to recall how to use memset:
#define MEMSET_INF 127 // about 2B
#define MEMSET_HALF_INF 63 // about 1B
//memset(dist, MEMSET_INF, sizeof dist); // useful to initialize shortest path distances
//memset(dp_memo, -1, sizeof dp_memo); // useful to initialize DP memoization table
//memset(arr, 0, sizeof arr); // useful to clear array of integers


#pragma mark - MAIN
using namespace std;

// A structure to represent a Point in 2D plane
struct Point
{
    double x, y;
};


// A utility function to find the distance between two points
double dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y)
                );
}

void fastInput(int &number) //not thread safe
{
    register unsigned int c;
    number = 0;
    while((c = getchar_unlocked()) == ' ' || (c == '\n'));
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number *10 + c - 48;
    //cout << number << endl;
}

int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    
    #ifdef USE_INPUT_FILE
    freopen("input.txt", "r", stdin);
    #endif
    #ifdef USE_OUTPUT_FILE
    freopen("output.txt", "w", stdout);
    #endif
    
    // MAIN Begin
    
    int pupils;
    fastInput(pupils); // read n
    int minDistance = INF;
    vector<vector<Point>> floors(50);
    for (int c=0; c<pupils; c++) {
        int x, y, floor;
        fastInput(x);
        fastInput(y);
        fastInput(floor);
        floors[floor].push_back(Point{(double) x, (double)y});
        //        cin >> in;
        //        cout << out << endl; // write result on stdout
    }
    for (int i = 0; i < 50; i ++) {
        if (floors[i].size() < 2) continue;
        for (int j = 0; j < floors[i].size()-1; j++) {
            for (int k = j+1; k < floors[i].size(); k++) {
                int currDist = (int)(dist(floors[i][j], floors[i][k])*100);
                if (currDist > 0 && currDist < minDistance) minDistance = currDist;
            }
        }
    }
    cout << minDistance << endl;
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
