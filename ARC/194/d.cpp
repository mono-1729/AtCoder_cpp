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
constexpr ll MOD1 = 1000000007;
constexpr ll MOD2 = 998244353;
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

ll MOD = 998244353;

ll maxnum=200005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll n; cin >> n;
    n  = n+2;
    string s; cin >> s;
    s = '(' + s + ')'; 
    vector<ll> dh(n+1);
    rep(i,0,n+1) dh[i] = (rand()%998244352)+1;
    auto solve = [&](auto solve, ll l, ll r, ll d) -> tuple<mint,ll,ll> {
        mint res = 1;
        ll h1 = dh[d], h2 = dh[d];
        ll c1 = 1, c2 = 1;
        ll left = l+1, now = left, cnt = 0;
        ll sum = 0;
        unordered_map<ll,ll> mp;
        unordered_map<ll,mint> mp2;
        while(now < r){
            if(s[now] == '(') cnt++;
            else cnt--;
            if(cnt == 0){
                auto [pat, ch1, ch2] = solve(solve, left, now, d+1);
                c1 = c1*ch1%MOD1, c2 = c2*ch2%MOD2;
                mp[ch1*MOD1+ch2]++;
                mp2[ch1*MOD1+ch2] = pat;
                left = now+1, now = left;
                sum++;
                continue;
            }
            now++;
        }
        res *= fac[sum];
        h1 = (h1+c1)%MOD1, h2 = (h2+c2)%MOD2;
        for(auto [key, val]: mp){
            res *= finv[val];
            rep(i,0,val) res *= mp2[key];
        }
        return {res, h1, h2};
    };

    cout << get<0>(solve(solve, 0, n, 0)).val() << endl;
    return 0;
}