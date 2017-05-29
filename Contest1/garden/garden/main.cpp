//
//  main.cpp
//  garden
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
        int nodeCount, start, end;
        cin >> start >> end >> nodeCount;
        vector<vector<int>> matrix(nodeCount, vector<int>(nodeCount, INF));
        
        vector<pair<int,vector<int>>> dist(nodeCount, make_pair(INF, vector<int>(0)));     // The output array.  dist[i] will hold the shortest
        // distance from src to i
        
        vector<bool> sptSet(nodeCount, false); // sptSet[i] will true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized
        
        // Distance of source vertex from itself is always 0
        int src = 0;
        dist[src].first = 0;
        
        // Find shortest path for all vertices
        for (int count = 0; count < nodeCount-1; count++)
        {
            // Pick the minimum distance vertex from the set of vertices not
            // yet processed. u is always equal to src in first iteration.
            int min = INF, u = 0;
            
            for (int v = 0; v < nodeCount; v++)
                if (sptSet[v] == false && dist[v].first <= min)
                    min = dist[v].first, u = v;
            
            // Mark the picked vertex as processed
            sptSet[u] = true;
            
            // Update dist value of the adjacent vertices of the picked vertex.
            for (int v = 0; v < nodeCount; v++) {
                // Update dist[v] only if is not in sptSet, there is an edge from
                // u to v, and total weight of path from src to  v through u is
                // smaller than current value of dist[v]
                if (matrix[u][v] > 0) {
                    cout << "q " << u << " " << v << endl;
                    cin >> matrix[u][v];
                }
                
                if (matrix[u][v] > 0 && !sptSet[v] && matrix[u][v] && dist[u].first != INF && dist[u].first+matrix[u][v] < dist[v].first) {
                    dist[v].first = dist[u].first + matrix[u][v];
                    dist[v].second = dist[u].second;
                    dist[v].second.push_back(u);
                }
            }
        }
        cout << "p ";
        for (int i = 0; i < dist[end].second.size()-1; i++) {
            cout << dist[end].second[i] << " ";
        }
        cout << dist[end].second[dist[end].second.size()-1];
        cout << endl;
    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
