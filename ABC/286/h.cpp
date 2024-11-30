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

struct Pos {
  ll x, y;
  Pos() {}
  Pos(ll x, ll y) : x(x), y(y) {}
  bool operator< (const Pos& other) const {
    return (x == other.x ? y < other.y : x < other.x);
  }
};
 
inline ll cross(Pos &a, Pos &b, Pos &c) {
  return (((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x)));
}
 
void convex_hull(vector<Pos> &ps, vector<Pos> &qs) {
  sort(ps.begin(), ps.end());
  qs.clear();
  qs.reserve(ps.size());
  int n = ps.size();
  for(auto p : ps) {
    // 外積判定の等号なし => 凸包の直線上にある点も含む
    while(qs.size() > 1 && cross(qs[qs.size()-2], qs[qs.size()-1], p) > 0) {
      qs.pop_back();
    }
    qs.push_back(p);
  }
  int t = qs.size();
 
  for(int i = n-2; i >= 0; --i) {
    Pos &p = ps[i];
    while(qs.size() > t && cross(qs[qs.size()-2], qs[qs.size()-1], p) > 0) {
      qs.pop_back();
    }
    qs.push_back(p);
  }
  qs.pop_back();
}

int main() {
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    vector<Pos> ps(n+2), qs;
    rep(i, 0, n) cin >> ps[i].x >> ps[i].y;
    ll sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;
    if(sx == tx && sy == ty){
        cout << 0 << endl;
        return 0;
    }
    bool flg_ = true;
    ps[n] = {sx, sy}, ps[n+1] = {tx, ty};
    rep(i, 0, n){
        if(cross(ps[i], ps[(i+1)%n], ps[n]) * cross(ps[i], ps[(i+1)%n], ps[n+1]) < 0) flg_ = false;
    }
    if(flg_){
        cout << sqrt((double)(sx-tx)*(sx-tx) + (sy-ty)*(sy-ty)) << endl;
        return 0;
    }
    convex_hull(ps, qs);
    double ans1 = 0, ans2 = 0;
    int flg = 0;
    rep(i,0,qs.size()){
        if((qs[i].x == sx && qs[i].y == sy) || (qs[i].x == tx && qs[i].y == ty)) flg = 1-flg;
        double dist = sqrt((double)(qs[i].x-qs[(i+1)%qs.size()].x)*(qs[i].x-qs[(i+1)%qs.size()].x) + (qs[i].y-qs[(i+1)%qs.size()].y)*(qs[i].y-qs[(i+1)%qs.size()].y));
        if(flg == 0) ans1 += dist;
        else ans2 += dist;
    }
    cout << min(ans1, ans2) << endl;
    return 0;
}