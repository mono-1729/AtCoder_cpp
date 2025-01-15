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

cpp_int gcd(cpp_int a, cpp_int b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

cpp_int lcm(cpp_int a, cpp_int b){
    return a*b / gcd(a, b);
}


int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<ll> ans;
    rrep(len,n,2){
        vector<cpp_int> llcm(len+1, 1), rlcm(len+1,1);
        rep(i,0,len) llcm[i+1] = lcm(llcm[i], a[i]);
        rrep(i,len-1,0) rlcm[i] = lcm(rlcm[i+1], a[i]);
        bool ok = false;
        cpp_int all = llcm[len];
        rep(i,0,len){
            if(lcm(llcm[i], rlcm[i+1]) != all){
                ok = true;
                ans.push_back(a[i]);
                a.erase(a.begin()+i);
                break;
            }
        }
        if(!ok){
            cout << "No" << endl;
            return 0;
        }
    }
    ans.push_back(a[0]);
    cout << "Yes" << endl;
    reverse(ans.begin(), ans.end());
    for(auto x: ans) cout << x << " ";
    cout << endl;
    return 0;
}