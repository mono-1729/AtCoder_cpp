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
    ll n, k;
    cin >> n >> k;
    string s; cin >> s;
    sort(s.begin(), s.end());
    unordered_map<string, ll> mp;
    auto check = [&](string& x) -> bool {
        rep(i, 0, x.size()/2){
            if(x[i] != x[x.size()-1-i]) return false;
        }
        return true;
    };
    ll ans = 0;
    do{
        if(mp[s] == 1) continue;
        mp[s] = 1;
        bool ok = true;
        rep(i,0,s.size()-k+1){
            string t = s.substr(i, k);
            if(check(t)){
                ok = false;
                break;
            }
        }
        if(ok) ans++;
    }while(next_permutation(s.begin(), s.end()));
    cout << ans << endl;
    return 0;
}