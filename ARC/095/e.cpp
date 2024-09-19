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
    ll h, w; cin >> h >> w;
    vector<string> s(h);
    rep(i,0,h) cin >> s[i];
    vector<ll> use(w,0);
    auto solve = [&](auto solve, vector<pll> vec) -> ll {
        if(vec.size() < (w+1)/2){
            if(vec.size() == 0 && w%2 == 1){
                rep(i,0,w){
                    use[i] = 1;
                    vec.push_back({i,i});
                    if(solve(solve, vec)) return 1;
                    vec.pop_back();
                    use[i] = 0;
                }
                return 0;
            }
            ll mini = -1;
            rep(i,0,w){
                if(use[i] == 0){
                    if(mini == -1) mini = i;
                    else{
                        use[mini] = 1;
                        use[i] = 1;
                        vec.push_back({mini,i});
                        if(solve(solve, vec)) return 1;
                        vec.pop_back();
                        use[mini] = 0;
                        use[i] = 0;
                    }
                }
            }
            return 0;
        }

        vector<string> t(h,""), rev(h,"");
        rep(i,0,h){
            for(auto [a,b]: vec){
                t[i].push_back(s[i][a]);
                rev[i].push_back(s[i][b]);
            }
            rrep(j,vec.size()-1,0){
                auto [a, b] = vec[j];
                t[i].push_back(s[i][b]);
                rev[i].push_back(s[i][a]);
            }
        }
        unordered_map<string, ll> mp;
        rep(j,0,h) mp[t[j]]++;

        // cout << "--------------------------------------" << endl;
        // rep(j,0,h) cout << t[j] << endl;

        if(h%2 == 0){
            bool flg = 1;
            rep(j,0,h){
                if(t[j] == rev[j] && mp[t[j]]%2 != 0) flg = 0;
                if(t[j] != rev[j] && mp[t[j]] != mp[rev[j]]) flg = 0;
            }
            if(flg) return 1;
        }else{
            rep(i,0,h){
                if(t[i] == rev[i]){
                    bool flg = true;
                    mp[t[i]]--;
                    rep(j,0,h){
                        if((t[j] == rev[j] && mp[t[j]]%2 != 0) || (t[j] != rev[j] && mp[t[j]] != mp[rev[j]])){
                            flg = false;
                            break;
                        }
                    }
                    if(flg) return 1;
                    mp[t[i]]++;
                }
            }
        }
        if(w%2 == 1) vec.pop_back();
        return 0;
    };
    if(solve(solve, {})) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}