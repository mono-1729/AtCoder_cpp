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
    string s; cin >> s;

    if(s.size() <= 3){
        ll n = stoll(s);
        rep(i,n,n*2){
            ll num1 = i, num2 = i+1;
            ll sum1 = 0, sum2 = 0;
            for(auto x: to_string(num1)) sum1 += x - '0';
            for(auto x: to_string(num2)) sum2 += x - '0';
            if(num1 % sum1 == 0 and num2 % sum2 == 0){
                cout << num1 << endl;
                return 0;
            }
        }
        cout << -1 << endl;
        return 0;
    }
    if(s[0] == '1' && s[1] == '0'){
        cout << "11";
        rep(i,2,s.size()) cout << '0';
        cout << endl;
    }else if(s[0] == '1'){
        cout << "2";
        rep(i,1,s.size()) cout << '0';
        cout << endl;
    }else if(s[0] == '2' && s[1] <= '5'){
        cout << "26";
        rep(i,2,s.size()) cout << '0';
        cout << endl;
    }else if(s[0] < '4' || (s[0] == '4' && s[1] < '4')){
        cout << "44";
        rep(i,2,s.size()) cout << '0';
        cout << endl;
    }else if(s[0] < '8'){
        cout << "8";
        rep(i,1,s.size()) cout << '0';
        cout << endl;
    }else{
        cout << "11";
        rep(i,1,s.size()) cout << '0';
        cout << endl;
    }
    return 0;
}