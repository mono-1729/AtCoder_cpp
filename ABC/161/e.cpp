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
    ll n, k, c; cin >> n >> k >> c;
    string s; cin >> s;
    vector<ll> l(n+1,INF), r(n+1,-INF);
    {
        ll cnt = 0;
        l[0] = -INF;
        rep(i,0,n){
            if(s[i] == 'o' && i-l[cnt] > c){
                cnt++;
                l[cnt] = i;
            }
        }
    }
    {
        ll cnt = 0;
        r[0] = INF;
        rrep(i,n-1,0){
            if(s[i] == 'o' && r[cnt]-i > c){
                cnt++;
                r[cnt] = i;
            }
        }
    }  
    rep(i,0,n){
        if(s[i] == 'x') continue;
        ll lid = lower_bound(l.begin(), l.end(),i) - l.begin()-1;
        ll ok = false;
        // cout << i << " " << lid << endl;
        if(lid >= k || l[lid]+c < r[k-lid] && i < r[k-lid]){
            // cout << "type1 " << l[lid] << " " << r[k-lid] << endl;
            ok = true;
        }else if(lid > 0 && l[lid-1] + c < r[k-lid+1] && i < r[k-lid+1]){
            // cout << "type2 " << l[lid-1] << " " << r[k-lid+1] << endl;
            ok = true;
        }
        if(!ok) cout << i+1 << endl;
    } 
    return 0;
}