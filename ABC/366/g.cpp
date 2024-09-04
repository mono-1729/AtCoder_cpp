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

class xor_set{
private:
    vector<ll> w;
public:
    xor_set () {}
    void insert(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return;
        for(ll& v : w) if(x & -x & v) v ^= x;
        w.push_back(x);
    }
    // 独立か判定
    ll count(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return 1;
        else return 0;
    }
    vector<ll> get(){return w;}

    void sweep(){
        rep(i,0,w.size())rep(j,0,w.size()){
            if(i == j) continue;
            chmin(w[j], w[j] ^ w[i]);
        }
        sort(w.begin(), w.end(), greater<ll>());
    }
};

int main() {
    ll n, m; cin >> n >> m;
    vector<vector<ll>> edge(n,vector<ll>(n,0));
    rep(i,0,m){
        ll u, v; cin >> u >> v;
        u--;v--;
        edge[u][v] = 1;
        edge[v][u] = 1;
    }
    xor_set xset;
    rep(i,0,n){
        ll num = 0;
        rep(j,0,n) if(edge[i][j]) num ^= 1LL << j;
        xset.insert(num);
    }
    xset.sweep();
    vector<ll> ans(n,-1);
    ll now = 1;
    for(auto x: xset.get()){
        ll pcnt = __popcount(x);
        if(pcnt == 1){
            cout << "No" << endl;
            return 0;
        }
        ll num = 0, cnt = 0;
        rep(bit,0,60){
            if((x >> bit & 1) == 0) continue;
            cnt++;
            if(ans[bit] == -1){
                if(cnt == pcnt) ans[bit] = num;
                else ans[bit] = (1LL << bit);
            }
            num ^= ans[bit];
        }
    }
    cout << "Yes" << endl;
    for(auto x: ans) cout << (x == -1 ? 1: x) << " ";
    cout << endl;
    return 0;
}