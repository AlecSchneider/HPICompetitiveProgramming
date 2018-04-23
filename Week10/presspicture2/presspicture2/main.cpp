//
//  main.cpp
//  presspicture2
//
//  Created by Alec Schneider on 11.07.17.
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
typedef std::vector<ll> vi;
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

ll merge(int arr[], int temp[], int left, int mid, int right)
{
    ll inv_count = 0;
    
    int i = left; /* i is index for left subarray*/
    int j = mid;  /* i is index for right subarray*/
    int k = left; /* i is index for resultant merged subarray*/
    while ((i <= mid - 1) && (j <= right))
    {
        if (arr[i] > arr[j])
            temp[k++] = arr[i++];
        else
        {
            temp[k++] = arr[j++];
            
            /* this is tricky -- see above explanation/
             diagram for merge()*/
            inv_count = inv_count + (mid - i);
        }
    }
    
    /* Copy the remaining elements of left subarray
     (if there are any) to temp*/
    while (i <= mid - 1)
        temp[k++] = arr[i++];
    
    /* Copy the remaining elements of right subarray
     (if there are any) to temp*/
    while (j <= right)
        temp[k++] = arr[j++];
    
    /*Copy back the merged elements to original array*/
    for (i=left; i <= right; i++)
        arr[i] = temp[i];
    
    return inv_count;
}

/* An auxiliary recursive function that sorts the input
 array and returns the number of inversions in the
 array. */
ll _mergeSort(int arr[], int temp[], int left, int right)
{
    int mid;
    ll inv_count = 0;
    if (right > left)
    {
        /* Divide the array into two parts and call
         _mergeSortAndCountInv() for each of the parts */
        mid = (right + left)/2;
        
        /* Inversion count will be sum of inversions in
         left-part, right-part and number of inversions
         in merging */
        inv_count  = _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid+1, right);
        
        /*Merge the two parts*/
        inv_count += merge(arr, temp, left, mid+1, right);
    }
    
    return inv_count;
}

/* This function sorts the input array and returns the
 number of inversions in the array */
ll countSwaps(int arr[], int n)
{
    int temp[n];
    return _mergeSort(arr, temp, 0, n - 1);
}

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
        int colors[n];
        for (int i = 0; i < n; i++) {
            int color;
            cin >> color;
            colors[i] = color;
        }
        cout << countSwaps(colors, n) << endl;
        //        cout << out << endl; // write result on stdout
    }
    
    // MAIN End
    
    #ifdef USE_OUTPUT_FILE
    freopen("diff.txt", "w", stdout);
    system("diff output.txt expected_output.txt");
    #endif
    
    return 0;
}
