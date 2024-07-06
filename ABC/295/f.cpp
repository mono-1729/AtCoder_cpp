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
    int t; cin >> t;
    auto solve = [&](string str, ll right)-> ll {
        string rightstr = to_string(right);
        ll strnum = stoll(str);
        if(str.size() > rightstr.size()) return 0;
        ll f0 = str[0] == '0' ? 1 : 0;
        ll res = 0;
        rep(i,0,rightstr.size() - str.size() + 1){
            ll lnum = i == 0 ? 0 : stoll(rightstr.substr(0,i));
            ll cnum = stoll(rightstr.substr(i,str.size()));
            ll rnum = rightstr.size()-(i+str.size()) == 0 ? 0 : stoll(rightstr.substr(i+str.size(),rightstr.size()-(i+str.size())));
            // cout << lnum << " " << cnum << " " << rnum << " " << endl;
            if(cnum > strnum){
                res += max(0LL,lnum-f0+1) * (ll)pow(10,rightstr.size()-(i+str.size()));
            }else if(cnum == strnum){
                res += max(0LL,lnum-f0) * (ll)pow(10,rightstr.size()-(i+str.size()));
                if(lnum != 0 || f0 == 0) res += rnum+1;
            }else if(cnum < strnum){
                res += max(0LL,lnum-f0) * (ll)pow(10,rightstr.size()-(i+str.size()));
            }
        }
        return res;
    };
    while(t--){
        string s; cin >> s;
        ll l, r; cin >> l >> r;
        cout << solve(s,r)-solve(s,l-1) << endl;
        //cout << solve(s,r) << " " << solve(s,l-1) << endl;
    }
    return 0;
}