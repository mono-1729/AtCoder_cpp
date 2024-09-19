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
    ll n, m; cin >> n >> m;
    ll sum = 0;
    unordered_map<ll,ll> mp;
    rep(i,0,n){
        ll a, b; cin >> a >> b;
        sum += a;
        mp[b-a]++;
    }
    vector<ll> dp(m+1, INF);
    dp[sum] = 0;
    rep(i,1, m+1){
        if(mp[-i] == 0) continue;
        rep(mod,0,i){
            ll idx = ((m-mod)/i)*i + mod;
            deque<pll> que;
            que.push_back({dp[idx], idx/i});
            for(int j = idx-i; j >= 0; j -= i){
                ll tmp = dp[j];
                chmin(dp[j], que.front().first + que.front().second - j/i);
                while(que.size() > 0 && que.back().first + que.back().second >= tmp + j/i) que.pop_back();
                que.push_back({tmp, j/i});
                if(que.front().second >= j/i + mp[-i]) que.pop_front(); 
            }
        }
    }
    rep(i,1, m+1){
        if(mp[i] == 0) continue;
        rep(mod,0,i){
            ll idx = mod;
            deque<pll> que;
            que.push_back({dp[idx], idx/i});
            for(int j = idx+i; j <= m; j += i){
                ll tmp = dp[j];
                chmin(dp[j], que.front().first + j/i - que.front().second);
                while(que.size() > 0 && que.back().first - que.back().second >= tmp - j/i) que.pop_back();
                que.push_back({tmp, j/i});
                if(que.front().second <= j/i - mp[i]) que.pop_front(); 
            }
        }
    }
    rep(i,0,m+1) cout << (dp[i] == INF ? -1 : dp[i]) << endl;
    return 0;
}