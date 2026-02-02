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

int main() {
    ll n; cin >> n;
    unordered_map<ll,ll> cnt;
    vector<vector<ll>> c(n,vector<ll>(4));
    vector<ll> dim(5,1);
    rep(i,0,4) dim[i+1] = dim[i]*1000LL;
    auto f = [&](vector<ll> vec) -> pll {
        ll res = 0;
        ll mi = INF;
        rep(j,0,4){
            ll num = 0;
            rep(k,0,4) num += dim[k]*vec[(j+k)%4];
            chmin(mi,num);
        }
        rep(j,0,4){
            ll num = 0;
            rep(k,0,4) num += dim[k]*vec[(j+k)%4];
            if(mi == num) res++;
        }
        return {mi,res};
    };
    rep(i,0,n){
        rep(j,0,4) cin >> c[i][j];
        auto [mi,x] = f(c[i]);
        cnt[mi] += x;
    }
    ll ans = 0;
    vector<ll> vec1(4), vec2(4);
    rep(i,0,n){
        auto [mii, xi] = f(c[i]);
        cnt[mii] -= xi;
        rep(l,0,4) vec1[l] = c[i][l];
        rep(j,i+1,n){
            auto [mij, xj] = f(c[j]);
            cnt[mij] -= xj;
            rep(k,0,4){
                rep(l,0,4) vec2[l] = c[j][(k-l+4)%4];
                ll comb = 1;
                rep(l,0,4){
                    vector<ll> v = {vec2[l], vec2[(l+1)%4], vec1[(l+1)%4], vec1[l]};
                    auto [mil, xl] = f(v);
                    comb *= cnt[mil];
                    cnt[mil] -= xl;
                }
                ans += comb;
                rep(l,0,4){
                    vector<ll> v = {vec2[l], vec2[(l+1)%4], vec1[(l+1)%4], vec1[l]};
                    auto [mil, xl] = f(v);
                    cnt[mil] += xl;
                }
            }
            cnt[mij] += xj;
        }
    }
    cout << ans << endl;
    return 0;
}