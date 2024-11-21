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
    vector<string> s(n);
    vector<ll> c(n);
    rep(i,0,n) cin >> s[i] >> c[i];
    vector<vector<ll>> dp(42, vector<ll>(n,INF));
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;
    pq.push({0,s[0].size(),0});
    auto is_palindrome = [&](ll i, ll l, ll r) -> bool {
        while(l < r){
            r--;
            if(s[i][l] != s[i][r]) return false;
            l++;
        }
        return true;
    };
    auto is_valid = [&](ll i1, ll l, ll i2, ll r) -> bool {
        while(l < s[i1].size() && r > 0){
            r--;
            if(s[i1][l] != s[i2][r]) return false;
            l++;
        }
        return true;
    };
    ll ans = INF;
    while(!pq.empty()){
        auto [cost, len, id] = pq.top(); pq.pop();
        if(cost > dp[len][id]) continue;
        if(len <= 20){
            rep(i,0,n){
                if(!is_valid(id, len, i, s[i].size())) continue;
                if(s[id].size()-len >= s[i].size()){
                    if(dp[len+s[i].size()][id] > cost+c[i]){
                        pq.push({cost+c[i], len+s[i].size(), id});
                        dp[len+s[i].size()][id] = cost+c[i];
                        if(is_palindrome(id,len+s[i].size(),s[id].size())) chmin(ans, cost+c[i]);
                    }
                }else{
                    if(dp[20+s[i].size()-(s[id].size()-len)][i] > cost+c[i]){
                        pq.push({cost+c[i], 20+s[i].size()-(s[id].size()-len), i});
                        dp[20+s[i].size()-(s[id].size()-len)][i] = cost+c[i];
                        if(is_palindrome(i,0,s[i].size()-(s[id].size()-len))) chmin(ans, cost+c[i]);
                    }
                }
            }
        }else{
            len -= 20;
            rep(i,0,n){
                if(!is_valid(i, 0, id, len)) continue;
                if(len >= s[i].size()){
                    if(dp[20+len-s[i].size()][id] > cost+c[i]){
                        pq.push({cost+c[i], 20+len-s[i].size(), id});
                        dp[20+len-s[i].size()][id] = cost+c[i];
                        if(is_palindrome(id,0,len-s[i].size())) chmin(ans, cost+c[i]);
                    }
                }else{
                    if(dp[len][i] > cost+c[i]){
                        pq.push({cost+c[i], len, i});
                        dp[len][i] = cost+c[i];
                        if(is_palindrome(i,len, s[i].size())) chmin(ans, cost+c[i]);
                    }
                }
            }
        }
    }
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}