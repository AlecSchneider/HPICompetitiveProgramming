//
//  main.cpp
//  electriccars
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
#define INF 2000000000 // 2 billion

// If you need to recall how to use memset:
#define MEMSET_INF 127 // about 2B
#define MEMSET_HALF_INF 63 // about 1B
//memset(dist, MEMSET_INF, sizeof dist); // useful to initialize shortest path distances
//memset(dp_memo, -1, sizeof dp_memo); // useful to initialize DP memoization table
//memset(arr, 0, sizeof arr); // useful to clear array of integers


#pragma mark - MAIN
using namespace std;

class CompareDist
{
public:
    bool operator()(ii n1,ii n2) {
        return n1.second > n2.second;
    }
};

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
        ll nodeCount, edgeCount, start, end;
        cin >> nodeCount >> edgeCount >> start >> end;
        vector<vector<ii>> edges(nodeCount);
        ll maxValue = 0;
        for (int e = 0; e < edgeCount; e++) {
            ll from, to, weight;
            cin >> from >> to >> weight;
            edges[from].push_back(make_pair(to, weight));
            edges[to].push_back(make_pair(from, weight));
        }
        priority_queue<ii,vector<ii>,CompareDist> toBeVisited;
        vector<bool> visited(nodeCount, false);
        toBeVisited.push(make_pair(start, 0));
        while(!visited[end]) {
            ii currentNode = toBeVisited.top();
            toBeVisited.pop();
            if (currentNode.second > maxValue) maxValue = currentNode.second;
            if (!visited[currentNode.first]) {
                visited[currentNode.first] = true;
                    while(!edges[currentNode.first].empty()) {
                        ii subNode = edges[currentNode.first].back();
                        edges[currentNode.first].pop_back();
                        toBeVisited.push(subNode);
                    }
                }
            }
        cout << maxValue << endl;
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
