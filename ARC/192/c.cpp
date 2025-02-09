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
    ll n; cin >> n;
    vector<ll> flgs(n, 0);
    vector<vector<ll>> res(n, vector<ll>(n, -1));
    flgs[0] = 1;
    auto question = [&](ll i, ll j) -> ll {
        cout << "? " << i+1 << " " << j+1 << endl;
        ll x; cin >> x;
        return x;
    };
    rep(i,1,n){
        ll x = question(0, i);
        res[0][i] = x;
        res[i][0] = x;
    }
    rep(i,0,n){
        if(i == 1) continue;
        ll x = question(1, i);
        res[1][i] = x;
        res[i][1] = x;
    }
    rep(i,2,n){
        if(res[0][i] < res[1][i]) flgs[i] = 1;
    }
    vector<tuple<ll,ll,ll>> pos(n);
    rep(i,0,n){
        if(flgs[i] == 0) pos[i] = {1,res[0][i],i};
        else pos[i] = {0,-res[1][i],i};
    }
    sort(all(pos));
    vector<ll> p(n);
    rep(i,0,n) p[get<2>(pos[i])] = i;
    vector<ll> rev(n);
    rep(i,0,n) rev[p[i]] = i;
    vector<ll> a(n, -1);
    rep(i,1,n){
        if(p[0] < p[i]-1) a[p[i]] = res[0][i] - res[0][rev[p[i]-1]];
        if(p[0] > p[i]+1) a[p[i]] = res[0][i] - res[0][rev[p[i]+1]];
    }
    rep(i,0,n){
        if(i == 1) continue;
        if(p[1] < p[i]-1) a[p[i]] = res[1][i] - res[1][rev[p[i]-1]];
        if(p[1] > p[i]+1) a[p[i]] = res[1][i] - res[1][rev[p[i]+1]];
    }

    if(p[1]-p[0] == 1){
        if(p[0] == 0){
            a[0] = res[0][rev[2]] - res[1][rev[2]];
            a[1] = -(res[0][rev[2]] - res[0][1] - res[1][rev[2]]);
        }else{
            a[p[1]] = res[rev[p[0]-1]][1] - res[rev[p[0]-1]][0];
            a[p[0]] = -(res[rev[p[0]-1]][1] - res[0][1] - res[0][rev[p[0]-1]]);
        }
    }if(p[1]-p[0] == 2){
        a[p[0]+1] = res[0][1] - a[p[0]]-a[p[1]];
    }

    cout << "! ";
    rep(i,0,n) cout << p[i]+1 << " ";
    rep(i,0,n) cout << a[i] << " ";
    cout << endl;
    return 0;
}

