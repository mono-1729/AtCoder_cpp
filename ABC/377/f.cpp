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
    ll n, m; cin >> n >> m;
    vector<pll> lines;
    ll sum = n*n;

    rep(i, 0, m){
        ll a, b; cin >> a >> b;
        a--; b--;
        lines.push_back({0, a});
        lines.push_back({1, b});
        lines.push_back({2, b-a});
        lines.push_back({3, b+a});
    }
    
    sort(lines.begin(), lines.end());
    lines.erase(unique(lines.begin(), lines.end()), lines.end());

    unordered_map<ll, ll> mp;

    rep(i, 0, lines.size()){
        if(lines[i].first == 0 || lines[i].first == 1) sum -= n;
        if(lines[i].first == 2){
            ll l = max(0LL, lines[i].second);
            ll r = min(n-1, lines[i].second+n-1);
            sum -= max(0LL, r-l+1);
        }
        if(lines[i].first == 3){
            ll l = max(0LL, lines[i].second-n+1);
            ll r = min(n-1, lines[i].second);
            sum -= max(0LL, r-l+1);
        }
        rep(j, i+1, lines.size()){
            auto [t1, a1] = lines[i];
            auto [t2, a2] = lines[j];
            if(t1 == 0){
                if(t2 == 1) mp[a1 * n + a2]++;
                if(t2 == 2 && a2 + a1 < n && a1 + a2 >= 0) mp[a1 * n + a1 + a2]++;
                if(t2 == 3 && a2 - a1 >= 0 && a2 - a1 < n) mp[a1 * n + a2 - a1]++;
            }
            if(t1 == 1){
                if(t2 == 2 && a1 - a2 >= 0 && a1 - a2 < n) mp[(a1 - a2) * n + a1]++;
                if(t2 == 3 && a2 - a1 < n && a2 - a1 >= 0) mp[(a2 - a1) * n + a1]++;
            }
            if(t1 == 2){
                if(t2 == 3){
                    if(abs(a1 - a2) % 2 == 0){
                        ll x = (a1 + a2) / 2 - a1;
                        ll y = (a1 + a2) / 2;
                        if(x >= 0 && x < n && y >= 0 && y < n) mp[x * n + y]++;
                    }
                }
            }
        }
    }


    unordered_map<ll, ll> cmp;
    rep(i,2,lines.size()+1) cmp[i*(i-1)/2] = i-1;

    for(auto [key, val] : mp){
        sum += cmp[val];
    }

    cout << sum << endl;
    return 0;
}