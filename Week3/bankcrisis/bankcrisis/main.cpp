//
//  main.cpp
//  bankcrisis
//
//  Created by Alec Schneider on 05.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

// Shortcuts for "common" data types in contests
typedef long long ll;
typedef std::vector<int> vi;
typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;
typedef std::set<unsigned int> si;
typedef std::map<std::string, unsigned int> msi;
typedef std::unordered_map<unsigned int, std::unordered_set<unsigned int>> dict;


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
    
    int relations;
    cin >> relations; // read n
    vector<vector<unsigned int>> edges(2000000);
    set<unsigned int> notVisited;
    for (int r=0; r<relations; r++) {
        int from;
        int to;
        cin >> from >> to;
        if (edges[from].empty()) notVisited.insert(from);
        if (edges[to].empty()) notVisited.insert(to);
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    
    while (!notVisited.empty()) {
        unsigned int node = *notVisited.begin();
        si out;
        out.insert(node);
        queue<unsigned int> toBeVisited;
        toBeVisited.push(node);
        notVisited.erase(node);
        while(!toBeVisited.empty()) {
            unsigned int currentNode = toBeVisited.front();
            toBeVisited.pop();
            while(!edges[currentNode].empty()) {
                unsigned int subNode = edges[currentNode].back();
                edges[currentNode].pop_back();
                if (notVisited.find(subNode) != notVisited.end()) {
                    notVisited.erase(subNode);
                    out.insert(subNode);
                    toBeVisited.push(subNode);
                }
            }
        }
        string x = "";
        const char *padding = "";
        for (auto iter = out.begin(); iter != out.end(); ++iter) {
            x = x + padding + to_string(*iter);
            padding = ", ";
        }
        cout << x << "\n";
        
    }
    // MAIN End
    
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
