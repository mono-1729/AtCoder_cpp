#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

// 0ならば素数, 0でないなら最⼩の素因数
// 素因数分解や素因数の数も求めることが可能
ll max_num=200005;
vector<ll> erat(max_num);
void init_e(){
    rep(i, 2, sqrt((double)max_num-1)){
        if(erat[i] == 0){
            for(ll j = i*i; j <= max_num-1; j += i){
                if(erat[j] == 0) erat[j] = i;
            }
        }
    }
}

int main() {
    init_e();
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<mint> invp(n+1);
    rep(i,1,n+1) invp[i] = 1/(mint)i;
    vector<vector<ll>> yaku(n+1);
    rep(i,1,n+1){
        yaku[i].push_back(i);
        for(ll j = i*2; j <= n; j += i){
            invp[j] -= invp[i];
            yaku[j].push_back(i);
        }
    }
    vector<mint> sum(n+1);
    {
        for(auto x: yaku[a[0]]) sum[x] += invp[x]*a[0];
    }
    rep(i,1,n){
        mint ans = 0;
        for(auto x: yaku[a[i]]) ans += sum[x]*a[i];
        cout << ans.val() << endl;
        for(auto x: yaku[a[i]]) sum[x] += ans*invp[x]*a[i];
    }

    
    return 0;
}