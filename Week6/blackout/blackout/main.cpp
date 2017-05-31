//
//  main.cpp
//  blackout
//
//  Created by Alec Schneider on 30.05.17.
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
    vector<vector<ll>> dp;
    for (int c=0; c<cases; c++) {
        ll length, prices;
        cin >> length >> prices;
        vector<ll> dp(length+1, 0);
        vector<ll> priceTable(prices);
        vector<ll> lengthTable(prices);
        for (int i = 0; i < prices; i++) {
            ll l, p;
            cin >> l >> p;
            priceTable[i] = p;
            lengthTable[i] = l;
        }
        for (int i = 0; i < prices; i++) {
            ll price = priceTable[i];
            ll len = lengthTable[i];
            for (int j = 0; j <= length; j++) {
                if (j - len >= 0 && dp[j] < dp[j - len] + price) dp[j] = dp[j - len] + price;
                
            }
        }
        cout << dp[length] << endl;

    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
