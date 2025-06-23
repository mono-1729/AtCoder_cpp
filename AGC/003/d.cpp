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

int main() {
    ll n; cin >> n;
    vector<ll> s(n);
    rep(i,0,n) cin >> s[i];
    unordered_map<ll,ll> square;
    unordered_map<ll,ll> cnt;
    unordered_map<ll,ll> pir;
    rep(i,1,100001) square[i*i] = i;
    rep(i,0,n){
        ll px = 1;
        ll num = 1;
        rep(j,2,2160){
            ll c = 0;
            while(s[i]%j == 0){
                c++;
                s[i] /= j;
            }
            c %= 3;
            rep(k,0,c) num *= j;
            rep(k,0,(3-c)%3) px *= j;
        }
        if(square[s[i]] == 0){
            if(s[i] >= 100001){
                cnt[num*s[i]]++;
                pir[num*s[i]] = -1;
            }else{
                cnt[num*s[i]]++;
                pir[num*s[i]] = px*s[i]*s[i];
            }
        }else{
            cnt[num*s[i]]++;
            pir[num*s[i]] = px*square[s[i]];
            // cout << i << " " << num*s[i] << " " << px*square[s[i]] << " " << px << " " << square[s[i]] << endl;
        }
    }
    ll ans = 0;
    vector<ll> vec;
    for(auto [x,y]: cnt) vec.push_back(x);
    for(auto x: vec){
        if(x == 1){
            ans++;
            continue;
        }
        ans += max(cnt[x], cnt[pir[x]]);
        cnt[x] = 0;
        cnt[pir[x]] = 0;
    }
    cout << ans << endl;
    return 0;
}