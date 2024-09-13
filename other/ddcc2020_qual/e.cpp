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
    ll n; cin >> n;
    string ans(n*2,'_');
    char lc;
    {
        cout << "? ";
        rep(i,1,n+1) cout << i << " ";
        cout << endl;
        string res; cin >> res;
        lc = res[0];
    }
    ll l = 0, r = n;
    while(r-l > 1){
        ll mid = (r+l)/2;
        cout << "? ";
        rep(i,mid+1,mid+n+1) cout << i << " ";
        cout << endl;
        string res; cin >> res;
        if(res[0] == lc) l = mid;
        else r = mid;
    }
    ans[l] = lc, ans[l+n] = lc == 'R' ? 'B' : 'R';
    rep(i,0,2*n){
        if(ans[i] != '_') continue;
        if(i < l || l+n < i){
            cout << "? " << i+1 << " ";
            rep(j,l+2,l+n+1) cout << j << " ";
            cout << endl;
            string res; cin >> res;
            ans[i] = res[0];
        }else{
            cout << "? " << i+1 << " ";
            rep(j,1,l+1) cout << j << " ";
            rep(j,l+n+2,n*2+1) cout << j << " ";
            cout << endl;
            string res; cin >> res;
            ans[i] = res[0];
        }
    }

    cout << "! " << ans << endl;
    return 0;
}