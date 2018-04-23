//
//  main.cpp
//  pokerchips
//
//  Created by Alec Schneider on 10.06.17.
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
        int n;
        cin >> n;
        vi stacksizes(n);
        vector<vector<int>> stacks(n);
        for (int s = 0; s < n; s++) {
            cin >> stacksizes[s];
        }
        for (int s = 0; s < n; s++) {
            for (int i = 0; i < stacksizes[s]; i++) {
                int chip;
                cin >> chip;
                stacks[s].push_back(chip);
            }
        }
        if (n == 2) {
            vector<vi> dp(stacksizes[0]+1, vi(stacksizes[1]+1));
            for (int i=0; i<=stacksizes[0]; i++)
            {
                for (int j=0; j<=stacksizes[1]; j++)
                {
                    if (i == 0 || j == 0)
                        dp[i][j] = 0;
                
                    else if (stacks[0][i-1] == stacks[1][j-1])
                        dp[i][j] = dp[i-1][j-1] + 1;
                
                    else
                        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
            cout << dp[stacksizes[0]][stacksizes[1]] << endl;
        }
        else cout << -1 << endl;
    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
