//
//  main.cpp
//  sculpture
//
//  Created by Alec Schneider on 11.07.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>


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
        int nodeCount;
        cin >> nodeCount;
        vector<vi> adj(55);
        for (int e = 0; e < nodeCount; e++) {
            int from, to;
            cin >> from >> to;
            adj[from].push_back(to);
            adj[to].push_back(from);
        }
        unordered_map<int,int> edge_count;
        int src = 0;
        bool isPossible = true;
        for (int i = 0; i < 55; i++) {
            edge_count[i] = adj[i].size();
            if (adj[i].size() > 0) {
                src = i;
            }
            if (adj[i].size() % 2 != 0) {
                isPossible = false;
            }
        }
        cout << "Case #" << c + 1 << endl;
        if (!isPossible) {
            cout << "some trusses may be lost" << endl;
        }
        else {
            // Maintain a stack to keep vertices
            stack<int> curr_path;
            
            // vector to store final circuit
            vector<int> circuit;
            
            // start from any vertex
            curr_path.push(src);
            int curr_v = src; // Current vertex
            
            while (!curr_path.empty())
            {
                // If there's remaining edge
                if (edge_count[curr_v])
                {
                    // Push the vertex
                    curr_path.push(curr_v);
                    
                    // Find the next vertex using an edge
                    if (adj[curr_v].size() <= 0) {
                        cout << "some trusses may be lost" << endl;
                        break;
                    }
                    int next_v = adj[curr_v].back();
                    // and remove that edge
                    edge_count[curr_v]--;
                    adj[curr_v].pop_back();
                    edge_count[next_v]--;
                    adj[next_v].erase(std::find(adj[next_v].begin(),adj[next_v].end(),curr_v));
                    
                    // Move to next vertex
                    curr_v = next_v;
                }
                
                // back-track to find remaining circuit
                else
                {
                    circuit.push_back(curr_v);
                    
                    // Back-tracking
                    curr_v = curr_path.top();
                    curr_path.pop();
                }
            }
            
            // we've got the circuit, now print it in reverse
            for (int i=circuit.size()-1; i>=1; i--)
            {
                cout << circuit[i] << " " << circuit[i-1] << endl;
            }
        }
        cout << endl;

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
