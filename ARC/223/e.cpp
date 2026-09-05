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
    ll t_; cin >> t_;
    while(t_--){
        ll n, m; cin >> n >> m;
        vector<ll> a(n), b(m);
        rep(i,0,n){
            cin >> a[i];
            if(i%2) a[i] = 1-a[i];
        }
        rep(i,0,m){
            cin >> b[i]; 
            if(i%2) b[i] = 1-b[i];
        }
        vector<ll> va, vb;
        {
            ll now = 0;
            while(now < n){
                ll r = now+1;
                while(r < n && a[now] == a[r]) r++;
                va.push_back(r-now);
                now = r;
            }
            now = 0;
            while(now < m){
                ll r = now+1;
                while(r < m && b[now] == b[r]) r++;
                vb.push_back(r-now);
                now = r;
            }
        }
        if(n%2 != m%2 || a[0] != b[0] || va.size() != vb.size()){
            cout << "No" << endl;
            continue;
        }
        ll f = 1, l = va.size();
        vector<pll> v;
        auto judge = [&](){
            vector<ll> dp(3);
            dp[0] = 1;
            for(auto [p,q] : v){
                vector<ll> ndp(3);
                rep(i,0,3)rep(j,0,3){
                    if(p == 1 && i+j == 0) continue;
                    if(p+i+j <= q && (p+i+j)%2 == q%2) ndp[j] |= dp[i];
                }
                swap(dp,ndp);
            }
            if(dp[0] == 0) f = 0;
            v.clear();
        };
        rep(i,0,l){
            if(!f) break;
            if(va[i] > vb[i]){
                f = 0;
                break;
            }else if(va[i] == vb[i]){
                judge();
                continue;
            }else v.push_back({va[i],vb[i]});
        }
        judge();
        if(f) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}