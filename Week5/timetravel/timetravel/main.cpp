//
//  main.cpp
//  timetravel
//
//  Created by Alec Schneider on 22.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <climits>


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
#define INF LLONG_MAX/10 // 2 billion

// If you need to recall how to use memset:
#define MEMSET_INF 127 // about 2B
#define MEMSET_HALF_INF 63 // about 1B
//memset(dist, MEMSET_INF, sizeof dist); // useful to initialize shortest path distances
//memset(dp_memo, -1, sizeof dp_memo); // useful to initialize DP memoization table
//memset(arr, 0, sizeof arr); // useful to clear array of integers


#pragma mark - MAIN
using namespace std;


int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    
    #ifdef USE_INPUT_FILE
    freopen("input.txt", "r", stdin);
    #endif
    #ifdef USE_OUTPUT_FILE
    freopen("output.txt", "w", stdout);
    #endif
    
    // MAIN Begin
    
        ll nodeCount, edgeCount, distances;
        cin >> nodeCount >> edgeCount >> distances;
        vector<vector<ll>> matrix(nodeCount, vector<ll>(nodeCount, INF));
        for (int e = 0; e < edgeCount; e++) {
            ll from, to, weight;
            cin >> from >> to >> weight;
            matrix[from][to] = weight;
        }
        
        int i, j, k;
        vector<vector<ll>> dist(nodeCount, vector<ll>(nodeCount));
    
        for (i = 0; i < nodeCount; i++)
            for (j = 0; j < nodeCount; j++)
                dist[i][j] = matrix[i][j];
        
        for (k = 0; k < nodeCount; k++)
        {
            // Pick all vertices as source one by one
            for (i = 0; i < nodeCount; i++)
            {
                // Pick all vertices as destination for the
                // above picked source
                for (j = 0; j < nodeCount; j++)
                {
                    // If vertex k is on the shortest path from
                    // i to j, then update the value of dist[i][j]
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
        for (int d = 0; d < distances; d++) {
            cin >> i >> j;
            if (dist[i][j] >= INF) cout << "oo" << endl;
            else cout << dist[i][j] << endl;
        }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
