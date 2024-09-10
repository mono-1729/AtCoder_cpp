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

using mint = modint1000000007;

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
    vector<int> a(n);
    rep(i,0,n) cin >> a[i];
    vector<int> cum(n+1,0);
    rep(i,0,n) cum[i+1] = cum[i] ^ a[i];
    mint ans = 0;
    if(cum.back() == 0){
        // rep(i,0,n+1) cout << cum[i] << " ";
        cout << endl;
        vector<int> cum0(n+1,0);
        rep(i,1,n+1){
            cum0[i] = cum0[i-1];
            if(cum[i] == 0) cum0[i]++;
        }
        vector<vector<int>> idxs(1<<20);
        rep(i,0,n+1) idxs[cum[i]].push_back(i);
        mint num = 1;
        rep(i,0,idxs[0].size()-2) num *= 2;
        ans += num;
        rep(i,1,1<<20){
            if(idxs[i].size() == 0) continue;
            mint sum0 = 1, sum1 = 0;
            int pre = 0;
            for(auto idx: idxs[i]){
                // cout << idx << " " << pre << " " << cum0[idx]-cum0[pre] << " " << sum0.val() << " " << sum1.val() << endl;
                if(cum0[idx]-cum0[pre] > 0) sum0 += sum1 * (cum0[idx]-cum0[pre]);
                sum1 += sum0;
                pre = idx;
            }
            ans += sum1;
        }
    }else{
        vector<int> cum0(n+1,0);
        cum0[0] = 1;
        rep(i,1,n+1){
            cum0[i] = cum0[i-1];
            if(cum[i] == 0) cum0[i]++;
        }
        vector<vector<int>> idxs(1<<20);
        rep(i,0,n+1) idxs[cum[i]].push_back(i);
        mint sum0 = 1, sum1 = 0;
        int pre = 0;
        for(auto idx: idxs[cum[n]]){
            if(cum0[idx]-cum0[pre] > 0) sum0 += sum1 * (cum0[idx]-cum0[pre]);
            sum1 += sum0;
            pre = idx;
        }
        ans += sum0;
    }
    cout << ans.val() << endl;
    return 0;
}