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

int main() {
    ll n; cin >> n;
    vector<pll> vec(n), plus;
    ll all = 0, ans = 0;
    rep(i,0,n){
        pll p = {1,0};
        if(i > 0){
            char c; cin >> c;
            if(c == '-') p.first = -1;
        }
        cin >> p.second;
        all += p.second;
        if(p.first == 1) ans += p.second;
        else ans -= p.second;
        vec[i] = p;
    }
    {
        ll i = 0;
        while(i < n){
            if(vec[i].first == -1){
                i++;
                continue;
            }
            ll r = i, sum = 0;
            while(r < n && vec[r].first == 1){
                sum += vec[r].second;
                r++;
            }
            plus.push_back({i,sum});
            i = r;
        }
        plus.push_back({n,0});
    }
    ll minus = 0;
    rep(i,0,n){
        if(vec[i].first == 1) continue;
        if(i > 0 && vec[i-1].first == -1){
            minus += vec[i].second;
            continue;
        }
        auto [id, x] = *lower_bound(all(plus),make_pair(i,0));
        minus += vec[i].second;
        if(i < n-1 && vec[i+1].first == -1) chmax(ans,all-minus*2);
        else chmax(ans,all-x*2-minus*2);
        // cout << i << " " << ans << endl;
    }
    cout << ans << endl;

    return 0;
}