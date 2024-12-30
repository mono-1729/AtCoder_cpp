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
    ll n, k; cin >> n >> k;
    ll ans = 0;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    ll num = 0;
    if(k*2 > n){
        rep(i,0,n){
            num ^= a[i];
        }
        k = n-k; 
    }
    bitset<200005> bs;
    rep(i,0,k){
        bs[i] = 1;
        num ^= a[i];
    }
    ans = num;
    if(k == 0){
        cout << ans << endl;
        return 0;
    }
    ll last = k-1;
    auto next = [&]() -> bool {
        if(last == n-1){
            ll cnt = 0;
            ll idx = last;
            while(bs[idx] == 1){
                cnt++;
                num ^= a[idx];
                bs[idx] = 0;
                idx--;
                if(cnt == k) return false;
            }
            while(bs[idx] == 0) idx--;
            bs[idx] = 0;
            num ^= a[idx];
            idx++;
            rep(i,0,cnt+1){
                bs[idx] = 1;
                num ^= a[idx];
                idx++;
            }
            last = idx-1;
            return true;      
        }else{
            bs[last] = 0;
            num ^= a[last];
            last++;
            bs[last] = 1;
            num ^= a[last];
            return true;
        }
        return true;
    };
    while(next()){
        chmax(ans,num);
    }
    cout << ans << endl;
    return 0;
}