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

ll maxnum=300005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    string s; cin >> s;
    reverse(s.begin(), s.end());
    ll n = s.size();
    vector<vector<mint>> dp(n+1, vector<mint>(2,0));
    vector<mint> num(n+1,0);
    num[n] = 1;
    vector<mint> pow26(n+1,1);
    rep(i,0,n) pow26[i+1] = pow26[i]*26;
    {
        bool flg = false;
        vector<ll> cnt(26,0);
        ll ha = 0;
        ll use = 0;
        rrep(i,n-1,0){
            if(s[i] == '?') ha++;
            else if(s[i] <= 'Z'){
                cnt[s[i]-'A']++;
                if(cnt[s[i]-'A'] == 1) use++;
                else if(cnt[s[i]-'A'] == 2) flg = true;
            }
            if(flg) num[i] = 0;
            else{
                rep(j,0,26-use+1){
                    if(ha-j < 0) break;
                    num[i] += mint(1) * nCr(ha,j) * nCr(26-use, j) * fac[j] * pow26[ha-j];
                    // cout << i << " " << ha << " " << j << " " << use << " " << num[i].val() << endl;

                }
            }
        }
    }
    dp[0][0] = 1;
    mint ans = 0;
    rep(i,0,n){
        if(s[i] == '?'){
            dp[i+1][0] = dp[i][0]*26;
            dp[i+1][1] = (dp[i][0]+dp[i][1])*26;
            ans += dp[i][1]*26*num[i+1];
        }else if(s[i] <= 'Z'){
            dp[i+1][1] = dp[i][0]+dp[i][1];
        }else{
            dp[i+1][0] = dp[i][0];
            dp[i+1][1] = 0;
            ans += dp[i][1]*num[i+1];
        }
        // cout << ans.val() << endl;
    }
    ans += dp[n][0]+dp[n][1];
    cout << ans.val() << endl;
    return 0;
}