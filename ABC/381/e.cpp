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
    ll n, q; cin >> n >> q;
    string s; cin >> s;
    vector<ll> num1(n+1), num2(n+1), numbar(n+1);
    rep(i,0,n){
        num1[i+1] = num1[i];
        num2[i+1] = num2[i];
        numbar[i+1] = numbar[i];
        if(s[i] == '1') num1[i+1]++;
        if(s[i] == '2') num2[i+1]++;
        if(s[i] == '/') numbar[i+1]++;
    }
    rep(i,0,q){
        ll l, r; cin >> l >> r;
        l--;
        ll ok = 0, ng = (r-1+2)/2;
        while(ng - ok > 1){
            ll mid = (ok + ng) / 2;
            ll flg = true;
            if(num1[r] < num1[l] + mid) flg = false;
            if(num2[r] < num2[l] + mid) flg = false;
            ll n1 = lower_bound(num1.begin(), num1.end(), num1[l] + mid) - num1.begin();
            ll n2 = upper_bound(num2.begin(), num2.end(), num2[r] - mid) - num2.begin();
            if(n1 >= n2) flg = false;
            if(numbar[n1] == numbar[n2]) flg = false;
            if(flg) ok = mid;
            else ng = mid;
        }
        if(numbar[l] == numbar[r]) cout << 0 << endl;
        else cout << ok*2+1 << endl;
    }
    return 0;
}