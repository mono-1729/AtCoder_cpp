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
    ll n, l, t; cin >> n >> l >> t;
    vector<ll> pos;
    vector<ll> x(n), w(n);
    rep(i,0,n) cin >> x[i] >> w[i];
    ll idx = 0;
    if(w[0] == 1){
        ll p0 = x[0] + t;
        pos.push_back(p0%l);
        rep(i,1,n){
            if(w[i] == 1) pos.push_back((x[i]+t)%l);
            else{
                pos.push_back((x[i]-t + t * l)%l);
                idx += (p0 - x[i] + t + l)/l;
            }
        }
        idx %= n;
        sort(pos.begin(), pos.end());
        if(n == 1) cout << pos[0] << endl;
        else if(n == 2 && pos[0] == pos[1]) cout << pos[0] << endl << pos[1] << endl;
        else{
            vector<ll> ans(n);
            rep(i,0,n){
                if(pos[i] == p0%l && pos[(i+1)%n] != p0%l) {
                    rep(j,0,n) ans[(idx+j)%n] = pos[(i+j)%n];
                    rep(j,0,n) cout << ans[j] << endl;
                    break;
                }
            }
        }
    }else{
        ll p0 = x[0] - t;
        pos.push_back(((p0%l)+l)%l);
        rep(i,1,n){
            if(w[i] == 2) pos.push_back((x[i]-t + t * l)%l);
            else{
                pos.push_back((x[i]+t)%l);
                idx -= (x[i]+t - p0)/l;
            }
        }
        idx = (idx%n+n)%n;
        sort(pos.begin(), pos.end());
        if(n == 1) cout << pos[0] << endl;
        else if(n == 2 && pos[0] == pos[1]) cout << pos[0] << endl << pos[1] << endl;
        else{
            vector<ll> ans(n);
            rep(i,0,n){
                if(pos[i] == ((p0%l)+l)%l && pos[(i+n-1)%n] != ((p0%l)+l)%l) {
                    rep(j,0,n) ans[(idx+j)%n] = pos[(i+j)%n];
                    rep(j,0,n) cout << ans[j] << endl;
                    break;
                }
            }
        }
    }
    return 0;
}