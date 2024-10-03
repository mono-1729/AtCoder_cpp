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

using mint1 = modint1000000007;
using mint2 = modint998244353;

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
    ll m1 = 998244353, m2 = 1000000007;
    vector<mint1> pow1(200005,1);
    vector<mint2> pow2(200005,1);
    rep(i,1,200005){
        pow1[i] = pow1[i-1] * 27;
        pow2[i] = pow2[i-1] * 27;
    }
    auto RollingHash = [&](string str) -> pair<mint1, mint2> {
        mint1 hash1 = 0; mint2 hash2 = 0;
        rrep(i,str.size()-1,0){
            hash1 *= 27, hash2 *= 27;
            hash1 += (str[i]-'a'+1);
            hash2 += (str[i]-'a'+1);
        }
        return {hash1, hash2};
    };
    unordered_map<ll,pair<ll,ll>> mp;
    unordered_map<ll,ll> use;
    rep(i,0,n){
        string s; cin >> s;
        auto [hash1, hash2] = RollingHash(s);
        mint1 h1 = hash1; mint2 h2 = hash2;
        auto [c, h] = mp[h1.val()*m1+h2.val()];
        ll cnt = c == 0 ? 1 : c;
        if(c != 0) hash1 = h/m1, hash2 = h%m1;
        assert(c == 0 || use[hash1.val()*m1+hash2.val()] == 1);
        while(use[hash1.val()*m1+hash2.val()]){
            cnt++;
            hash1 = hash1*pow1[s.size()] + h1;
            hash2 = hash2*pow2[s.size()] + h2;
        }
        cout << cnt << " ";
        use[hash1.val()*m1+hash2.val()] = 1;
        mp[h1.val()*m1+h2.val()] = {cnt,hash1.val()*m1+hash2.val()};
    }
    return 0;
}