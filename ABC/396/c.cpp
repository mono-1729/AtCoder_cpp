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
    ll n, m; cin >> n >> m;
    priority_queue<ll> b, w;
    rep(i,0,n) {
        ll k; cin >> k;
        b.push(k);
    }
    rep(i,0,m) {
        ll k; cin >> k;
        w.push(k);
    }
    ll ans = 0;
    while(b.size() > 0){
        if(w.size() == 0){
            if(b.top() > 0){
                ans += b.top();
                b.pop();
            }else break;
        }
        else{
            if(w.top()>=0 && b.top() >= 0){
                ans += b.top();
                ans += w.top();
                b.pop();w.pop();
            }else if(b.top() >= 0){
                ans += b.top();
                b.pop();
            }else if(b.top()+w.top() >= 0){
                ans += b.top();
                ans += w.top();
                b.pop();w.pop();
            }else break;
        }
    }
    cout << ans << endl;
    return 0;
}