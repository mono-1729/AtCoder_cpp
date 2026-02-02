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
    ll k; cin >> k;
    ll x, y; cin >> x >> y;
    if(abs(x)+abs(y) == k){
        cout << 1 << endl;
        cout << x << " " << y << endl;
        return 0;
    }
    vector<pll> ans;
    auto solve = [&](auto solve, ll nx, ll ny, ll cnt) -> void {
        if(cnt == 2){
            ll f = (abs(x-nx) > abs(y-ny));
            if(f) swap(x,y), swap(nx,ny);
            ll yobun = (k*2-abs(x-nx)-abs(y-ny))/2, rem = k;
            ll px = nx, py = ny;
            if(x > nx){
                ll num = x-nx;
                px += num+yobun, rem -= num+yobun;
            }else{
                ll num = nx-x;
                px -= num+yobun, rem -= num+yobun;
            }
            {
                ll num = min(rem,y-ny);
                if(num > 0) py += num, rem -= num;
            }
            {
                ll num = min(rem,ny-y);
                if(num > 0) py -= num, rem -= num;
            }
            ans.push_back({px,py});
            if(f){
                swap(ans.back().first,ans.back().second);
                swap(x,y), swap(nx,ny);
            }
            ans.push_back({x,y});
        }else{
            ll rem = k;
            ll px = nx, py = ny;
            {
                ll num = min(rem,x-nx);
                if(num > 0) px += num, rem -= num;
            }
            {
                ll num = min(rem,nx-x);
                if(num > 0) px -= num, rem -= num;
            }
            {
                ll num = min(rem,y-ny);
                if(num > 0) py += num, rem -= num;
            }
            {
                ll num = min(rem,ny-y);
                if(num > 0) py -= num, rem -= num;
            }
            if(rem > 0){
                if(nx < px) px += rem;
                else if(nx > px) px -= rem;
                else if(ny < py) py += rem;
                else py -= rem;
            }
            ans.push_back({px,py});
            solve(solve,px,py,cnt-1);
        }
    };
    ll ok = 0;
    rep(i,2,1000000){
        if(i*k >= abs(x)+abs(y) && (i*k - (abs(x)+abs(y)))%2 == 0){
            ok = 1;
            solve(solve,0,0,i);
            break;
        }
    }
    if(ok){
        cout << ans.size() << endl;
        for(auto [a, b]: ans) cout << a << " " << b << endl;
    }else cout << -1 << endl;
    return 0;
}