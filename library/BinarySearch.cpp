#define ll long long
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
bool is_ok(ll mid){
    return true;
}
ll binary_search(ll left, ll right){
    while (abs(right - left) > 1){
        ll mid = (right + left) / 2 ;
        if (is_ok(mid)) left = mid;
        else right = mid;
    }
    return left;
}