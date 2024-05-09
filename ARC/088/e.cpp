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

using S = long long;
S op(S x1, S x2) {
    return x1+x2;
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    string s;cin>>s;
    ll n = s.size();
    vector<vector<ll>> charidx(26),ansidx(26);
    vector<ll> charcnt(26, 0);
    rep(i,0,n)charidx[s[i]-'a'].push_back(i);
    ll odd = 0;
    rep(i,0,26){
        if(charidx[i].size()%2)odd++;
        charcnt[i] = charidx[i].size();
    }
    if(odd>1){
        cout<<-1<<endl;
        return 0;
    }
    string t = "";
    char oddchar;
    rep(i,0,n){
        if(charcnt[s[i]-'a']>=2){
            t += s[i];
            charcnt[s[i]-'a'] -= 2;
        }
        if(charcnt[s[i]-'a']==1) oddchar = s[i];
    }
    string u = t;
    if(n%2)u+=oddchar;
    reverse(t.begin(), t.end());
    u+=t;
    rep(i,0,n) ansidx[u[i]-'a'].push_back(i);
    segtree<S, op, e> seg(n);
    ll ans = 0;
    unordered_map<ll, ll> mp;
    rep(i,0,26){
        rep(j,0,charidx[i].size()) mp[charidx[i][j]] = ansidx[i][j];
    }
    rep(i,0,n){
        ans+=seg.prod(mp[i],n);
        seg.set(mp[i],1);
    }
    cout<<ans<<endl;
    return 0;
}