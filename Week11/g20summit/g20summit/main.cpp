//
//  main.cpp
//  g20summit
//
//  Created by Alec Schneider on 18.07.17.
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
        int width, height, crosses;
        cin >> width >> height >> crosses;
        vector<vi> grid(width+2, vi(height+2, 0));
        vii points(crosses);
        for (int i = 0; i < crosses; i++) {
            int x, y;
            cin >> x >> y;
            grid[x][y] = 1;
            points[i] = make_pair(x, y);
        }
        for (int x = 0; x < width; x++) {
            grid[x][0] = 2;
            grid[x][height] = 2;
        }
        for (int y = 0; y < height; y++) {
            grid[0][y] = 2;
            grid[width][y] = 2;
        }
        bool possible = true;
        while(!points.empty()) {
            ii point = points.back();
            points.pop_back();
            queue<ii> q;
            q.push(point);
            vector<vector<bool>> visited(width+2, vector<bool>(height+2, false));
            vector<vii> route(width+2, vii(height+2, make_pair(-1, -1)));
            while (!q.empty()) {
                possible = false;
                ii current = q.front();
                q.pop();
                int dX = current.first;
                int dY = current.second;
                if (visited[dX][dY]) continue;
                visited[dX][dY] = true;
                if (grid[dX-1][dY] == 2 || grid[dX+1][dY] == 2 || grid[dX][dY-1] == 2 || grid[dX][dY+1] == 2) {
                    possible = true;
                    while(current != point) {
                        dX = current.first;
                        dY = current.second;
                        grid[dX][dY] = 3;
                        current = route[dX][dY];
                    }
                    break;
                }
                if (grid[dX-1][dY] == 0 && !visited[dX-1][dY]) {
                    q.push(make_pair(dX-1, dY));
                    route[dX-1][dY] = make_pair(dX, dY);
                }
                if (grid[dX+1][dY] == 0 && !visited[dX+1][dY]) {
                    q.push(make_pair(dX+1, dY));
                    route[dX+1][dY] = make_pair(dX, dY);
                }
                if (grid[dX][dY-1] == 0 && !visited[dX][dY-1]) {
                    q.push(make_pair(dX, dY-1));
                    route[dX][dY-1] = make_pair(dX, dY);
                }
                if (grid[dX][dY+1] == 0 && !visited[dX][dY+1]) {
                    q.push(make_pair(dX, dY+1));
                    route[dX][dY+1] = make_pair(dX, dY);
                }
            }
            if (!possible) {
                grid[point.first][point.second] = 4;
                for (int x = 0; x < width; x++) {
                    for (int y = 0; y < height; y++) {
                        cerr << grid[x][y];
                    }
                    cerr << endl;
                }
                cerr << endl;
                break;
            }
        }
        if (possible) cout << "possible" << endl;
        else cout << "not possible" << endl;
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
