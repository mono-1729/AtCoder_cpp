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
    ll h, w; cin >> h >> w;
    vector<vector<ll>> s(h, vector<ll>(w));
    rep(i,0,h){
        string t; cin >> t;
        rep(j,0,w) s[i][j] = t[j] == '#' ? 1 : 0;
    }
    vector<vector<ll>> ng(h);
    rep(i,0,h) ng[i].push_back(w);
    rep(i,1,h)rrep(j,w-1,1){
        ll cnt = s[i][j]+s[i-1][j]+s[i][j-1]+s[i-1][j-1];
        if(cnt%2 == 1) ng[i].push_back(j);
    }
    ll ans = 0;
    rep(j,0,w){
        vector<ll> left(h,0), right(h,0); 
        {
            stack<pll> st;
            st.push({j,-1});
            rep(i,0,h){
                while(st.top().first >= ng[i].back()) st.pop();
                left[i] = st.top().second;
                st.push({ng[i].back(),i-1});
            }
        }
        {
            stack<pll> st;
            st.push({j,h});
            rrep(i,h-1,0){
                while(st.top().first >= ng[i].back()) st.pop();
                right[i] = st.top().second;
                st.push({ng[i].back(),i});
            }
        }
        rep(i,0,h) chmax(ans,(ng[i].back()-j)*(right[i]-left[i]-1));
        rep(i,0,h) if(ng[i].back() == j+1) ng[i].pop_back();
    }
    cout << ans << endl;
    return 0;
} 