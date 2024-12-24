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
    ll a, b, c, d, e; cin >> a >> b >> c >> d >> e;
    vector<string> strs;
    rep(i,1,1<<5){
        string s = "";
        if(i & 1) s += "A";
        if(i & 2) s += "B";
        if(i & 4) s += "C";
        if(i & 8) s += "D";
        if(i & 16) s += "E";
        strs.push_back(s);
    }
    rep(i,0,32)rep(j,0,30){
        ll sum1 = 0, sum2 = 0;
        for(char x: strs[j]){
            if(x == 'A') sum1 += a;
            if(x == 'B') sum1 += b;
            if(x == 'C') sum1 += c;
            if(x == 'D') sum1 += d;
            if(x == 'E') sum1 += e;
        }
        for(char x: strs[j+1]){
            if(x == 'A') sum2 += a;
            if(x == 'B') sum2 += b;
            if(x == 'C') sum2 += c;
            if(x == 'D') sum2 += d;
            if(x == 'E') sum2 += e;
        }
        if(sum1 < sum2) swap(strs[j], strs[j+1]);
        else if(sum1 == sum2 && strs[j] > strs[j+1]) swap(strs[j], strs[j+1]);


    }
    for(auto s : strs){
        cout << s << endl;
    }
    return 0;
}