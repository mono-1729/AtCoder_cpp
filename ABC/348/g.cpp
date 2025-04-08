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

class BIT {
    public:
        ll n; // データの長さ
        vector<ll> a; // データの格納先
    
        BIT(ll n_): n(n_), a(n_+1, 0){} // コンストラクタ
    
        // a[i]をxに加算する
        void add(ll pos, ll x){
            pos++; // 1インデックスにしてる
            while(pos <= n){
                a[pos] += x;
                pos += pos&(-pos);
            }
        }
    
        // [0, i]を求める
        ll sum_sub(ll pos){
            pos++;
            ll res = 0;
            while(0 < pos){
                res += a[pos];
                pos -= pos&(-pos);
            }
            return res;
        }
    
        // [l, r)の和
        ll sum(ll l, ll r){
            r--;
            return sum_sub(r)-sum_sub(l-1);
        }
    
        // a[0]+a[1]+...+a[i-1] >= x となる最小のiを求める（任意のkでa[k]>=0が必要）
        ll lower_bound(ll x){
            if(x <= 0){
                return 0;
            }else{
                ll i = 0, len = 1;
                //最大としてありうる区間の長さを取得する
                //n以下の最小の二乗のべき(BITで管理する数列の区間で最大のもの)を求める
                while(len < n) len *= 2;
                //区間の長さは調べるごとに半分になる
                for(;len>0;len=len>>1) {
                    //その区間を採用する場合
                    if(i+len<n && a[i+len]<x){
                        x-=a[i+len];
                        i+=len;
                    }
                }
                return i+1;
            }
        }
};

struct P{
    ll a, b;
    P(ll a = 0,ll b = 0): a(a),b(b){}
    bool operator<(const auto& p) const {return b < p.b;};
};

int main() {
    ll n; cin >> n;
    vector<P> ab(n);
    vector<pll> avec(n);
    rep(i,0,n) cin >> ab[i].a >> ab[i].b;
    sort(all(ab));
    rep(i,0,n) avec[i] = {ab[i].a, i};
    sort(all(avec), greater<pll>());
    vector<ll> rev(n);
    rep(i,0,n) rev[avec[i].second] = i;
    vector<ll> ans(n+1);
    BIT cnt(n), sum(n);
    auto solve = [&](auto& solve, ll kl, ll kr, ll l, ll r) -> void {
        // cerr << kl << " " << kr << " " << l << " " << r << endl;
        if(kl == kr){
            rep(i,l,r){
                cnt.add(rev[i], 1);
                sum.add(rev[i], ab[i].a);
            }
            return;
        }
        ll mid = (kl+kr)/2;
        ll maxi = -INF, idx = -1;
        rep(i,l,r){
            cnt.add(rev[i], 1);
            sum.add(rev[i], ab[i].a);
            if(i+1 >= mid){
                ll rr = cnt.lower_bound(mid);
                ll num = sum.sum(0,rr)-ab[i].b;
                if(maxi < num){
                    maxi = num;
                    idx = i;
                }
            }
        }
        // cerr << mid << " " << maxi << " " << idx << endl;
        ans[mid] = maxi;
        rep(i,l,r){
            cnt.add(rev[i], -1);
            sum.add(rev[i], -ab[i].a);
        }
        solve(solve, kl, mid, l, idx+1);
        cnt.add(rev[idx], -1);
        sum.add(rev[idx], -ab[idx].a);
        solve(solve, mid+1, kr, idx, r);
    };
    solve(solve, 1, n+1, 0, n);
    rep(i,1,n+1) cout << ans[i] << endl;
    return 0;
}