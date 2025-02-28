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
constexpr ll MOD = 1000000007;
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    string s; cin >> s;
    ll n = s.size();
    ll k; cin >> k;
    ll qnum = 0;
    rep(i,0,n) if(s[i] == '?') qnum++;
    if(n*k == 0){
        cout << 0 << endl;
        return 0;
    }
    qnum *= k;
    mint x = powMod(2,qnum);
    mint div2 = mint(2).inv();
    mint ans = 0;
    rep(i,0,n-1){
        if(s[i] != '?' && s[i+1] != '?'){
            if(s[i] != s[i+1]) ans += x*k;
        }else{
            ans += x*k*div2;
        }
    }
    if(s[0] != '?' && s[n-1] != '?'){
        if(s[0] != s[n-1]) ans += x*(k-1);
    }else{
        ans += x*(k-1)*div2;
    }
    if(s[0] != '?' && s[n-1] != '?'){
        if(s[0] != s[n-1]) ans += x;
    }else{
        ans += x*div2;
    }
    cout << (ans/2).val() << endl;
    return 0;
}