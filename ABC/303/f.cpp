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

struct st {
    ll t;
    ll d;
};

int main() {
    ll n, h; cin >> n >> h;
    vector<st> td;
    rep(i,0,n){
        ll t, d; cin >> t >> d;
        td.push_back({t,d});
    }
    sort(td.begin(), td.end(), [](const auto a, const auto b){
        return a.d > b.d;
    });
    vector<st> vec;
    rep(i,0,n){
        bool flg = true;
        auto [x,y] = td[i];
        while(!vec.empty()){
            auto [a,b] = vec.back();
            if(a*b >= x*y){
                flg = false;
                break;
            }else if(y == b) vec.pop_back();
            else break;
        }
        if(flg) vec.push_back(td[i]);
    }
    vector<ll> limit(vec.size(), INF);
    rep(i,0,vec.size()-1){
        auto [t1, d1] = vec[i];
        auto [t2, d2] = vec[i+1];
        ll l = 0, r = INF;
        while(r-l > 1){
            ll mid = (l+r)/2;
            if(d1 * min(mid,t1) >= d2 * min(mid,t2)) l = mid;
            else r = mid;
        }
        limit[i] = l;
    }
    ll l = 0, r = 1e18;
    while(r-l > 1){
        ll mid = (l+r)/2;
        ll cnt = h;
        auto add = [&](ll i, ll left, ll right) -> bool {
            auto [t,d] = vec[i];
            __int128_t num = 0;
            if(left <= t) num = __int128_t(1)*(min(right,t)-left+1)*(d*left + d*min(right,t))/2;
            ll newl = min(right,t);
            if(num >= cnt) return true;
            cnt -= num;
            if(INF/(d*t) <= (right - newl)) return true;
            // cout << t << " " << d << " " << newl << " " << right << " " << num << endl;
            cnt -= (d*t)*(right - newl);
            if(cnt <= 0) return true;
            return false;
        };
        ll x = 1;
        rep(i,0,vec.size()){
            if(add(i, x, min(mid,limit[i]))){
                cnt = 0;
                break;
            }
            if(limit[i] >= mid) break;
            x = limit[i]+1;
        }
        if(cnt > 0) l = mid;
        else r = mid;
    }
    cout << r << endl;
    return 0;
}