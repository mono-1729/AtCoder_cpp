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
    ll n; cin >> n;
    vector<ll> a(n), b(n), c(n), d(n);
    rep(i,0,n) cin >> a[i] >> b[i];
    rep(i,0,n) cin >> c[i] >> d[i];
    vector<pll> vec0(n), vec1(n);
    vector<ll> ans(n), vec2(n), vec3(n);
    auto solve = [&](auto solve, vector<ll> p, vector<ll> q) -> void {
        // cout << "------------------" << endl;
        // for(auto x: p) cout << x << " ";
        // cout << endl;
        // for(auto x: q) cout << x << " ";
        // cout << endl;
        if(p.size() == 0) return;
        if(a[p[0]]*5001+b[p[0]] < c[q[0]]*5001+d[q[0]]){
            for(auto x: q){
                ll xd = c[x] - a[p[0]], yd = d[x] - b[p[0]];
                vector<ll> np1, nq1, np2, nq2;
                for(auto y: p){
                    if(p[0] == y) continue;
                    if(xd*(b[y]-b[p[0]]) - yd*(a[y]-a[p[0]]) > 0) np1.push_back(y);
                    else np2.push_back(y);
                }
                for(auto y: q){
                    if(x == y) continue;
                    if(xd*(d[y]-b[p[0]]) - yd*(c[y]-a[p[0]]) > 0) nq1.push_back(y);
                    else nq2.push_back(y);
                }
                if(np1.size() == nq1.size()) {
                    ans[p[0]] = x;
                    solve(solve,np1,nq1);
                    solve(solve,np2,nq2);
                    return;
                }
            }
        }else{
            for(auto x: p){
                ll xd = a[x] - c[q[0]], yd = b[x] - d[q[0]];
                vector<ll> np1, nq1, np2, nq2;
                for(auto y: p){
                    if(x == y) continue;
                    if(xd*(b[y]-d[q[0]]) - yd*(a[y]-c[q[0]]) > 0) np1.push_back(y);
                    else np2.push_back(y);
                }
                for(auto y: q){
                    if(q[0] == y) continue;
                    if(xd*(d[y]-d[q[0]]) - yd*(c[y]-c[q[0]]) > 0) nq1.push_back(y);
                    else nq2.push_back(y);
                }
                if(np1.size() == nq1.size()) {
                    ans[x] = q[0];
                    solve(solve,np1,nq1);
                    solve(solve,np2,nq2);
                    return;
                }
            }
        }
    };
    rep(i,0,n){
        vec0[i] = {a[i]*5001+b[i],i};
        vec1[i] = {c[i]*5001+d[i],i};
    }
    sort(vec0.begin(), vec0.end());
    sort(vec1.begin(), vec1.end());
    rep(i,0,n){
        vec2[i] = vec0[i].second;
        vec3[i] = vec1[i].second;
    }
    solve(solve, vec2, vec3);
    for(auto x: ans) cout << x+1 << " ";
    cout << endl;
    return 0;
}