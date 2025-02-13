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

std::vector<ll> sieve(int n){
    //素数候補を管理する配列
    std::vector<ll> min_factor(n+1);
    //2以上の数を一度素数候補に入れる
    for(int i = 0; i <= n; i++) min_factor[i] = i;
    //それぞれの数について最小の素因数を求める
    for(int i = 2; i*i <= n; i++){
        if(min_factor[i] == i){
            for(int j = 2; i*j <= n; j++){
                if(min_factor[i*j] > i){
                    min_factor[i*j] = i;
                }
            }
        }
    }
    return min_factor;
}

std::vector<ll> factor(std::vector<ll> &min_factor, int m){
    std::vector<ll> ans;
    while(m > 1){
        ans.push_back(min_factor[m]);
        m /= min_factor[m];
    }
    return ans;
}

mint powMod(mint x, ll n) {
    if (n == 0) return 1;
    mint val = powMod(x, n / 2);
    val *= val;
    if (n % 2 == 1) val *= x;
    return val;
}


int main() {
    ll n; cin >> n;
    vector<ll> erat = sieve(1001);
    vector<ll> a(n-1);
    vector<vector<pll>> vec(1001);
    rep(i,0,n-1) cin >> a[i];
    rep(i,0,n-1){
        vector<ll> fac = factor(erat, a[i]);
        ll now = 0;
        while(now < fac.size()){
            ll r = now;
            while(r < fac.size() && fac[now] == fac[r]) r++;
            vec[fac[now]].push_back({i,r-now});
            now = r;
        }
    }
    rep(i,2,1001) vec[i].push_back({n-1,0});

    mint ans = 1;
    rep(i,2,1001){
        if(vec[i].size() == 1) continue;
        ll si = 0;
        for(auto [x, y] : vec[i]) si += y;
        vector<mint> dp(si+1);
        vector<mint> p(max(n,si)+1,1);
        rep(j,0,max(n,si)) p[j+1] = p[j]*i;
        dp[0] = 1;
        ll pre = -1;
        // cout << i << endl;
        for(auto [idx, cnt] : vec[i]){
            // cout << idx << " " << cnt << endl;
            vector<mint> ndp(si+1);
            vector<mint> x(cnt+1,1);
            rep(j,0,cnt) x[j+1] = x[j] * p[idx+1];
            rep(j,0,si+1){
                if(dp[j] == 0) continue;
                mint z = powMod(p[idx-pre], j);
                ndp[j+cnt] += dp[j]*z;
                if(cnt == 0) continue;
                if(j-cnt < 0){
                    ndp[0] += dp[j]*z*x[cnt-j];
                }else{
                    ndp[j-cnt] += dp[j]*z;
                }
            }
            pre = idx;
            swap(dp, ndp);
        }
        mint sum = 0;
        rep(j,0,si+1) sum += dp[j];
        ans *= sum; 
        // rep(j,0,si+1) cout << dp[j].val() << " ";
        // cout << endl;
    }
    cout << ans.val() << endl;
    return 0;
}