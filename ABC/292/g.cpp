#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
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
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

bool done[41][41][41];
mint mem[41][41][41];

int main() {
    int n, m; cin >> n >> m;
    vector<string> s(n);
    rep(i,0,n) cin >> s[i];

    auto f = [&](auto f, int l, int r, int k) -> mint {
        if(l == r) return 1;
        if(k == m){
            if(r-l == 1) return 1;
            return 0;
        }
        if(done[l][r][k]) return mem[l][r][k];
        done[l][r][k] = true;

        vector<mint> dp(n+1);
        dp[l] = 1;
        rep(d,0,10){
            vector<mint> p(n+1); swap(dp,p);
            rep(i,l,r+1){
                rep(ni,i,r+1){
                    dp[ni] += p[i]*f(f,i,ni,k+1);
                    if(ni == r) break;
                    if(s[ni][k] != '?' && s[ni][k] != '0'+d) break;
                }
            }
        }
        return mem[l][r][k] = dp[r];
    };

    cout << f(f,0,n,0).val() << endl;
    return 0;
}