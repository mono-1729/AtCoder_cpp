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
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    priority_queue<ll> pqa, pqb;
    rep(i,0,n) cin >> a[i], pqa.push(a[i]);
    rep(i,0,n) cin >> b[i], pqb.push(b[i]);
    ll ans = 0;
    while(!pqa.empty()){
        ll maxa = pqa.top();
        ll maxb = pqb.top();
        if(maxa == maxb){
            pqa.pop();
            pqb.pop();
        }else if(maxa > maxb){
            pqa.pop();
            pqa.push(maxa/2);
            ans++;
        }else{
            if(maxb%2 == 0){
                pqb.pop();
                pqb.push(maxb/2);
                ans++;
            }else{
                cout << -1 << endl;
                return 0;
            }
        }
    }
    cout << ans << endl;
    return 0;
}