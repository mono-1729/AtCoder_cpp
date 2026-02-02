#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<ll> a(n);
        auto answer = [&]() -> void {
            rep(i,0,n) cout << a[a[i]]+1 << " ";
            cout << endl;
        };
        ll cnt = 0;
        ll f = 0;
        rep(i,0,n){
            cin >> a[i];
            if(a[i] != -1) a[i]--;
            else cnt++;
            if(a[i] == 0) f = 1;
        }
        if(a[0] == -1){
            rep(i,0,n) if(a[i] == -1) a[i] = 0;
            answer();
            continue;
        }
        ll ff = 0;
        rep(i,0,n){
            if(a[i] == -1){
                if(cnt == 1 && !f){
                    if(ff){
                        a[i] = 0;
                        cnt--;
                        f = 1;
                    }else{
                        pll mini = {i,i};
                        rep(j,0,n){
                            if(a[j] != -1) chmin(mini,make_pair(a[j],j));
                        }
                        a[i] = mini.second;
                    }
                }else{
                    a[i] = -2;
                    cnt--;
                    ff = 1;
                }
            }else if(a[a[i]] == -1){
                a[a[i]] = 0;
                f = 1;
                cnt--;
            }else if(a[a[i]] == -2){
                rep(j,0,n){
                    if(a[j] == -1 || a[j] == 0){
                        a[j] = 0;
                        f = 1;
                        break;
                    }
                }
            }
        }
        ll b = -1;
        rep(i,0,n){
            if(a[i] == 0){
                b = i;
                break;
            }
        }
        rep(i,0,n){
            if(a[i] == -2) a[i] = b;
        }
        answer();
    }
    return 0;
}