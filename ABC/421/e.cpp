#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    cout << fixed << setprecision(15);
    vector<ll> a(6);
    rep(i,0,6) cin >> a[i]; 
    vector<map<vector<ll>,ld>> mp(4);
    vector<ll> vec(6);
    auto solve = [&](auto solve, ll turn, vector<ll> fix) -> ld {
        sort(all(fix));
        if(mp[turn].count(fix)) return mp[turn][fix];
        if(turn == 3){
            if(fix.size() != 5) return mp[turn][fix] = 0;
            ll now = 0, score = 0;
            while(now < 5){
                ll r = now+1;
                while(r < 5 && fix[now] == fix[r]) r++;
                chmax(score,(r-now)*fix[now]);
                now = r;
            }
            return mp[turn][fix] = score;
        }
        ll m = fix.size();
        ld res = 0;
        vector<ll> plus;
        auto dfs = [&](auto dfs) -> void {
            if(fix.size()+plus.size() == 5){
                ld score = 0;
                rep(bit,0,1<<(plus.size())){
                    rep(i,0,plus.size()){
                        if(bit>>i&1) fix.push_back(plus[i]);
                    }
                    chmax(score,solve(solve,turn+1,fix));
                    while(fix.size()>m) fix.pop_back();
                }
                res += score;
            }else{
                rep(i,0,6){
                    plus.push_back(a[i]);
                    dfs(dfs);
                    plus.pop_back();
                }
            }
        };
        dfs(dfs);
        rep(i,0,5-fix.size()) res /= 6;
        return mp[turn][fix] = res;
    };
    cout << solve(solve,0,{}) << endl;
    return 0;
}