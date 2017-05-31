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
typedef unsigned long long ll;
typedef std::vector<ll> vi;
typedef std::pair<ll, ll> ii;
typedef std::vector<ii> vii;
typedef std::set<int> si;
typedef std::unordered_map<std::string, int> msi;
typedef std::unordered_map<int, int> mii;


// To simplify repetitions/loops, Note: define your loop style and stick with it!
#define REP(i, a, b) \
for (int i = int(a); i <= int(b); i++) // a to b, and variable i is local!
#define TRvi(c, it) \
for (vi::iterator it = (c).begin(); it != (c).end(); it++)
#define TRvii(c, it) \
for (vii::iterator it = (c).begin(); it != (c).end(); it++)
#define TRmsi(c, it) \
for (msi::iterator it = (c).begin(); it != (c).end(); it++)
#define INF 100000000000000 // 2 billion

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
    vector<vector<int>> matrix(4000, vector<int>(4000, 0));
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
            ll weight, fromId, toId;
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
            if (matrix[toId][fromId] == 1) {
                if (weight == 0) weight = INF;
                for (auto pair = adj[fromId].begin(); pair < adj[fromId].end(); pair++)
                    if (pair->first == toId) pair->second = weight;
                for (auto pair = adj[toId].begin(); pair < adj[toId].end(); pair++)
                    if (pair->first == fromId) pair->second = weight;
            }
            else {
                adj[fromId].push_back(make_pair(toId, weight));
                adj[toId].push_back(make_pair(fromId, weight));
                matrix[fromId][toId] = 1;
                matrix[toId][fromId] = 1;
            }
        }
        
        vi dist(placeId, INF);
        vi distEnd(placeId, INF);
        // The output array.  dist[i] will hold the shortest
        // distance from src to i
        
        vector<bool> sptSet(placeId-1, false);
        vector<bool> sptSetEnd(placeId-1, false);
        // sptSet[i] will true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized
        
        // Distance of source vertex from itself is always 0
        dist[src] = 0;
        distEnd[endId] = 0;
        priority_queue< ii, vector <ii> , greater<ii> > pq;
        pq.push(make_pair(0, src));
        priority_queue< ii, vector <ii> , greater<ii> > pqEnd;
        pqEnd.push(make_pair(0, endId));
        
        
        // Find shortest path for all vertices
        while (!pq.empty() && !pqEnd.empty())
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
            ll w = pqEnd.top().second;
            pqEnd.pop();
            
            if (!sptSetEnd[w]) {
            sptSetEnd[w] = true;
            for (int i = 0; i < adj[w].size(); i++)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                ll v = (adj[w][i]).first;
                ll weight = (adj[w][i]).second;
                
                //  If there is shorted path to v through u.
                if (distEnd[v] > distEnd[w] + weight)
                {
                    // Updating distance of v
                    distEnd[v] = distEnd[w] + weight;
                    pqEnd.push(make_pair(distEnd[v], v));
                }
            }
             }
            if ((sptSet[u] && sptSetEnd[u]) || (sptSet[w] && sptSetEnd[w])) break;
        }
        ll minDistance = INF;
        for (int i = 0; i < placeId; i++)
            if (sptSetEnd[i] || sptSet[i])
            if (dist[i] + distEnd[i] < minDistance) minDistance = dist[i] + distEnd[i];
        cout << minDistance << endl;
        src = endId;
            
    }
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
