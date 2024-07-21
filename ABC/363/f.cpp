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
    ll n_; cin >> n_;
    unordered_map<ll,string> mp;
    vector<ll> rev(1e6+1);
    rep(i,1,1e6+1){
        string s = to_string(i);
        reverse(s.begin(),s.end());
        bool ok = true;
        rep(j,0,s.size()){
            if(s[j] == '0'){
                rev[i] = -1;
                ok = false;
                break;
            }
        }
        if(ok) rev[i] = stoll(s);
    }
    auto isrev = [&](ll n) -> bool{
        string s = to_string(n);
        for(auto c:s) if(c == '0') return false;
        string t = s;
        reverse(t.begin(),t.end());
        return s == t;
    };
    auto solve = [&](auto solve, ll n) -> string {
        if(mp[n] != "") return mp[n];
        if(isrev(n)) return mp[n] = to_string(n);
        rep(i,2,sqrt((double)n)+1){
            if(rev[i] == -1) continue;
            if(n%i == 0 && (n/i)%rev[i] == 0){
                string s = solve(solve,(n/i)/rev[i]);
                if(s != "-1") return mp[n] = to_string(i) + "*"+ s +"*"+ to_string(rev[i]);
            }
        }
        return mp[n] = "-1";
    };
    cout << solve(solve,n_) << endl;
    return 0;
}