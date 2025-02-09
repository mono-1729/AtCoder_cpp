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
    string s; cin >> s;
    vector<vector<mint>> powm(1000, vector<mint>(m+1));
    vector<vector<ll>> type(n+1, vector<ll>(n+2, 0));
    rep(i,0,n+1){
        rep(j,i,n+2){
            unordered_set<ll> st;
            rep(k,i,min(j,n)){
                st.insert(s[k]-'a');
            }
            type[i][j] = st.size();
        }
    }
    rep(i,0,1000){
        powm[i][0] = 1;
        rep(j,1,m+1){
            powm[i][j] = powm[i][j-1] * i;
        }
    }
    vector<ll> num(n+1, 0);
    vector<mint> ans(n+1, 0);
    auto dfs = [&](auto &dfs, ll idx, ll cnt) -> void {
        if(idx == n){
            ll now = 0;
            ll sum = 0;
            ll base = 0;
            rep(i,0,n+1){
                ll next = now+num[i];
                if(i != 0)sum += 26 - type[now+1][next+1];
                else sum += 26 - type[now][next+1];
                now = next;
                if(now == n){
                    base = i;
                    break;
                }
            }
            if(cnt == n-1){
                base = n;
            }
            for(auto x : num) cout << x << " ";
            cout << endl;
            cout << base << " " << sum << endl;
            ans[base] += powm[sum][m-base];
            return;
        }
        if(cnt == n){
            num[idx] = 0;
            dfs(dfs, idx+1, cnt);
        }else{
            if(idx == 0){
                rep(i,0,n-cnt+1){
                    num[idx] = i;
                    dfs(dfs, idx+1, cnt+i);
                }
            }else{
                rep(i,1,n-cnt+1){
                    num[idx] = i;
                    dfs(dfs, idx+1, cnt+i);
                }
            }
            
        }
    };
    dfs(dfs, 0, 0);
    for(auto x : ans) cout << x.val() << " ";
    cout << endl;
    return 0;
}