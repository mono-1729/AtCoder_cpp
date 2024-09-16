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

// 0ならば素数, 0でないなら最⼩の素因数
// 素因数分解や素因数の数も求めることが可能
ll max_num=200005;
vector<ll> erat(max_num);
void init_e(){
    rep(i, 2, sqrt(double(max_num)-1)){
        if(erat[i] == 0){
            for(ll j = i*i; j <= max_num-1; j += i){
                if(erat[j] == 0) erat[j] = i;
            }
        }
    }
}
vector<pll> primes(ll num){
    vector<pll> res;
    while(erat[num] != 0){
        if(res.empty() || res.back().first != erat[num]) res.push_back({erat[num],1});
        else res.back().second++;
        num /= erat[num];
    }
    if(res.empty() || res.back().first != num) res.push_back({num,1});
    else res.back().second++;

    return res;
};

// 2元の場合
// 負の数にも対応した mod 
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
//pll res = chineseRem({2, 3}, {3, 5});
//cout << "x ≡ " << res.first << " (mod. "  << res.second << ")" << endl;

ll pw (ll i, ll j){
    ll res = 1;
    rep(k,0,j) res *= i;
    return res;
}

int main() {
    init_e();
    ll n; cin >> n;
    vector<ll> x(n), a(n);
    rep(i,0,n) cin >> x[i], x[i]--;
    rep(i,0,n) cin >> a[i];
    vector<ll> ans(n), check(n);
    vector<ll> q(n+1), modnum(n+1);
    rep(i,0,n){
        if(check[i]) continue;
        vector<ll> nums;
        ll now = i;
        while(true){
            check[now] = 1;
            nums.push_back(now);
            if(x[now] == i) break;
            now = x[now];
        }
        ll m = nums.size();
        auto pqs = primes(m);
        ll g, r;
        {
            vector<ll> nr, nm;
            for(auto [s,t] : pqs){
                ll pq = pw(s,min(t,q[s]));
                nr.push_back(modnum[s] % pq);
                nm.push_back(pq);
            }
            tie(r,g) = chineseRem(nr,nm);
        }
        ll best = r;
        rep(j,0,m)if(j%g == r){
            if(a[nums[j]] < a[nums[best]]) best = j;
        }
        rep(j,0,m) ans[nums[j]] = a[nums[(best+j)%m]];

        for(auto [s,t] : pqs){
            if(q[s] >= t) continue;
            ll pq = pw(s,t);
            q[s] = t;
            modnum[s] = best%pq;
        }
    }
    for(auto tmp: ans) cout << tmp << " ";
    cout << endl;
    return 0;
}