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
    ll n, x; cin >> n >> x;
    x--;
    ll asum = 0, bsum = 0;
    vector<ll> a(n), b(n), p(n), q(n);
    vector<vector<ll>> reva(n), revb(n);
    rep(i,0,n) cin >> a[i], asum += a[i];
    rep(i,0,n) cin >> b[i], bsum += b[i];
    rep(i,0,n) cin >> p[i], p[i]--, reva[p[i]].push_back(i);
    rep(i,0,n) cin >> q[i], q[i]--, revb[q[i]].push_back(i);
    priority_queue<pll> pq;
    {
        ll num = a[x];
        queue<ll> que;
        que.push(x);
        vector<ll> check(n, 0);
        vector<ll> dist(n, 0);        
        check[x] = 1;
        while(!que.empty()){
            ll now = que.front();
            que.pop();
            for(auto next : reva[now]){
                if(check[next] == 0){
                    check[next] = 1;
                    dist[next] = dist[now] + 1;
                    pq.push({dist[next], next});
                    num += a[next];
                    que.push(next);
                }
            }
        }
        if(num != asum){
            cout << "-1" << endl;
            return 0;
        }
    }
    {
        ll num = b[x];
        queue<ll> que;
        que.push(x);
        vector<ll> check(n, 0);
        vector<ll> dist(n, 0);  
        check[x] = 1;
        while(!que.empty()){
            ll now = que.front();
            que.pop();
            for(auto next : reva[now]){
                if(check[next] == 0){
                    check[next] = 1;
                    dist[next] = dist[now] + 1;
                    pq.push({dist[next], next});
                    num += b[next];
                    que.push(next);
                }
            }
        }
        if(num != bsum){
            cout << "-1" << endl;
            return 0;
        }
    }
    vector<ll> check(n, 0);
    ll ans = 0;
    while(!pq.empty()){
        auto [dist, now] = pq.top();
        pq.pop();
        if(check[now] == 1) continue;
        check[now] = 1;
        ans++;
        a[p[now]] += a[now];
        b[q[now]] += b[now];
        a[now] = 0, b[now] = 0;
    }
    cout << 'a' << endl;
    if(asum != a[x] || bsum != b[x]){
        cout << "-1" << endl;
        return 0;
    }else cout << ans << endl;
    return 0;
}