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
    ll t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        vector<vector<ll>> g(n);
        unordered_map<ll, ll> mp;
        rep(i, 0, m){
            ll a, b; cin >> a >> b;
            a--; b--;
            if(a > b) swap(a, b);
            mp[a*n+b]++;
        }
        if(n*n/4 < n*(n-1)/2 - m){
            cout << "No" << endl;
            continue;
        }
        rep(i, 0, n){
            rep(j, i+1, n){
                if(mp[i*n+j] == 0){
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        auto check = [&](){
            vector<ll> col(n, -1);
            rep(i, 0, n){
                if(col[i] != -1) continue;
                col[i] = 0;
                queue<ll> q;
                q.push(i);
                while(!q.empty()){
                    ll now = q.front(); q.pop();
                    for(auto next : g[now]){
                        if(col[next] == -1){
                            col[next] = col[now] ^ 1;
                            q.push(next);
                        }else if(col[next] == col[now]){
                            return false;
                        }
                    }
                }
            }
            return true;
        };
        if(check()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}