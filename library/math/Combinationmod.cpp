#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;

/* Com：nCk % p の計算のための構造体
    前処理・初期化: O(p^2)
    nCk(n,k): nCk % p の計算。O(log n)
*/
struct Comb {
    vector<vector<long long>> com;  // 前計算の結果を保存
    long long p;                    // p は素数である必要がある
    Comb(long long _p) : p(_p) {
        init(p);
    }
    void init(long long p) {  // 動的計画法で前処理
        com.assign(p, vector<long long>(p));
        com[0][0] = 1;
        for (int i = 1; i < p; i++) {
            com[i][0] = 1;
            for (int j = i; j > 0; j--) {
                com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % p;
            }
        }
    }
    long long nCk(long long n, long long k) {
        long long ret = 1;
        while (n > 0) {  // 下から一桁ずつ計算する
            int ni = n % p;
            int ki = k % p;
            ret *= com[ni][ki];
            ret %= p;
            n /= p;
            k /= p;
        }
        return ret;
    }
};