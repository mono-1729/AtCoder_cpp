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

using S = struct{
    ll fsum;
    ll fid;
    ll ssum;
    ll sid;
};
S op(S x1, S x2) {
    vector<pll> v = {{x1.fsum, x1.fid}, {x1.ssum, x1.sid}, {x2.fsum, x2.fid}, {x2.ssum, x2.sid}};
    sort(v.begin(), v.end(), greater<pll>());
    return {v[0].first, v[0].second, v[1].first, v[1].second};
} 
S e() {return {0,0,0,0};}


int main() {
    ll n; cin >> n;
    vector<ll> c(n);
    rep(i,0,n) cin >> c[i];
    vector<S> v(n);
    rep(i,0,n) v[i] = {c[i], i, 0, 0};
    segtree<S, op, e> seg(v);
    vector<vector<ll>> ans;
    vector<ll> sum(n, 0);   
    while(true){
        bool flag = true;
        int x1 = -1;
        vector<ll> a(5);
        rep(i,0,5){
            S s = seg.all_prod();
            if(sum[s.fid] >= 3){
                if(s.ssum == 0){
                    flag = false;
                    break;
                }
                S t = seg.get(s.sid);
                seg.set(s.sid, {t.fsum-1, t.fid, t.ssum, t.sid});
                sum[s.sid] += 1;
                a[i] = s.sid+1;
            }
            else{
                if(s.fsum == 0){
                    flag = false;
                    break;
                }
                S t = seg.get(s.fid);
                seg.set(s.fid, {t.fsum-1, t.fid, t.ssum, t.sid});
                sum[s.fid] += 1;
                a[i] = s.fid+1;
                if(sum[s.fid] == 3) x1 = s.fid+1;
            }
        }
        if(flag){
            sort(a.begin(), a.end());
            if(x1 == -1){
                ans.push_back({a[0], a[3], a[1], a[4], a[2]});
            }else{
                vector<ll> b;
                rep(i,0,5){
                    if(a[i] != x1) b.push_back(a[i]);
                }
                ans.push_back({x1, b[0], x1, b[1], x1});
            }
            rep(i,0,5) sum[a[i]-1] -= 1;
        }else break;
    }
    cout << ans.size() << endl;
    rep(i,0,ans.size()){
        rep(j,0,5){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}