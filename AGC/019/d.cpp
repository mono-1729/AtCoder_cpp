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
    string a, b; cin >> a >> b;
    ll n = a.size();
    vector<ll> c;
    rep(i,0,n)if(b[i] == '1') c.push_back(i);
    ll ans = INF;
    if(c.size() == 0){
        ll f = 1;
        rep(j,0,n) f &= (a[j] == '0');
        if(f) cout << 0 << endl;
        else cout << -1 << endl;
        return 0;
    }
    vector<ll> l(n), r(n);
    rep(i,0,n){
        auto it = lower_bound(all(c),i);
        if(it == c.end()) it = c.begin();
        r[i] = i <= *it ? *it-i : *it+n-i;
        if(*it != i){
            if(it == c.begin()) it = prev(c.end());
            else it--;
        }
        l[i] = i >= *it ? i-*it : i+n-*it;
    }
    rep(i,0,n){
        priority_queue<pll> pq;
        ll cnt = 0;
        rep(j,0,n){
            if(a[j] != b[(i+j)%n]) pq.push({l[j], r[j]}), cnt++;
        }
        ll rmax = 0;
        if(pq.empty()){
            chmin(ans, min(i, n-i));
            continue;
        }
        {
            ll lmax = pq.empty() ? 0 : pq.top().first;
            chmin(ans,cnt+rmax+lmax+min(rmax+abs(lmax-(n-i)), lmax+abs(rmax-i)));
        }
        while(!pq.empty()){
            auto [x, y] = pq.top();pq.pop();
            chmax(rmax, y);
            ll lmax = pq.empty() ? 0 : pq.top().first;
            chmin(ans,cnt+rmax+lmax+min(rmax+abs(lmax-(n-i)), lmax+abs(rmax-i)));
            // cout << i << " " << lmax << " " << rmax << " " << x << " " << y << endl;
        }
    }
    cout << ans << endl;
    return 0;
}