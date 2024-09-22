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
    ll n, m, q; cin >> n >> m >> q;
    vector<ll> num(n,0);
    rep(i,1,32){
        cout << "? " << 1 << " " << i+1 << endl;
        ll x; cin >> x;
        num[i] = x;
    }

    ll cnt_ = 0;
    rep(j,0,32) if(num[j] == 1) cnt_++;
    if(cnt_ >= 16)rep(j,0,32) num[j] = 1-num[j];

    for(int i = 32; i < n; i+=16){
        ll left = i + 16 >= n ? n-16 : i;
        vector<ll> a(16,0);
        for(int j = 0; j < 15; j++){
            cout << "? " << left + j + 1 << " " << left + j + 2 << endl;
            ll x; cin >> x;
            if(x == 0) a[j+1] = a[j];
            else a[j+1] = 1-a[j];
        }
        ll cnt = 0;
        rep(j,0,16){
            cnt += a[j];
        }
        if(cnt >= 11)rep(j,0,16) a[j] = 1-a[j];
        else if(cnt >= 6){
            cout << "? " << 1 << " " << left + 1 << endl;
            ll x; cin >> x;
            if((x == 0 && a[0] != num[0]) || (x == 1 && a[0] == num[0])){
                rep(j,0,16){
                    a[j] = 1-a[j];
                }
            }
        }
        rep(j,0,16){
            num[left+j] = a[j];
        }
    }
    cout << "! ";
    rep(i,0,n) if(num[i] == 1) cout << i+1 << " ";
    cout << endl;
    return 0;
}