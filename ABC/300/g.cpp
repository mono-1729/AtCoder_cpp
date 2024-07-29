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
    if (n == 0) return 1;
    ll val = powMod(x, n / 2);
    val *= val;
    if (n % 2 == 1) val *= x;
    return val;
}

int main() {
    ll n, p; cin >> n >> p;
    vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    vector<ll> nums = {1};
    ll idx = primes.size()-1;
    rep(i,0,primes.size()){
        if(primes[i] > p || nums.size() > 100000){
            idx = i-1;
            break;
        }
        vector<ll> nnums;
        for(auto x: nums){
            for(ll y = x; y<=n; y*=primes[i]) nnums.push_back(y);
        }
        swap(nums,nnums);
    }
    sort(nums.begin(), nums.end());
    auto solve = [&](auto& solve, ll num2, int id) -> ll {
        if(id <= idx){
            return upper_bound(nums.begin(), nums.end(), n/num2) - nums.begin();
        }
        ll res = 0;
        ll m = 1;
        while(true){
            if(n/(num2*m) == 0) break;
            res += solve(solve, num2*m, id-1);
            m *= primes[id];
        }
        return res;
    };
    rep(i,0,primes.size()){
        if(primes[i] == p)cout << solve(solve,1,i) << endl;
    }
    return 0;
}