//
//  main.cpp
//  blackholes
//
//  Created by Alec Schneider on 27.08.17.
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
#define INF 20000000 // 2 billion

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
        double min = INF;
        double max = -INF;
        for (int i = 0; i< 3; i++) {
            double n, y, z;
            cin >> n >> y >> z;
            if (n < min) min = n;
            if (n > max) max = n;
        }
        cout << "Case #"+to_string(c+1)+": " + to_string((max - min)/6) << endl;
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
