//
//  main.cpp
//  gardenV2
//
//  Created by Alec Schneider on 11.06.17.
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
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#define read _read
#else
#include <unistd.h>
#endif

/// IMPORTANT: Call this at the beginning of main!
void init_binio() {
#ifdef _WIN32
    _setmode(0, _O_BINARY);
#endif
}

/// Helper function.
void fill_buf(uint32_t* buf, uint32_t count) {
    uint32_t remaining = count * 4;
    uint8_t* bbuf = (uint8_t*)buf;
    
    while (remaining > 0) {
        auto r = read(0, bbuf, remaining);
        if (r <= 0) {
            std::cerr << "Error reading input" << std::endl;
            exit(33);
        }
        remaining -= (uint32_t)r;
        bbuf += r;
    }
}

/// Read one unsigned 32bit integer from standard input.
uint32_t read_int() {
    uint32_t buf;
    fill_buf(&buf, 1);
    return buf;
}

/// Overwrite the contents of vec with `size` 32bit integers read from standard
/// input.
void read_vec(vector<uint32_t> &vec, uint32_t size) {
    vec.resize(size);
    fill_buf(vec.data(), size);
}

int main(int argc, const char * argv[]) {
    init_binio();
    std::ios::sync_with_stdio(false);
    
    #ifdef USE_INPUT_FILE
    freopen("input.txt", "r", stdin);
    #endif
    #ifdef USE_OUTPUT_FILE
    freopen("output.txt", "w", stdout);
    #endif
    
    // MAIN Begin
    
    uint32_t cases;
    cases = read_int(); // read n
    for (uint32_t c=0; c<cases; c++) {
        uint32_t nodeCount;
        nodeCount = read_int();
        uint32_t src = read_int();
        vector<vector<uint32_t>> mat(nodeCount);
        for (uint32_t j = 0; j < nodeCount; j++) {
            read_vec(mat[j], nodeCount);
        }
        vector<bool> visited(nodeCount, false);
        queue<uint32_t> toBeVisited;
        toBeVisited.push(src);
        vector<uint32_t> dist(nodeCount, INF);
        vector<uint32_t> hops(nodeCount, 0);
        dist[src] = 0;
        uint32_t maxIndex = src;
        uint32_t maxHops = 0;
        while (!toBeVisited.empty()) {
            uint32_t currentNode = toBeVisited.front();
            toBeVisited.pop();
                for (uint32_t i = 0; i < nodeCount; i++) {
                    if (dist[currentNode] + mat[currentNode][i] == mat[src][i] && hops[currentNode] >= hops[i] && currentNode != i) {
                        hops[i] = hops[currentNode] + 1;
                        dist[i] = mat[src][i];
                        toBeVisited.push(i);
                        if (hops[i] > maxHops) {
                            maxHops = hops[i];
                            maxIndex = i;
                        }
                    }
                }
            }
        cout << maxIndex << " " << maxHops << endl;
    }

    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
