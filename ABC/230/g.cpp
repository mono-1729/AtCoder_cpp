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

struct Eratosthenes {
    // テーブル
    vector<bool> isprime;
    
    // 整数 n を割り切る最小の素数
    vector<int> minfactor;

    // メビウス関数値
    vector<int> mobius;

    // コンストラクタで篩を回す
    Eratosthenes(int N) : isprime(N+1, true),
                          minfactor(N+1, -1),
                          mobius(N+1, -1) {
        // 1 は予めふるい落としておく
        isprime[1] = false;
        minfactor[1] = 1;
        mobius[1] = 0;

        // 篩
        for (int p = 2; p <= N; ++p) {
            // すでに合成数であるものはスキップする
            if (!isprime[p]) continue;

            // p についての情報更新
            minfactor[p] = p;
            mobius[p] = 1;
            
            // p 以外の p の倍数から素数ラベルを剥奪
            for (int q = p * 2; q <= N; q += p) {
                // q は合成数なのでふるい落とす
                isprime[q] = false;
                
                // q は p で割り切れる旨を更新
                if (minfactor[q] == -1) minfactor[q] = p;
                if ((q / p) % p == 0) mobius[q] = 0;
                else mobius[q] = -mobius[q];
            }
        }
    }
};


int main() {
    ll n; cin >> n;
    Eratosthenes erat(n+1);
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i];
    vector<vector<ll>> nums(n+1);
    rep(i,2,n+1){
        ll now = i;
        while(now <= n){
            nums[i].push_back(p[now-1]);
            now += i;
        }
    }
    ll ans = 0;
    rep(i,2,n+1){
        if(erat.mobius[i] == 0) continue;
        unordered_map<ll,ll> mp;
        for(auto x: nums[i]){
            vector<ll> idx;
            ll now = x;
            while(now > 1){
                idx.push_back(erat.minfactor[now]);
                now /= erat.minfactor[now];
            }
            idx.erase(unique(idx.begin(), idx.end()), idx.end());
            rep(j,1,1<<idx.size()){
                ll val = 1;
                rep(k,0,idx.size()) if(j>>k&1) val *= idx[k];
                mp[val]++;
            }
        }
        for(auto [key, val]: mp){
            ans += (erat.mobius[i]*erat.mobius[key] * val * (val+1)) / 2;
        }
    }
    cout << ans << endl;
    return 0;
}