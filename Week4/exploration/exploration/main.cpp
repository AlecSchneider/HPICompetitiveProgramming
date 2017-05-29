//
//  main.cpp
//  exploration
//
//  Created by Alec Schneider on 13.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <list>



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

bool operator<(const ii& a, const ii& b) {
    return a.first > b.first;
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
    cin >> cases; // read n
    for (int c=0; c<cases; c++) {
        int nodeCount, edgeCount;
        cin >> nodeCount >> edgeCount;
        vector<vector<int>> adj(nodeCount);
        vector<int> incoming(nodeCount, 0);
        vi visited(nodeCount, 0);
        for (int e = 0; e < edgeCount; e++) {
            int from, to;
            cin >> from >> to;
            incoming[to] += 1;
            adj[from].push_back(to);
        }
        for (int j = 0; j < nodeCount; j ++) {
            int i = 0;
            while (visited[i] == 1 || incoming[i] > 0) i +=1;
            cout << i << endl;
            visited[i] = 1;
            for (auto edge: adj[i]) {
                if (visited[edge] == 0)
                    incoming[edge] -= 1;
            }
            
        }
        //        cin >> in;
        //        cout << out << endl; // write result on stdout
    }

    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
