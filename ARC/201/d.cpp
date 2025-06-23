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
    ll t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        vector<pll> vec(2*n);
        rep(i,0,n){
            ll a; cin >> a;
            vec[i] = {(m-a),-1};
        }
        rep(i,0,n){
            ll b; cin >> b;
            vec[i+n] = {b,1};
        }
        sort(all(vec));
        ll mini = 0, id = 0;
        ll now = 0;
        rep(i,0,2*n){
            auto [num, type] = vec[i];
            now -= type;
            // cout << i << " " << num << " " << type << " " << now << endl;
            if(mini > now){
                mini = now;
                id = (i+1) % (2*n);
            }
        }
        // cout << "id: " << id << endl;
        {
            vector<pll> nvec;
            rep(i,id,2*n) nvec.push_back(vec[i]);
            rep(i,0,id) nvec.push_back({vec[i].first+m, vec[i].second});
            swap(vec, nvec);
        }
        ll ans = 0;
        queue<ll> que;
        rep(i,0,2*n){
            auto [num, type] = vec[i];
            // cout << num << " " << type << endl;
            if(type == -1) que.push(num);
            else {
                assert(que.size() > 0);
                ll a = que.front(); que.pop();
                chmax(ans, num-a);
            }
        }
        cout << ans << endl;
    }
    return 0;
}