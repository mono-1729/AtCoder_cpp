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
    if (n == 0) return 1LL;
    ll val = powMod(x, n / 2);
    val *= val;
    if (n % 2 == 1) val *= x;
    return val;
}

// 0ならば素数, 0でないなら最⼩の素因数
// 素因数分解や素因数の数も求めることが可能
ll max_num=2000005;
vector<ll> erat(max_num);
void init_e(){
    rep(i, 2, sqrt((double)max_num-1)){
        if(erat[i] == 0){
            for(ll j = i*i; j <= max_num-1; j += i){
                if(erat[j] == 0) erat[j] = i;
            }
        }
    }
}

int main() {
    init_e();
    ll n; cin >> n;
    ll ans = 0;
    rep(i,2,100){
        if(erat[i] == 0) if(n >= powMod(i, 8)) ans++;
    }
    vector<ll> a;
    rep(i,2,2000005)if(erat[i] == 0) a.push_back(i*i);
    rrep(i,2000005, 2){
        if(erat[i] != 0) continue;
        ans += upper_bound(a.begin(), a.end(), min(n/(i*i),i*i-1)) - a.begin();
        // if(upper_bound(a.begin(), a.end(), min(n/(i*i),i*i-1)) - a.begin() > 0) cout << i << " " << upper_bound(a.begin(), a.end(), min(n/(i*i),i*i-1)) - a.begin() << endl;
    }
    cout << ans << endl;
    return 0;
}