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
    if (n == 0) return 1;
    ll val = powMod(x, n / 2);
    val *= val;
    if (n % 2 == 1) val *= x;
    return val;
}

int main() {
    ll n; cin >> n;
    string s; cin >> s;
    string t; cin >> t;
    s+="..";
    t+="..";
    unordered_map<string, ll> mp;
    mp[s] = 1;
    queue<string> q;
    q.push(s);
    while(!q.empty()){
        string now = q.front();
        q.pop();
        if(now == t){
            cout << mp[now]-1 << endl;
            return 0;
        }
        vector<int> dotidx;
        vector<int> sidx;
        rep(i,0,n+2){
            if(now[i] == '.')  dotidx.push_back(i);
            else sidx.push_back(i);
        }
        rep(i,0,sidx.size()-1){
            if(sidx[i]+1 != sidx[i+1]) continue;
            string next = now;
            swap(next[sidx[i]], next[dotidx[0]]);
            swap(next[sidx[i+1]], next[dotidx[1]]);
            if(mp[next] == 0){
                mp[next] = mp[now]+1;
                q.push(next);
            }
        }
    }
    cout << -1 << endl;
    return 0;
}