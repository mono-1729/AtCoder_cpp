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

int main() {
    ll t_; cin >> t_;
    while(t_--){
        ll n; cin >> n;
        string s, t; cin >> s >> t;
        string sr = s, tr = t;
        if(count(all(s),'A') != count(all(t),'A')){
            cout << "No" << endl;
            continue;
        }
        ll l = 0, r = n;
        while(l < n && s[l] == t[l]) l++;
        while(r >= 0 && s[r] == t[r]) r--;
        if(l == n){
            cout << "Yes" << endl << 0 << endl;
            continue;
        }
        if(s[l] != 'A' || s[r] != 'B'){
            cout << "No" << endl;
            continue;
        }
        s = s.substr(l+1,r-l-1);
        t = t.substr(l+1,r-l-1);
        reverse(all(t));
        vector<pll> v1, v2;
        auto insert1 = [&](ll i, ll j) -> void {
            v1.push_back({l+1+i,l+1+j});
        };
        auto insert2 = [&](ll i, ll j) -> void {
            v2.push_back({r-1-j,r-1-i});
        };
        ll m = s.size();
        ll ca = count(all(s),'A'), cb = m-ca;
        vector<ll> p, q;
        if(ca <= cb){
            rep(i,0,m){
                if(s[i] == 'A') p.push_back(i);
                if(t[i] == 'A') q.push_back(i);
            }
            rrep(i,(ll)p.size()-1,0){
                if(p[i] < q[i]) insert1(p[i],q[i]);
                else if(p[i] > q[i]) insert2(q[i],p[i]);
            }
        }else{
            rep(i,0,m){
                if(s[i] == 'B') p.push_back(i);
                if(t[i] == 'B') q.push_back(i);
            }
            rep(i,0,(ll)p.size()){
                if(p[i] > q[i]) insert1(q[i],p[i]);
                else if(p[i] < q[i]) insert2(p[i],q[i]);
            }
        }
        vector<pll> ans;
        for(auto [i,j]: v1) ans.push_back({i+1,j+1});
        ans.push_back({l+1,r+1});
        reverse(all(v2));
        for(auto [i,j]: v2) ans.push_back({i+1,j+1});
        cout << "Yes" << endl;
        cout << ans.size() << endl;
        for(auto [i,j]: ans) cout << i << " " << j << endl;

    }
    return 0;
}