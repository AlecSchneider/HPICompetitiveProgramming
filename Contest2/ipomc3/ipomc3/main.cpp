//
//  main.cpp
//  ipomc3
//
//  Created by Alec Schneider on 20.06.17.
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
#define INF 10000000 // 2 billion

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
        int nodeCount;
        cin >> nodeCount;
        vector<vector<int>> matrix(nodeCount, vector<int>(nodeCount, INF));
        for (int e = 0; e < nodeCount-1; e++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            matrix[from][to] = weight;
            matrix[to][from] = weight;
        }
        
        int i, j, k;
        vector<vector<int>> dist(nodeCount, vector<int>(nodeCount));
        
        for (i = 0; i < nodeCount; i++)
            for (j = 0; j < nodeCount; j++)
                dist[i][j] = matrix[i][j];
        
        for (k = 0; k < nodeCount; k++)
        {
            // Pick all vertices as source one by one
            for (i = 0; i < nodeCount; i++)
            {
                // Pick all vertices as destination for the
                // above picked source
                for (j = 0; j < nodeCount; j++)
                {
                    // If vertex k is on the shortest path from
                    // i to j, then update the value of dist[i][j]
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
        
        int min = INF;
        vector<int> minset;
        for (i = 0; i < nodeCount; i++) {
            int distance = 0;
            for (j = 0; j < nodeCount; j++) {
                if (i != j && dist[i][j] != INF)
                    distance += dist[i][j];
            }
            if (distance == min) {
                minset.push_back(i);
            }
            else if (distance < min) {
                minset.clear();
                minset.push_back(i);
                min = distance;
            }
        }
        
        sort(minset.begin(), minset.end());
        cout << minset.size() << endl;
        for (int x = 0; x < minset.size(); x++) {
            cout << minset[x] << endl;
        }
        
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
