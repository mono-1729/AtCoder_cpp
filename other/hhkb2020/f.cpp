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
constexpr ll MOD = 1000000007;
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    ll n; cin >> n;
    vector<ll> l(n), r(n);
    vector<ll> vec(n*2);
    vector<mint> inv(n+10);
    rep(i,1,n+10) inv[i] = ((mint)i).inv();
    ll lmin = INF;
    rep(i,0,n){
        cin >> l[i] >> r[i];
        vec[i*2] = l[i];
        vec[i*2+1] = r[i];
        chmin(lmin,l[i]);
    }
    mint pirl = 1, nfac = 1;
    rep(i,1,n+2) nfac *= i;
    rep(i,0,n) pirl *= r[i]-l[i];
    sort(all(vec));
    vec.erase(unique(all(vec)),vec.end());
    mint ans = lmin*pirl;
    auto multiply = [&](const vector<mint>& a, const vector<mint>& b) -> vector<mint> {
        vector<mint> c(a.size() + b.size() - 1);
        rep(i,0,(ll)a.size()){
            rep(j,0,(ll)b.size()){
                c[i+j] += a[i] * b[j];
            }
        }
        return c;
    };
    auto calc = [&](ll left, ll right) -> void {
        // cout << (ans*nfac).val() << endl;
        ans += pirl*(right-left);

        queue<vector<mint>> q;
        rep(i,0,n){
            if(left >= r[i]) q.push({r[i]-l[i]});
            else if(right <= l[i]) q.push({0});
            else q.push({left-l[i],1});
        }
        while(q.size() > 1){
            vector<mint> a = q.front(); q.pop();
            q.push(multiply(a,q.front())); q.pop();
        }
        vector<mint> vv = q.front();
        vv.push_back(0);
        rrep(i,vv.size()-2,0) vv[i+1] = vv[i]*inv[i+1];
        mint rf = right-left;
        rep(i,1,vv.size()){
            ans += -rf*vv[i];
            rf *= right-left;
        }
        // cout << vv.size() << " " << (ans*nfac).val() << " " << ans.val() << endl;
    };

    rep(i,0,vec.size()-1) calc(vec[i],vec[i+1]);
    ans *= nfac;
    cout << ans.val() << endl;
    return 0;
}