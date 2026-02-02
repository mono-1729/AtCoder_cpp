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
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    string t = s;
    reverse(all(t));
    string ss = s+t;
    string ans = t;
    char mc = 'z';
    for(auto x: s) chmin(mc,x);
    if(k == 1){
        rep(i,0,n) chmin(ans,ss.substr(i,n));
        cout << ans << endl;
        return 0;
    }
    ll now = 0;
    while(now < n){
        if(s[now] != mc){
            now++;
            continue;
        }
        ll r = now+1;
        while(r < n && s[r] == mc) r++;
        if(r == n){
            ll cnt = r-now;
            rep(i,0,k){
                cnt *= 2;
                if(cnt >= n){
                    cnt = n;
                    break;
                }
            }
            string cand = "";
            rep(i,0,cnt) cand.push_back(mc);
            rrep(i,now-1,0) if(cand.size() < n) cand.push_back(s[i]);
            chmin(ans,cand);
        }else{
            ll cnt = r-now;
            rep(i,0,k-1){
                cnt *= 2;
                if(cnt >= n){
                    cnt = n;
                    break;
                }
            }
            string cand = "";
            rep(i,0,cnt) cand.push_back(mc);
            rep(i,r,n) if(cand.size() < n) cand.push_back(s[i]);
            rrep(i,n-1,0) if(cand.size() < n) cand.push_back(s[i]);
            chmin(ans,cand);
        }
        now = r;
    }
    cout << ans << endl;
    return 0;
}