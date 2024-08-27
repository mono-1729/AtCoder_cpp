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
    ll t; cin >> t;
    while(t--){
        ll n, k; cin >> n >> k;
        vector<ll> a(n), b(n);
        rep(i, 0, n) cin >> a[i];
        rep(i, 0, n) cin >> b[i];
        if(k == 1){
            ll idx = 0;
            rep(i,0,n){
                while(idx < n && a[i] == b[idx]) idx++;
            }
            if(idx == n) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
        else{
            bool flg = true;
            rep(i,0,n)if(a[i] != b[i]) flg = false;
            if(flg){
                cout << "Yes" << endl;
                continue;
            }
            flg = true;
            unordered_set<ll> st;
            rep(i,0,n) st.insert(a[i]);
            rep(i,0,n) if(st.find(b[i]) == st.end()) flg = false;
            if(flg == false){
                cout << "No" << endl;
                continue;
            }
            flg = false;
            unordered_map<ll,ll> mp;
            rep(i,0,n){
                if(mp[b[i]] != 0 && i+1 - mp[b[i]] <= k) flg = true;
                mp[b[i]] = i+1;
            }
            if(flg) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}