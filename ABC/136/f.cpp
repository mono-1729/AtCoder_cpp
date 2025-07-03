#include <bits/stdc++.h>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
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
struct point {
    int x;
    int y;
    
};

using S = int;
S op(S x1, S x2) {
    return x1+x2;
} 
S e() {return 0;}

int main() {
    int n; cin >> n;
    vector<point> pos(n);
    vector<int> xlist, ylist;
    vector<mint> pow2(n+1,1);
    rep(i,0,n) pow2[i+1] = pow2[i] * 2; 
    rep(i,0,n){
        int x, y; cin >> x >> y;
        pos[i] = {x,y};
        xlist.push_back(x);
        ylist.push_back(y);
    }
    sort(pos.begin(), pos.end(),[](const auto &a, const auto &b){
        return a.x < b.x;
    });
    sort(xlist.begin(), xlist.end());
    sort(ylist.begin(), ylist.end());
    unordered_map<int,int> xmp, ymp;
    rep(i,0,n){
        xmp[xlist[i]] = i;
        ymp[ylist[i]] = i;
    }
    rep(i,0,n){
        pos[i] = {xmp[pos[i].x],ymp[pos[i].y]};
    }
    segtree<S,op,e> segleft(n),segright(vector<S>(n,1));
    mint ans = 0;
    rep(i,0,n){
        auto[x,y] = pos[i];
        segright.set(y,0);
        ans += pow2[n];
        rep(j,1,1<<4){
            int cnt = 0;
            int ld = segleft.prod(0,y), lu = segleft.prod(y,n), rd = segright.prod(0,y), ru = segright.prod(y,n);
            if((j >> 1 & 1) == 0 && (j >> 3 & 1) == 0) cnt += ld;
            if((j >> 1 & 1) == 0 && (j >> 2 & 1) == 0) cnt += lu;
            if((j >> 0 & 1) == 0 && (j >> 3 & 1) == 0) cnt += rd;
            if((j >> 0 & 1) == 0 && (j >> 2 & 1) == 0) cnt += ru;
            if(__popcount(j)%2 == 0) ans += pow2[cnt];
            else ans -= pow2[cnt];
        }
        segleft.set(y,1);
    }
    cout << ans.val() << endl;
    return 0;
}