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
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<ll> a(n), b(n);
        rep(i,0,n) cin >> a[i];
        rep(i,0,n) cin >> b[i];
        vector<ll> a1, b1;
        {
            ll ca = 0, cb = 0, a0 = 0, b0 = 0;
            rep(i,0,n){
                if(a[i] == 0) a0++;
                else ca += a0;
                if(b[i] == 0) b0++;
                else cb += b0;
            }
            if(ca != cb || a0 != b0){
                cout << "No" << endl;
                continue;
            }else cout << "Yes" << endl;
            if(a0+a0 < n){
                rep(i,0,n){
                    a[i] = 1-a[i];
                    b[i] = 1-b[i];
                }
            }
            rep(i,0,n){
                if(a[i]) a1.push_back(i);
                if(b[i]) b1.push_back(i);
            }
        }
        ll m = a1.size();
        set<ll> rst, lst;
        vector<tuple<ll,ll,ll,ll>> ans;
        rep(i,0,m){
            if(a1[i] < b1[i]) rst.insert(i);
            else if(a1[i] > b1[i]) lst.insert(i);
        }
        while(!rst.empty()){
            ll r = *rst.rbegin(), l = *lst.begin();
            ll len = min(b1[r]-a1[r], a1[l]-b1[l]);
            ans.push_back({a1[l]-len, a1[l], a1[r], a1[r]+len});
            // cout << l << " " << r << " " << len << " " << a1[l] << " " << a1[r] << endl;
            a1[l] -= len;
            a1[r] += len;
            // cout << l << " " << r << " " << len << " " << a1[l] << " " << a1[r] << endl;
            if(b1[r] == a1[r]) rst.erase(r);
            if(a1[l] == b1[l]) lst.erase(l);
        }
        cout << ans.size() << endl;
        for(auto [x, y, z, w]: ans) {
            if(x < z) cout << x+1 << " " << y+1 << " " << z+1 << " " << w+1 << endl;
            else cout << z+1 << " " << w+1 << " " << x+1 << " " << y+1 << endl;
        }
    }
    return 0;
}