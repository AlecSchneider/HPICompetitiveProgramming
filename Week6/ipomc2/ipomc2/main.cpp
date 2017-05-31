//
//  main.cpp
//  ipomc2
//
//  Created by Alec Schneider on 30.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <algorithm>


// Shortcuts for "common" data types in contests
typedef unsigned long long ll;
typedef std::vector<ll> vi;
typedef std::pair<ll, ll> ii;
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
#define INF 1000000000000 // 2 billion

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
    int nodeCount;
    cin >> nodeCount;
    vector<vector<ii>> adj(nodeCount);
    for (int e = 0; e < nodeCount-1; e++) {
        ll from, to, weight;
        cin >> from >> to >> weight;
        adj[from].push_back(make_pair(to, weight));
        adj[to].push_back(make_pair(from, weight));

    }
    vi dist(nodeCount, INF);
    // The output array.  dist[i] will hold the shortest
    // distance from src to i
    
    vector<bool> sptSet(nodeCount-1, false);
    // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    
    // Distance of source vertex from itself is always 0
    ll src = 0;
    dist[src] = 0;
    priority_queue< ii, vector <ii> , greater<ii> > pq;
    pq.push(make_pair(0, src));
    
    
    // Find shortest path for all vertices
    while (!pq.empty())
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in first iteration.
        ll u = pq.top().second;
        pq.pop();
        
        if (!sptSet[u]) {
            sptSet[u] = true;
            
            for (int i = 0; i < adj[u].size(); i++)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                ll v = (adj[u][i]).first;
                ll weight = (adj[u][i]).second;
                
                //  If there is shorted path to v through u.
                if (dist[v] > dist[u] + weight)
                {
                    // Updating distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }
    ll max = 0;
    ll start = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (dist[i] != INF && dist[i] > max) {
            max = dist[i];
            start = i;
        }
    }
    dist = vi(nodeCount, INF);     // The output array.  dist[i] will hold the shortest
    // distance from src to i
    
    sptSet = vector<bool>(nodeCount-1, false); // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    
    // Distance of source vertex from itself is always 0
    pq = priority_queue< ii, vector <ii> , greater<ii> >();
    src = start;
    dist[src] = 0;
    pq.push(make_pair(0, src));
    
    // Find shortest path for all vertices
    while (!pq.empty())
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in first iteration.
        ll u = pq.top().second;
        pq.pop();
        
        if (!sptSet[u]) {
            sptSet[u] = true;
            
            for (int i = 0; i < adj[u].size(); i++)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                ll v = (adj[u][i]).first;
                ll weight = (adj[u][i]).second;
                
                //  If there is shorted path to v through u.
                if (dist[v] > dist[u] + weight)
                {
                    // Updating distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }
    max = 0;
    ll end = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (dist[i] != INF && dist[i] > max) {
            max = dist[i];
            end = i;
        }
    }
    cout << max << endl;
    cout << start << endl;
    cout << end << endl;
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
