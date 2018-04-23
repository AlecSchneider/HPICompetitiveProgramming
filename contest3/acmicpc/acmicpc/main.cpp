//
//  main.cpp
//  acmicpc
//
//  Created by Alec Schneider on 01.08.17.
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


int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    
#ifdef USE_INPUT_FILE
    freopen("input.txt", "r", stdin);
#endif
#ifdef USE_OUTPUT_FILE
    freopen("output.txt", "w", stdout);
#endif
    
    // MAIN Begin
    
    int nodeCount, edgeCount;
    cin >> nodeCount >> edgeCount;
    vector<vector<ii>> adj(nodeCount);
    for (int e = 0; e < edgeCount; e++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adj[from].push_back(make_pair(to, weight));
    }
    while (1) {
        int src = 0;
        int end = nodeCount - 1;
        vector<vector<ii>> edges(nodeCount);
        edges = adj;
        queue<int> toBeVisited;
        vector<bool> visited(nodeCount);
        toBeVisited.push(src);
        vector<ii> parent(nodeCount);
        parent[src] = make_pair(src, 0);
        bool flag = false;
        while(!toBeVisited.empty()) {
            int currentNode = toBeVisited.front();
            toBeVisited.pop();
            if (!visited[currentNode]) {
                visited[currentNode] = true;
                while(!edges[currentNode].empty()) {
                    ii subNode = edges[currentNode].back();
                    edges[currentNode].pop_back();
                    if (!visited[subNode.first]) {
                        parent[subNode.first] = make_pair(currentNode, subNode.second);
                        toBeVisited.push(subNode.first);
                    }
                    if (subNode.first == end) {
                        flag = true;
                        break;
                    }
                }
            }
            if (flag) break;
        }
        if (!flag) break;
        else {
            pair<pair<int, int>, int> cut = make_pair(make_pair(0, 0), INF);
            while (end != 0) {
                ii pair = parent[end];
                if (pair.second < cut.second)
                {
                    cut = make_pair(make_pair(pair.first, end), pair.second);
                }
                end = pair.first;
            }
            cout << cut.first.first << " " << cut.first.second << endl;
            int from = cut.first.first;
            int to = cut.first.second;
            int weight = cut.second;
            adj[from].erase(remove(adj[from].begin(), adj[from].end(), make_pair(to, weight)), adj[from].end());
        }
    }
    //        cin >> in;
    //        cout << out << endl; // write result on stdout
    
    // MAIN End
    
#ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
#endif
    
    return 0;
}
