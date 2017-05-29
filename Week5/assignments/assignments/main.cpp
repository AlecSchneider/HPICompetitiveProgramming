//
//  main.cpp
//  assignments
//
//  Created by Alec Schneider on 22.05.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <climits>
#include <math.h>


// Shortcuts for "common" data types in contests
typedef unsigned long long ll;
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
        
        unsigned long long d = 0;
        unsigned long long prevD = 0;
        for (int i = 8; i > 0; i--) {
            unsigned long long test = ULONG_MAX/(pow(2,i*8-1));
            cout << "a " << test << endl;
            char response;
            cin >> response;
            if (response == 't') {
                d = test;
                break;
            }
            else d = ULONG_MAX;
            prevD = test;
        }
        ll  lower = prevD;
        ll upper = d;
        while (lower <= upper) {
            ll test = lower + (upper-lower)/2;
            cout << "a " << test << endl;
            char response;
            cin >> response;
            if (response == 't') {
                upper = test - 1;
            }
            else {
                lower = test + 1;
            }
        }
        cout << "i " << lower << endl;

    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}




































