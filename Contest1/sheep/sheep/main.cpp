//
//  main.cpp
//  sheep
//
//  Created by Alec Schneider on 23.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>



// Shortcuts for "common" data types in contests
typedef long long ll;
typedef std::vector<ll> vi;
typedef std::pair<ll, ll> ii;
typedef std::vector<ii> vii;
typedef std::set<ll> si;
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
#define INF 200000000 // 2 billion

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
    
    int cases;
    cin >> cases; // read n
    for (int c=0; c<cases; c++) {
        
        int nodeCount, edgeCount;
        cin >> nodeCount >> edgeCount;
        vector<vector<ii>> adj(nodeCount);
        for (int e = 0; e < edgeCount; e++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            adj[from].push_back(make_pair(to, -1*weight));
        }
        vi dist(nodeCount, INF);
        
        // Step 1: Initialize distances from src to all other vertices
        // as INFINITE
        int src = 1; // TODO
        dist[src] = 0; // OUT
        
        // Step 2: Relax all edges |V| - 1 times. A simple shortest
        // path from src to any other vertex can have at-most |V| - 1
        // edges
        for (int i = 1; i <= nodeCount-1; i++)
        {
            for (int j = 0; j < nodeCount; j++)
            {
                for (auto edge: adj[j]) {
                    ll u = j;
                    ll v = edge.first;
                    ll weight = edge.second;
                    if (dist[u] != INF && dist[u] + weight < dist[v]) {
                        if ((dist[u] + weight) > 0) {
                            dist[v] = 0;
                        } else {
                            dist[v] = dist[u] + weight;
                        }
                    }
                }
            }
        }
        
        // Step 3: check for negative-weight cycles.  The above step
        // guarantees shortest distances if graph doesn't contain
        // negative weight cycle.  If we get a shorter path, then there
        // is a cycle.
        bool flag = false;
        for (int j = 0; j < nodeCount; j++)
        {
            for (auto edge: adj[j]) {
                ll u = j;
                ll v = edge.first;
                ll weight = edge.second;
                if (dist[u] != INF && dist[u] + weight < dist[v]) {
                    flag = true;
                }
            }
        }
        if (flag) cout << 0 << endl;
        else cout << 1 << endl;
    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
