#define ll long long
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
int main(){
    ll left=-1,right=1000000000000000000;
    while (abs(right - left) > 1){
        ll mid = (right + left) / 2 ;
        bool flg=false;

        if (flg) left = mid;
        else right = mid;
    }
}