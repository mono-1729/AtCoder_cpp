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

int main() {
    ll n, m; cin >> n >> m;
    vector<int> check(n,0);
    rep(i,0,m){
        ll a; cin >> a;
        a--;
        char b; cin >> b;
        if(b != 'M') cout << "No" << endl;
        else{
            if(check[a] == 0) cout << "Yes" << endl;
            else cout << "No" << endl;
            check[a] = 1;
        }
    }
    return 0;
}