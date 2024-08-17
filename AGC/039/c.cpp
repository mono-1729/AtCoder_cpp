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
    string s; cin >> s;
    string t = s;
    rep(i,0,n)t[i] = t[i] == '0' ? '1' : '0';
    s = s + t;
    n *= 2;
    vector<ll> div;
    rep(i,1,n+1){
        if(n%i == 0 && (n/2)%i != 0) div.push_back(i);
    }
    mint ans = 0;
    ll m = div.size();
    vector<mint> cnt(m,0);
    rep(i,0,m){
        ll x = div[i];
        rep(j,0,i) if(x%div[j] == 0) cnt[i] -= cnt[j];
        mint num = 1;
        rep(j,0,x/2){
            num *= 2;
            num += s[j] -'0';
            num--;
        }
        string ss(x,'0');
        rep(j,0,x/2)ss[j] = s[j];
        rep(j,x/2,x)ss[j] = ss[j-x/2] == '1' ? '0' : '1';
        rep(j,0,n){
            if(s[j] > ss[j%x]){
                break;
            }else if(s[j] < ss[j%x]){
                num--;
                break;
            }
        }
        cnt[i] += num;
        ans += cnt[i] * x;
    }
    cout << ans.val() << endl;
    return 0;
}