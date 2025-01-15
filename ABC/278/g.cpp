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
    ll n, llen, rlen; cin >> n >> llen >> rlen;
    if(llen != rlen){
        cout << "First" << endl;
        ll p;
        if(n%2 == llen%2){
            cout << (n-llen)/2 + 1 << " " << llen << endl;
            p = (n-llen)/2 + llen;
        }
        else{
            cout << (n-llen-1)/2 + 1 << " " << llen+1 << endl;
            p = (n-llen-1)/2 + llen+1;
        }
        while(true){
            ll x, y; cin >> x >> y;
            if(x == 0 && y == 0) return 0;
            if(x <= p) cout << p+x << " " << y << endl;
            else cout << x-p << " " << y << endl;
        }
    }else{
        vector<ll> grundy(n+1);
        grundy[0] = 0;
        rep(i,1,n+1){
            unordered_map<ll,ll> mp;
            rep(left,0,i){
                if(left+llen > i) break;
                mp[grundy[left] ^ grundy[i-llen-left]] = 1;
            }
            rep(num,0,n+1){
                if(mp[num] == 0){
                    grundy[i] = num;
                    break;
                }
            }
        }
        vector<ll> field(n,1), rid(n);
        rep(i,0,n) rid[i] = n;
        ll nowg = grundy[n];
        auto myturn = [&]() {
            ll now = 0;
            while(true){
                if(now == rid[now]){
                    now++;
                    continue;
                }
                ll r = rid[now];
                ll flg = false;
                rep(l,now,r){
                    if(l+llen > r) continue;
                    if(nowg == (grundy[l-now] ^ grundy[r-now-llen-(l-now)] ^ grundy[r-now])){
                        cout << l+1 << " " << llen << endl;
                        rep(p,l,l+llen) field[p] = 0;
                        flg = true;
                        break;
                    }
                }
                if(flg) break;
                now = r;
            }
        };
        auto opturn = [&]() {
            ll x, y; cin >> x >> y;
            if(x == 0 && y == 0) return false;
            x--;
            rep(i,x,x+y) field[i] = 0;
            ll now = 0;
            nowg = 0;
            while(now < n){
                if(field[now] == 0){
                    rid[now] = now;
                    now++;
                    continue;
                }
                ll r = now;
                while(r < n && field[r] == 1) r++;
                nowg ^= grundy[r-now];
                rep(p,now,r) rid[p] = r;
                now = r;
            }
            return true;
        };
        if(grundy[n] == 0) cout << "Second" << endl;
        else {
            cout << "First" << endl;
            myturn();
        }
        while(opturn()) myturn();

    }
    return 0;
}