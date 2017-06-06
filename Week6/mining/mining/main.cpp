//
//  main.cpp
//  mining
//
//  Created by Alec Schneider on 06.06.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <queue>
#include <algorithm>


// Shortcuts for "common" data types in contests
typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<double, double> ii;
typedef std::vector<ii> vii;
typedef std::unordered_set<int> si;
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
void fastInput(int &number) //not thread safe
{
    register unsigned int c;
    number = 0;
    while((c = getchar_unlocked()) == ' ' || (c == '\n'));
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number *10 + c - 48;
    //cout << number << endl;
}

ii calcScore(int src, int parent, vector<ii>& values, vector<vector<int>>& adj) {
    if (adj[src].size() == 1 && adj[src].front() == parent) return values[src];
    ii uPair = values[src];
    for (int j = 0; j < adj[src].size(); j++) {
        if (adj[src][j] == parent) continue;
        ii pair = calcScore(adj[src][j], src, values, adj);
        uPair.first += pair.second;
        uPair.second += max(pair.first, pair.second);
    }
    return uPair;
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
    
    int cases;
    fastInput(cases); // read n
    for (int c=0; c<cases; c++) {
        int numberOfStarSystems;
        fastInput(numberOfStarSystems);
        vector<ii> values(numberOfStarSystems);
        for (int i = 0; i < numberOfStarSystems; i++) {
            int value;
            fastInput(value);
            values[i] = make_pair((double)value, (double)value/2);
        }
        vector<vector<int>> adj(numberOfStarSystems);
        for (int e = 0; e < numberOfStarSystems-1; e++) {
            int from, to;
            fastInput(from);
            fastInput(to);
            adj[from].push_back(to);
            adj[to].push_back(from);
        }
        int src = 0;
        ii out = calcScore(src, -1, values, adj);
        cout << max((int)out.first, (int)out.second) << endl;
    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
