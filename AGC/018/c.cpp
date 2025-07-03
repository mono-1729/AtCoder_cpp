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

struct Coin{
    ll a, b, c;
};

int main() {
    ll x, y, z; cin >> x >> y >> z;
    ll n = x+y+z;
    vector<Coin> coins(n);
    rep(i,0,n){
        ll a, b, c; cin >> a >> b >> c;
        coins[i] = {a,b,c};
    }
    sort(all(coins), [](const auto p, const auto q){
        auto [a1,b1,c1] = p;
        auto [a2,b2,c2] = q;
        return a1-c1 > a2-c2;
    });
    vector<ll> left(n+1,-INF),right(n+1,-INF);
    {
        ll num = 0;
        multiset<ll> st;
        rep(i,0,x){
            Coin co = coins[i];
            num += co.a;
            st.insert(co.b-co.a);
        }
        ll now = x;
        while(true){
            left[now] = num;
            if(now == n) break;
            num += coins[now].a;
            st.insert(coins[now].b-coins[now].a);
            num += *st.rbegin();
            st.erase(st.find(*st.rbegin()));
            now++;
        }
    }
    reverse(all(coins));
    {
        ll num = 0;
        multiset<ll> st;
        rep(i,0,z){
            Coin co = coins[i];
            num += co.c;
            st.insert(co.b-co.c);
        }
        ll now = z;
        while(true){
            right[n-now] = num;
            if(n-now == 0) break;
            num += coins[now].c;
            st.insert(coins[now].b-coins[now].c);
            num += *st.rbegin();
            st.erase(st.find(*st.rbegin()));
            now++;
        }
    }
    ll ans = 0;
    rep(i,0,n+1) chmax(ans,left[i]+right[i]);
    cout << ans << endl;
    return 0;
}