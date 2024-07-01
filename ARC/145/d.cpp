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

int p = 3000000;

int main() {
    ll n, m; cin >> n >> m;
    int x = m/n;m %= n;
    vector<int> ans;
    vector<int> vec(6000001,1);
    if(m == 0){
        if(n == 1){
            ans.push_back(0);
            n--;
        }else if(n%2 == 1){
            ans.push_back(-9000000);
            ans.push_back(4000000);
            ans.push_back(5000000);
            vec[3000000+p] = 0;
            vec[-2500000+p] = 0;
            n-=3;
        }
    }
    else{
        if(n%2 == 1){
            ans.push_back(m);
            vec[m+p] = 0;
            n--;
        }
        else{
            ans.push_back(-8000000);
            ans.push_back(8000000+m);
            if(m&2 == 0) vec[m/2+p] = 0;
            n-=2;
        }
    }
    int cnt = 3000000;
    while(n>0){
        while(vec[cnt+p] == 0 || vec[-cnt+p] == 0) cnt--;
        for(auto a:ans){
            if(abs(2*a+cnt)<=p) vec[2*a+cnt+p] = 0;
            if(abs(2*cnt+a)<=p) vec[2*cnt+a+p] = 0;
            if((cnt+a)%2 == 0 && abs((cnt+a)/2)<=p) vec[(cnt+a)/2 +p] = 0;
        }
        ans.push_back(cnt);
        vec[cnt+p] = 0;
        for(auto a:ans){
            if(abs(2*a-cnt)<=p) vec[2*a-cnt+p] = 0;
            if(abs(-2*cnt+a)<=p) vec[-2*cnt+a+p] = 0;
            if((-cnt+a)%2 == 0 && abs((-cnt+a)/2)<=p) vec[(-cnt+a)/2 +p] = 0;
        }
        ans.push_back(-cnt);
        vec[-cnt+p] = 0;
        cnt--;
        n-=2;
    }
    for(auto a:ans) cout << a+x << " ";
    cout << endl;
    return 0;
}