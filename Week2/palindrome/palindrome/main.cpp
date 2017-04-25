//
//  main.cpp
//  palindrome
//
//  Created by Alec Schneider on 25.04.17.
//  Copyright © 2017 Alec Schneider. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

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
        string in;
        cin >> in;
        int max = -1;
        if (in.length()>1) {
            for (int i = 1; i < in.length(); i++) {
                for (int j = 0; j < in.length()-i; j++) {
                    int k = j;
                    int l = j+i;
                    bool isPalindrom = true;
                    while (k < l) {
                        if (in[k] == in[l]) {
                            k += 1;
                            l -= 1;
                        }
                        else {
                            isPalindrom = false;
                            break;
                        }
                    }
                    if (isPalindrom) {
                        max = i+1;
                        break;
                    }
                }
            }
        }
        
        cout << max << endl; // write result on stdout
    }

    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
