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

ll n; 

struct mset{
    ll sum = 0;
    multiset<ll> mini, maxi;
    void add(ll x){
        if(mini.size() < n-2) mini.insert(x), sum += x;
        else if(mini.size() == 0 || *mini.rbegin() <= x) maxi.insert(x);
        else{
            sum -= *mini.rbegin();
            maxi.insert(*mini.rbegin());
            mini.erase(mini.find(*mini.rbegin()));
            mini.insert(x);
            sum += x;
        }
    }
    void del(ll x){
        auto it = maxi.find(x);
        if(it != maxi.end()) maxi.erase(it);
        else{
            sum -= x;
            mini.erase(mini.find(x));
            if(maxi.size() > 0){
                it = maxi.begin();
                mini.insert(*it);
                sum += *it;
                maxi.erase(it);
            }
        }
        
    }
};

int main() {
    cin >> n;
    ll asum = 0, bsum = 0;
    vector<ll> a(n), b(n);
    mset st;
    rep(i,0,n){
        cin >> a[i] >> b[i];
        asum += a[i];
        bsum += b[i];
        st.add(a[i]);
        st.add(b[i]);
    }
    ll ans = min(asum, bsum);
    rep(i,0,n){
        st.del(a[i]);
        st.del(b[i]);
        chmin(ans,st.sum+a[i]+b[i]);
        st.add(a[i]);
        st.add(b[i]);
    }
    cout << ans << endl;
    return 0;
}