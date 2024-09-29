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
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> a(n), sum(n+1,0), a_(n);
    vector<pll> b(n);
    rep(i,0,n) cin >> a[i], b[i] = {a[i],i}, a_[i] = -a[i];
    sort(b.begin(), b.end(), greater<pll>());
    sort(a_.begin(), a_.end());
    rep(i,0,n) sum[i+1] = sum[i] + b[i].first;
    vector<ll> ans(n);
    rep(i,0,n){
        auto [val, idx] = b[i];
        if(i >= m && val+(k-sum[n]) < b[m-1].first){
            ans[idx] = -1;
            continue;
        }else if(n == m){
            ans[idx] = 0;
            continue;
        }
        if(i < m){
            ll l = -1, r = k-sum[n];
            while(r-l > 1){
                ll mid = (r+l)/2;
                ll s = val+mid;
                ll id = min(i,(ll)(lower_bound(a_.begin(), a_.end(), -s-1) - a_.begin()));
                ll t = (s+1) * (m-id) - (sum[m+1] - sum[id] - val);
                // cout << idx << " " << mid << " " << s << " " << t << " " << id << endl;
                if(k-sum[n] - mid < t) r = mid;
                else l = mid;
            }
            ans[idx] = r;
        }else{
            ll l = -1, r = k-sum[n];
            while(r-l > 1){
                ll mid = (r+l)/2;
                ll s = val+mid;
                ll id = min(m-1,(ll)(lower_bound(a_.begin(), a_.end(), -s-1) - a_.begin()));
                ll t = (s+1) * (m-id) - (sum[m] - sum[id]);
                if(k-sum[n] - mid < t) r = mid;
                else l = mid;
            }
            ans[idx] = r;
        }
    }
    for(auto x: ans) cout << x << " ";
    cout << endl;
    return 0;
}