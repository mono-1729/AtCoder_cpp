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
    if(n <= 5 || n%3 == 2){
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    vector<vector<ll>> vec6 = {{1,4},{2,3},{5}}, vec7 = {{1,6},{2,5},{3,4}}, vec9 = {{1,2,3,6},{4,8},{5,7}}, vec10 = {{1,2,3,4,5},{6,9},{7,8}};
    auto solve = [&](vector<vector<ll>> vec, ll num) -> void {
        while(num/6 != 1){
            vec[0].push_back(n-6);
            vec[0].push_back(n-1);
            vec[1].push_back(n-5);
            vec[1].push_back(n-2);
            vec[2].push_back(n-4);
            vec[2].push_back(n-3);
            num-=6;
        }
        vector<vector<char>> ans(n);
        vector<pair<ll,char>> pq;
        for(auto x: vec[0]) pq.push_back(make_pair(x,'R'));
        for(auto x: vec[1]) pq.push_back(make_pair(x,'B'));
        for(auto x: vec[2]) pq.push_back(make_pair(x,'W'));
        sort(pq.begin(), pq.end());
        rep(i,0,n-1){
            rep(j,0,i+1){
                ans[j].push_back(pq[i].second);
            }
        }
        rep(i,0,n-1){
            for(auto x:ans[i]) cout << x;
            cout << endl;
        }
    };
    if(n%6 == 0) solve(vec6,n);
    if(n%6 == 1) solve(vec7,n);
    if(n%6 == 3) solve(vec9,n);
    if(n%6 == 4) solve(vec10,n);
    return 0;
}