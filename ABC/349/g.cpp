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
    ll n; cin >> n;
    vector<ll> a(n), s(n);
    rep(i,0,n) cin >> a[i], a[i]++;
    vector<vector<ll>> eq(n), neq(n); 
    auto no = [&]() {
        cout << "No" << endl;
        exit(0);
    };
    for(ll i = 0, w = 0; i < n;){
        while(0 <= i-w && i+w < n && a[i] > w){
            if(w) eq[i+w].push_back(i-w);
            w++;
        }
        if(0 <= i-w && i+w < n && w) neq[i+w].push_back(i-w);
        ll j = 1;
        while(j < w && a[i-j]+j < w){
            if(a[i+j] != a[i-j]) no();
            j++;
        }
        i += j; w -= j;
    }
    rep(i,0,n){
        if(eq[i].size() > 0){
            rep(j,1,eq[i].size()){
                if(s[eq[i][j]] != s[eq[i][0]]) no();
            }
            for(auto x: neq[i]){
                if(s[x] == s[eq[i][0]]) no();
            }
            s[i] = s[eq[i][0]];
        }else{
            vector<ll> vec;
            for(auto x: neq[i]){
                vec.push_back(s[x]);
            }
            sort(all(vec));
            vec.erase(unique(all(vec)), vec.end());
            ll now = 1;
            while(now <= vec.size() && vec[now-1] == now) now++;
            s[i] = now;
        }
    }

    cout << "Yes" << endl;
    for(auto x: s) cout << x << " ";
    cout << endl;
    return 0;
}