//
//  main.cpp
//  punctuality
//
//  Created by Alec Schneider on 23.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <list>

#include <algorithm>


// Shortcuts for "common" data types in contests
typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;
typedef std::set<int> si;
typedef std::unordered_map<std::string, int> msi;

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


int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    
    #ifdef USE_INPUT_FILE
    freopen("input.txt", "r", stdin);
    #endif
    #ifdef USE_OUTPUT_FILE
    freopen("output.txt", "w", stdout);
    #endif
    
    // MAIN Begin
    int questionCount;
    int placeId = 0;
    cin >> questionCount;
    vector<vector<int>> matrix(4000, vector<int>(4000, INF));
    vector<vector<ii>> adj(4000);
    msi placeNameToId;
    int src = 0;
    placeNameToId["Gryffindor-Common-Room"] = placeId;
    placeId += 1;
    for (int q = 0; q < questionCount; q++)
    {
        string end;
        cin >> end;
        if (placeNameToId.find(end) == placeNameToId.end()) {
            placeNameToId[end] = placeId;
            placeId += 1;
        }
        int endId = placeNameToId[end];
        int updateCount;
        cin >> updateCount;
        for (int i = 0; i < updateCount; i++) {
            string from, to;
            int weight, fromId, toId;
            cin >> from >> to >> weight;
            if (placeNameToId.find(from) == placeNameToId.end()) {
                placeNameToId[from] = placeId;
                placeId += 1;
            }
            if (placeNameToId.find(to) == placeNameToId.end()) {
                placeNameToId[to] = placeId;
                placeId += 1;
            }
            fromId = placeNameToId[from];
            toId = placeNameToId[to];
            if (weight == 0) {
                for (auto pair = adj[fromId].begin(); pair < adj[fromId].end(); pair++)
                    if (pair->first == toId) pair->second = INF;
                for (auto pair = adj[toId].begin(); pair < adj[toId].end(); pair++)
                    if (pair->first == fromId) pair->second = INF;
            }//            matrix[fromId][toId] = weight;
//            matrix[toId][fromId] = weight;
            else {
                adj[fromId].push_back(make_pair(toId, weight));
                adj[toId].push_back(make_pair(fromId, weight));
            }
        }
        
        vi dist(placeId, INF);     // The output array.  dist[i] will hold the shortest
        // distance from src to i
        
        vector<bool> sptSet(placeId-1, false); // sptSet[i] will true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized
        
        // Distance of source vertex from itself is always 0
        dist[src] = 0;
        priority_queue< ii, vector <ii> , greater<ii> > pq;
        pq.push(make_pair(0, src));
        
        // Find shortest path for all vertices
        while (!pq.empty())
        {
            // Pick the minimum distance vertex from the set of vertices not
            // yet processed. u is always equal to src in first iteration.
            int u = pq.top().second;
            pq.pop();
            
            // Mark the picked vertex as processed
            
            
            for (int i = 0; i < adj[u].size(); i++)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = (adj[u][i]).first;
                int weight = (adj[u][i]).second;
                
                //  If there is shorted path to v through u.
                if (dist[v] > dist[u] + weight)
                {
                    // Updating distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        cout << dist[endId] << endl;
        src = endId;
    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
