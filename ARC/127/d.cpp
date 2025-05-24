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

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

int main() {
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    vector<pll> c(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i];
    rep(i,0,n) c[i] = {a[i]^b[i], i};
    ll ans = 0;
    auto solve = [&](auto solve, vector<pll> vec, ll digit) -> void {
        if(vec.size() == 0) return;
        if(digit == -1){
            // cout << "ans: " << ans << " "; 
            vector<vector<ll>> cnt(18,vector<ll>(2,0));
            for(auto p : vec){
                for(int i = 0; i < 18; i++){
                    ans += cnt[i][a[p.second] & (1LL << i) ? 0 : 1]*(1LL << i);
                    cnt[i][a[p.second] & (1LL << i) ? 1 : 0]++;
                }
            }
            // cout << ans << endl;
            return;
        }
        vector<pll> vec0, vec1;
        for(auto p : vec){
            if(p.first & (1LL << digit)) vec1.push_back(p);
            else vec0.push_back(p);
        }
        solve(solve, vec0, digit-1);
        solve(solve, vec1, digit-1);
        vector<vector<ll>> cnt00a(18,vector<ll>(2,0)), cnt01a(18,vector<ll>(2,0)), cnt10a(18,vector<ll>(2,0)), cnt11a(18,vector<ll>(2,0)), cnt00b(18,vector<ll>(2,0)), cnt01b(18,vector<ll>(2,0)), cnt10b(18,vector<ll>(2,0)), cnt11b(18,vector<ll>(2,0));
        for(auto p : vec0){
            if(a[p.second] & (1LL << digit)){
                rep(i,0,18){
                    cnt01a[i][a[p.second] & (1LL << i) ? 1: 0]++;
                    cnt01b[i][b[p.second] & (1LL << i) ? 1: 0]++;
                }
            }
            else{
                rep(i,0,18){
                    cnt00a[i][a[p.second] & (1LL << i) ? 1: 0]++;
                    cnt00b[i][b[p.second] & (1LL << i) ? 1: 0]++;
                }
            }
        }
        for(auto p : vec1){
            if(a[p.second] & (1LL << digit)){
                rep(i,0,18){
                    cnt11a[i][a[p.second] & (1LL << i) ? 1: 0]++;
                    cnt11b[i][b[p.second] & (1LL << i) ? 1: 0]++;
                }
            }
            else{
                rep(i,0,18){
                    cnt10a[i][a[p.second] & (1LL << i) ? 1: 0]++;
                    cnt10b[i][b[p.second] & (1LL << i) ? 1: 0]++;
                }
            }
        }
        rep(i,0,18){
            ans += (cnt00a[i][0]*cnt10a[i][1]+cnt00a[i][1]*cnt10a[i][0])*(1<<i);
            ans += (cnt01b[i][0]*cnt10b[i][1]+cnt01b[i][1]*cnt10b[i][0])*(1<<i);
            ans += (cnt00b[i][0]*cnt11b[i][1]+cnt00b[i][1]*cnt11b[i][0])*(1<<i);
            ans += (cnt01a[i][0]*cnt11a[i][1]+cnt01a[i][1]*cnt11a[i][0])*(1<<i);
        }
        return;
    };
    solve(solve, c, 17); 
    cout << ans << endl;
    return 0;
}