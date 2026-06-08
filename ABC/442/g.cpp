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
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll n, c; cin >> n >> c;
    vector<vector<pll>> wvk_(4);
    vector<ll> sum_(4);
    rep(i,0,n){
        ll w, v, k; cin >> w >> v >> k;
        wvk_[w].push_back({v,k});
        sum_[w] += k;
    }
    ll ans = 0;
    rep(i,0,4) sort(all(wvk_[i]));
    rep(n1,0,7)rep(n2,0,4)rep(n3,0,2){
        if(n1 > sum_[1] || n2 > sum_[2] || n3 > sum_[3]) continue;
        if(c < n1*1+n2*2+n3*3) continue;
        ll num = 0;
        ll cc = c;
        vector<vector<pll>> wvk = wvk_;
        vector<ll> sum = sum_;
        auto get = [&](ll idx) -> ll {
            if(sum[idx]*idx < 6) return -INF;
            ll res = 0;
            ll cnt = 0;
            rrep(i,wvk[idx].size()-1,0){
                auto [v,k] = wvk[idx][i];
                if(cnt+k*idx >= 6){
                    res += v*((6-cnt)/idx);
                    return res;
                }else res += v*k, cnt += idx*k;
            }
            return res;
        };
        auto erase = [&](ll idx, ll f = -1) -> ll {
            // cout << n1 << " " << n2 << " " << n3 << " " << idx << " " << f << " " << sum[idx] << endl;
            ll remb = 6/idx;
            if(f == 1 && wvk[idx].back().second <= remb) f = 0;
            if(f == 1){
                auto [v,k] = wvk[idx].back();
                ll cmi = min(cc,(k/remb)*6);
                ll kmi = cmi/idx;
                wvk[idx].back().second -= kmi;
                if(kmi == k) wvk[idx].pop_back();
                cc -= cmi;
                sum[idx] -= kmi;
                return kmi*v;
            }else{
                if(f == -1) remb = 1;
                ll res = 0;
                cc -= remb*idx;
                rep(i,0,remb){
                    res += wvk[idx].back().first;
                    wvk[idx].back().second--;
                    if(wvk[idx].back().second == 0) wvk[idx].pop_back();
                }
                sum[idx] -= remb;
                return res;
            }
        };
        vector<ll> val(4);
        rep(i,0,n1) num += erase(1);
        rep(i,0,n2) num += erase(2);
        rep(i,0,n3) num += erase(3);
        while(cc >= 6){
            ll f = 0;
            rep(i,1,4) val[i] = get(i), f |= (val[i] >= 0);
            if(!f) break;
            if(val[1] > val[2] && val[1] > val[3]) num += erase(1,1);
            else if(val[2] > val[3]) num += erase(2,1);
            else num += erase(3,1);
        }
        // cout << n1 << " " << n2 << " " << n3 << " " << num << endl;
        chmax(ans,num);
    }
    cout << ans << endl;
    return 0;
}