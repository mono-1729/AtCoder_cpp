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
    if (n <= 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

inline ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

inline long long mul(long long a, long long b, long long m) {
    a = mod(a, m); b = mod(b, m);
    if (b == 0) return 0;
    long long res = mul(mod(a + a, m), b>>1, m);
    if (b & 1) res = mod(res + a, m);
    return res;
}

// 拡張ユークリッドの互除法
// ap+bq=gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします。
ll extGCD(ll a, ll b, ll &p, ll &q){
    if (b == 0) {
        p = 1;
        q = 0;
        return a;
    }
    ll d = extGCD(b, a%b, q, p);
    q -= a/b*p;
    return d;
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x = r (mod. m)
// 解なしの場合は (0, -1) をリターン
pll chineseRem(const vector<ll> &b, const vector<ll> &m){
    ll r = 0, M = 1;
    rep(i, 0, (int)b.size()){
        ll p, q;
        ll d = extGCD(M, m[i], p, q); // p is inv of m1/d (mod. m[i]/d)
        if((b[i] - r) % d != 0) return {0, -1};
        ll tmp = mul(((b[i] - r) / d), p, (m[i] / d));
        r += M * tmp;
        M *= m[i] / d;
    }
    return {mod(r, M), M};
}

void solve(){
    ll k; cin >> k;
    string s; cin >> s;
    ll p = 0, q = 1;
    vector<ll> pow10(10,1);
    rep(i,1,10) pow10[i] = pow10[i-1]*10;
    for(auto x: s){
        p *= 10;
        q *= 10;
        p += x-'0';
        p %= k;
        q %= k;
    }
    if(p == 0){
        cout << s << endl;
        return;
    }
    string ans = s+"0000000000";
    ll f = 0;
    rep(i,0,10){
        if(i < 5){
            ll mi = INF, mj = -1;
            ll g = gcd(k,q);
            rep(j,0,pow10[i]){
                ll x = ((k-p-j)%k+k)%k;
                if(x%g != 0) continue;
                ll inv, tmp;
                extGCD(q/g, k/g, inv, tmp);
                inv = mod(inv, k/g);
                ll num = ((x/g)*inv)%(k/g);
                // cout << num << " " << j << " " << i << endl;
                if(num < mi){
                    mi = num;
                    mj = j;
                }
            }
            if(mj != -1){
                string t = mi == 0 ? "" : to_string(mi);
                t += s;
                string suf = mj == 0 ? "" : to_string(mj);
                rep(l,0,i-suf.size()) t += '0';
                t += suf;
                if(ans.size() > t.size() || (ans.size() == t.size() && ans > t)){
                    ans = t;
                    f = 1;
                }
            }
        }else{
            rep(j,0,pow10[9-i]){
                ll x = ((k-p-j*q)%k+k)%k;
                if(x < pow10[i]){
                    string t = j == 0 ? "" : to_string(j);
                    t += s;
                    string suf = to_string(x);
                    rep(l,0,i-suf.size()) t += '0';
                    t += suf;
                    if(ans.size() > t.size() || (ans.size() == t.size() && ans > t)){
                        ans = t;
                        f = 2;
                        break;
                    }
                }
            }
        }
        p *= 10;
        q *= 10;
        p %= k;
        q %= k;
    }
    if(f == 2){
        ll pp = 0;
        for(auto x: ans){
            pp *= 10;
            pp += x-'0';
            pp %= k;
        }
        assert(pp == 0);
    }
    cout << ans << endl;
}

int main(){
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}