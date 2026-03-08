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
#define ll unsigned long long
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
    if(b == 0) return a;
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
    ll n; cin >> n;
    vector<ll> s(n), t(n), u(n), v(n);
    rep(i,0,n) cin >> s[i];
    rep(i,0,n) cin >> t[i];
    rep(i,0,n) cin >> u[i];
    rep(i,0,n) cin >> v[i];
    vector<vector<ll>> ans(n,vector<ll>(n,0));

    rep(bit,0,64){
        vector<vector<ll>> vec(n,vector<ll>(n,2));
        vector<ll> chr(n,1), chc(n,1);
        rep(i,0,n){
            if((!s[i] && (u[i]>>bit&1)) || (s[i] && !(u[i]>>bit&1))){
                rep(j,0,n) vec[i][j] = 1-s[i];
                chr[i] = 0;
            }
        }
        rep(j,0,n){
            if((!t[j] && (v[j]>>bit&1)) || (t[j] && !(v[j]>>bit&1))){
                rep(i,0,n) vec[i][j] = 1-t[j];
                chc[j] = 0;
            }
        }
        vector<ll> vr, vc;
        rep(i,0,n){
            if(chr[i]) vr.push_back(i);
            if(chc[i]) vc.push_back(i);
        }
        // if(bit == 0)for(auto x: vec){
        //     for(auto y: x) cout << y << " ";
        //     cout << endl;
        // }
        if((vr.size() >= 2 && vc.size() >= 2) || vr.size()*vc.size() == 0){
            rep(i,0,vr.size())rep(j,0,vc.size()){
                vec[vr[i]][vc[j]] = (i+j)%2;
            }
        }else if(vr.size() == 1){
            for(auto j: vc){
                ll f = 1;
                rep(i,0,n){
                    if((t[j] && vec[i][j] == 1) || (!t[j] && vec[i][j] == 0)) f = 0;
                }
                if(f) vec[vr[0]][j] = t[j];
            }
            // if(bit == 0)for(auto x: vec){
            //     for(auto y: x) cout << y << " ";
            //     cout << endl;
            // }
            for(auto j: vc){
                if(vec[vr[0]][j] == 2) vec[vr[0]][j] = s[vr[0]];
            }
        }else{
            for(auto i: vr){
                ll f = 1;
                rep(j,0,n){
                    if((s[i] && vec[i][j] == 1) || (!s[i] && vec[i][j] == 0)) f = 0;
                }
                if(f) vec[i][vc[0]] = s[i];
            }
            for(auto i: vr){
                if(vec[i][vc[0]] == 2) vec[i][vc[0]] = t[vc[0]];
            }
        }
        rep(i,0,n)rep(j,0,n) ans[i][j] += vec[i][j]<<bit;
    }

    auto check = [&]() -> ll {
        vector<ll> uu(n), vv(n);
        rep(i,0,n){
            if(s[i]) uu[i] = 0;
            else uu[i] = ULLONG_MAX;
            if(t[i]) vv[i] = 0;
            else vv[i] = ULLONG_MAX;
        }
        rep(i,0,n)rep(j,0,n){
            if(s[i]) uu[i] |= ans[i][j];
            else uu[i] &= ans[i][j];
            if(t[j]) vv[j] |= ans[i][j];
            else vv[j] &= ans[i][j];
        }
        rep(i,0,n){
            if(u[i] != uu[i]) return 0;
            if(v[i] != vv[i]) return 0;
        }
        return 1;
    };
    if(check()){
        for(auto vec: ans){
            for(auto x: vec) cout << x << " ";
            cout << endl;
        }
    }else cout << -1 << endl;
    return 0;
}