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
    ll m = powMod(3, n);
    string s; cin >> s;
    vector<pll> vec(m);
    rep(i,0,m){
        vec[i] = {s[i] == '0' ? 0 : 1, 1};
    }
    rep(i,0,n){
        vector<pll> nvec;
        for(ll j = 0; j < powMod(3, n-i); j += 3){
            ll cnt = (vec[j].first + vec[j+1].first + vec[j+2].first);
            ll nf = cnt/2;
            ll ns = 0;
            vector<ll> tmp;
            if(vec[j].first == nf) tmp.push_back(vec[j].second);
            if(vec[j+1].first == nf) tmp.push_back(vec[j+1].second);
            if(vec[j+2].first == nf) tmp.push_back(vec[j+2].second);
            sort(tmp.begin(), tmp.end());
            if(cnt == 3 || cnt == 0){
                ns = tmp[0]+tmp[1];
            }else ns = tmp[0];
            nvec.push_back({nf, ns});
        }
        swap(vec, nvec);
    }
    cout << vec[0].second << endl;
    return 0;
}