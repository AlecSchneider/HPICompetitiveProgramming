//
//  main.cpp
//  aliennetworking
//
//  Created by Alec Schneider on 20.06.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <queue>


// Shortcuts for "common" data types in contests
typedef long long ll;
typedef std::vector<ll> vi;
typedef std::pair<ll, double> ii;
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

void fastInput(int &number) //not thread safe
{
    register unsigned int c;
    number = 0;
    while((c = getchar_unlocked()) == ' ' || (c == '\n'));
    for (; (c>47 && c<58); c=getchar_unlocked())
    number = number *10 + c - 48;
//    cout << number << endl;
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
    fastInput(cases);
    for (int c=0; c<cases; c++) {
        int nodeCount, edgeCount;
        fastInput(nodeCount);
        fastInput(edgeCount);
        vector<vector<ii>> adj(nodeCount);
        vector<vector<ii>> adjInv(nodeCount);
        vi incoming(nodeCount, 0);
        vi visited(nodeCount, 0);
        for (int e = 0; e < edgeCount; e++) {
            int from, to, weight;
            fastInput(from);
            fastInput(to);
            cin >> weight;
            adj[from].push_back(make_pair(to, weight));
            adjInv[to].push_back(make_pair(from, weight));
            incoming[to] += 1;
        }
    
        vector<ll> topSort;
        for (int j = 0; j < nodeCount; j ++) {
            int i = 0;
            while (visited[i] == 1 || incoming[i] > 0) i +=1;
            topSort.push_back(i);
            visited[i] = 1;
            for (auto edge: adj[i]) {
                if (visited[edge.first] == 0)
                incoming[edge.first] -= 1;
            }
            
        }

        
        ll from = 0;
        ll to = 0;
        ll max = INF;
        vi dist(nodeCount, INF);
        ll src = topSort.back(); // TODO
        dist[src] = 0; // OUT
        for (int i = 1; i <= nodeCount-1; i++)
        {
            for (int j = 0; j < nodeCount; j++)
            {
                for (auto edge: adjInv[j]) {
                    ll u = j;
                    ll v = edge.first;
                    ll weight = edge.second;
                    if (dist[u] != INF && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        if (dist[v] < max) {
                            max = dist[v];
                            from = v;
                        }
                    }
                }
            }
        }

        dist = vi(nodeCount, INF);
        
        // Step 1: Initialize distances from src to all other vertices
        // as INFINITE
        max = INF;
        src = from; // TODO
        dist[src] = 0; // OUT
        for (int i = 1; i <= nodeCount-1; i++)
        {
            for (int j = 0; j < nodeCount; j++)
            {
                for (auto edge: adj[j]) {
                    ll u = j;
                    ll v = edge.first;
                    ll weight = edge.second;
                    if (dist[u] != INF && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        if (dist[v] < max) {
                            max = dist[v];
                            to = v;
                        }
                    }
                }
            }
        }
        
        cout << from << " " <<  to << " " << -1*max << endl; // write result on stdout
    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
