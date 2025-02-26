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
    string s; cin >> s;
    vector<vector<mint>> dp(n,vector<mint>(16, 0));
    dp[0][9] = 1;
    mint ans = 0;
    vector<ll> cnt(4, 0);
    rep(i,0,n-1){
        rep(j,1,16){
            if(dp[i][j] == 0) continue;
            rep(k,0,4) cnt[k] = 0;
            rep(k,0,4){
                if(((j >> k) & 1) == 0) continue;
                if(s[i] == '0'){
                    cnt[k/2+1] |= (1<<(k%2));
                    cnt[k/2] |= (1<<(2+k%2));
                }
                else{
                    cnt[k/2+1] |= (1<<(k%2));
                    cnt[k/2] |= (1<<(2+k%2));
                    cnt[k/2+2] |= (1<<(k%2));
                    cnt[k/2+1] |= (1<<(2+k%2));
                }
            }
            rep(k,0,4) if(cnt[k] != 0) dp[i+1][cnt[k]] += dp[i][j];
        }
    }
    // rep(x, 0, n){
    //     rep(i,0,16) cout << dp[x][i].val() << " ";
    //     cout << endl;
    // }

    
    {
        rep(j,1,16){
            if(dp[n-1][j] == 0) continue;
            rep(k,0,4) cnt[k] = 0;
            rep(k,0,4){
                if((j >> k & 1) == 0) continue;
                if(s[n-1] == '0'){
                    cnt[k/2+(1-k%2)] = 1;
                }
                else{
                    cnt[k/2+(1-k%2)] = 1;
                    cnt[k/2+(1-k%2)+1] = 1;
                }
            }
            rep(k,0,4) if(cnt[k] == 1) ans += dp[n-1][j];
        }
    }
    cout << ans.val() << endl;
    return 0;
}