#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
// 0ならば素数, 0でないなら最⼩の素因数
// 素因数分解や素因数の数も求めることが可能
int max_num=1000005;
vector<int> phi(max_num);
void init_e(){
	rep(i,0,max_num) phi[i] = i;
    rep(i,2,max_num) {
        if(phi[i] == i) {
            for(int j = i; j < max_num; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

// 約数列挙も同時に行う

// int max_num=100005;
// vector<ll> phi(max_num);
// vector<vector<ll>> divs(max_num);

// void init_e(){
//     rep(i, 1, max_num){
//         for(ll j = i; j < max_num; j += i){
//             divs[j].push_back(i);
//         }
//     }
// 	rep(i,0,max_num) phi[i] = i;
//     rep(i,2,max_num) {
//         if(phi[i] == i) {
//             for(ll j = i; j < max_num; j += i) {
//                 phi[j] = phi[j] / i * (i - 1);
//             }
//         }
//     }
// }