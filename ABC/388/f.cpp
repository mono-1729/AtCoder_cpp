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
    ll n_, m, a, b; cin >> n_ >> m >> a >> b;
    n_--;
    vector<vector<ll>> masu(m+1);
    masu[0].push_back(0);
    vector<ll> l(m), r(m);
    rep(i,0,m) cin >> l[i] >> r[i], l[i]--, r[i]--;
    if(a == b){
        if(n_%a != 0){
            cout << "No" << endl;
            return 0;
        }else{
            rep(i,0,m){
                ll x = (l[i] / a) * a;
                if(x == l[i] || (l[i] <= x+a && x+a <= r[i])){
                    cout << "No" << endl;
                    return 0;
                }
            }
        }
        cout << "Yes" << endl;
        return 0;
    }
    rep(i,0,m){
        rep(j,1,21){
            ll num = l[i]-j;
            if(i > 0 && num <= r[i-1]) continue;
            if(num <= 0) continue;
            masu[i].push_back(num);
        }
        rep(j,1,21){
            ll num = r[i]+j;
            if(i < m-1 && num >= l[i+1]) continue;
            if(num >= n_) continue;
            masu[i+1].push_back(num);
        }
    }
    masu[m].push_back(n_);
    vector<ll> masu2;
    vector<ll> kukan;
    rep(i,0,m+1){
        sort(masu[i].begin(), masu[i].end());
        masu[i].erase(unique(masu[i].begin(), masu[i].end()), masu[i].end());
        for(auto x : masu[i]){
            // cout << x << " ";
            masu2.push_back(x);
            kukan.push_back(i);
        }
    }
    ll n = masu2.size();
    vector<ll> dp(n, 0);
    dp[0] = 1;
    rep(i,0,n){
        if(dp[i] == 0) continue;
        rep(j,1,21){
            if(i+j >= n) break;
            if(kukan[i] == kukan[i+j]){
                ll x = (masu2[i+j]-masu2[i]) / a;
                if(masu2[i] + x * b >= masu2[i+j]){
                    dp[i+j] = 1;
                }
            }else{
                if(a <= (masu2[i+j]-masu2[i]) && (masu2[i+j]-masu2[i]) <= b){
                    dp[i+j] = 1;
                }
            }
        }
    }
    if(dp[n-1]) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}