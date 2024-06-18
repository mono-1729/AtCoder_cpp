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
    ll h,w,k;cin>>h>>w>>k;
    ll sx,sy;cin>>sx>>sy;
    sx--;sy--;
    vector<vector<ll>> a(h, vector<ll>(w));
    rep(i,0,h){
        rep(j,0,w){
            cin>>a[i][j];
        }
    }
    vector<vector<vector<ll>>> dist(2501, vector<vector<ll>>(h, vector<ll>(w,-1)));
    vector<ll> dx = {0,1,0,-1}, dy = {1,0,-1,0};
    dist[0][sx][sy] = 0;
    rep(i,0,2500){
        rep(x,0,h){
            rep(y,0,w){
                if(dist[i][x][y] == -1) continue;
                rep(j,0,4){
                    ll nx = x + dx[j], ny = y + dy[j];
                    if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
                    dist[i+1][nx][ny] = max(dist[i+1][nx][ny], dist[i][x][y] + a[nx][ny]);
                }
            }
        }
    }

    
    ll ans = 0;
    rep(i,0,2501){
        rep(x,0,h){
            rep(y,0,w){
                if(dist[i][x][y] == -1 || i > k) continue;
                ll num = dist[i][x][y];
                ll turn = k - i;
                num += turn * a[x][y];
                chmax(ans, num);
            }
        }
    }
    cout<<ans<<endl;

    // rep(i,0,h){
    //     rep(j,0,w){
    //         cout<<dist[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    return 0;
}