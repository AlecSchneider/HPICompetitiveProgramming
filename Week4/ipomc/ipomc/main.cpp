//
//  main.cpp
//  ipomc
//
//  Created by Alec Schneider on 09.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <queue>



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
        priority_queue<ii> pq;
        int nodeCount, edgeCount;
        cin >> nodeCount >> edgeCount;
        vector<vector<ii>> adj(nodeCount);
        for (int e = 0; e < edgeCount; e++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            adj[from].push_back(make_pair(to, weight));
            adj[to].push_back(make_pair(from, weight));
        }
        
        // Create a vector for keys and initialize all
        // keys as infinite (INF)
        vector<int> key(nodeCount, 0);
        
        
        // To keep track of vertices included in MST
        vector<bool> inMST(nodeCount, false);
        
        int src = 0;
        int maxWeight = 0;
        // Insert source itself in priority queue and initialize
        // its key as 0.
        pq.push(make_pair(0, src));
        key[src] = 0;
        
        /* Looping till priority queue becomes empty */
        while (!pq.empty())
        {
            // The first vertex in pair is the minimum key
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted key (key must be first item
            // in pair)
            int u = pq.top().second;
            pq.pop();
            
            inMST[u] = true;  // Include vertex in MST
            
            for (auto i: adj[u])
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = i.first;
                int weight = i.second;
                
                //  If v is not in MST and weight of (u,v) is smaller
                // than current key of v
                if (inMST[v] == false && key[v] < weight)
                {
                    // Updating key of v
                    maxWeight -= key[v];
                    maxWeight += weight;
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                }
            }
        }
        cout << maxWeight << endl;
        
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
