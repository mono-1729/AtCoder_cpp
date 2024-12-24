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
    ll h, w, k; cin >> h >> w >> k;
    ll p, q; cin >> p >> q;
    p--; q--;
    vector<vector<ll>> s(h, vector<ll>(w));
    rep(i,0,h)rep(j,0,w) cin >> s[i][j];
    ll now = s[p][q];
    vector<vector<ll>> check(h, vector<ll>(w, 0));
    check[p][q] = 1;
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;
    vector<ll> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
    rep(i,0,4){
        ll nx = p + dx[i], ny = q + dy[i];
        if(0 <= nx && nx < h && 0 <= ny && ny < w){
            pq.push({s[nx][ny], nx, ny});
            check[nx][ny] = 1;
        }
    }
    while(!pq.empty()){
        auto [val, x, y] = pq.top(); pq.pop();
        if((int128_t)val*k < now){
            now += s[x][y];
            rep(i,0,4){
                ll nx = x + dx[i], ny = y + dy[i];
                if(0 <= nx && nx < h && 0 <= ny && ny < w && !check[nx][ny]){
                    pq.push({s[nx][ny], nx, ny});
                    check[nx][ny] = 1;
                }
            }
        }
        else{
            break;
        }
    }
    cout << now << endl;
    return 0;
}