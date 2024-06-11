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
    ll n;cin>>n;
    vector<vector<char>> s(pow(3,n), vector<char>(pow(3,n), '#'));
    auto solve = [&](auto solve, ll x, ll y,ll z){
        if(z == 0) return;
        for(ll i = 0; i < (ll)pow(3,z); i+=pow(3,z-1)){
            for(ll j = 0; j < (ll)pow(3,z); j+=pow(3,z-1)){
                if(i == pow(3,z-1) && j == pow(3,z-1)){
                    rep(k,0,pow(3,z-1)){
                        rep(l,0,pow(3,z-1)){
                            s[x+i+k][y+i+l] = '.';
                        }
                    }
                }
                else{
                    solve(solve,x+i,y+j,z-1);
                }
                
            }
        }
    };
    solve(solve,0,0,n);
    rep(i,0,pow(3,n)){
        rep(j,0,pow(3,n)){
            cout << s[i][j];
        }
        cout << endl;
    }
    return 0;
}