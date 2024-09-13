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
    vector<vector<ll>> s_(h,vector<ll>(w,0)), sum(h+1,vector<ll>(w+1,0));
    vector<ll> delh(h+1,1), delw(w+1,1);
    rep(i,0,h)rep(j,0,w){
        char x; cin >> x;
        if(x == 'Y') s_[i][j]++, sum[i+1][j+1]++;
    }
    {
        ll pre = 0;
        rep(i,0,h){
            bool flg = false;
            rep(j,0,w) if(s_[i][j]) flg = true;
            if(flg) pre = i+1;
            else delh[pre]++;
        }
        delh[0] = 1;
        delh[pre] = 1;
    }
    {
        ll pre = 0;
        rep(j,0,w){
            bool flg = false;
            rep(i,0,h) if(s_[i][j]) flg = true;
            if(flg) pre = j+1;
            else delw[pre]++;
        }
        delw[0] = 1;
        delw[pre] = 1;
    }
    rep(i,0,h)rep(j,0,w+1) sum[i+1][j] += sum[i][j];
    rep(i,0,h+1)rep(j,0,w) sum[i][j+1] += sum[i][j];
    if(sum[h][w]%2 == 1 || sum[h][w] == 0){
        cout << 0 << endl;
        return 0;
    }
    ll num = sum[h][w];
    vector<pii> cand;
    rep(i,1,h+1){
        if((num/2)%i == 0 && (num/2)/i <= w) cand.push_back({i,(num/2)/i});
    }
    mint ans = 0;
    auto calc = [&](ll u, ll d, ll l, ll r) -> ll {
        return sum[d][r] - sum[u][r] - sum[d][l] + sum[u][l];
    };
    for(auto [s,t]: cand){
        mint add = 1;
        vector<ll> vec, vec2;
        ll now = 0;
        bool flg = true;
        rep(i,0,s+1){
            while(true){
                if(sum[now][w] == (num/s)*i){
                    vec.push_back(now);
                    add *= delh[now];
                    break;
                }else if(sum[now][w] > (num/s)*i){
                    flg = false;
                    break;
                }
                now++;
            }
            if(flg == false) break;
            now++;
        }
        if(flg == false) continue;
        now = 0;
        cout << endl;
        rep(i,0,t+1){
            while(true){
                if(sum[h][now] == (num/t)*i){
                    if(vec2.size()){
                        ll pre = vec2.back();
                        rep(j,0,vec.size()-1){
                            if(calc(vec[j],vec[j+1],pre,now) != 2){
                                flg = false;
                                break;
                            }
                        }
                    }
                    vec2.push_back(now);
                    add *= delw[now];
                    break;
                }else if(sum[h][now] > (num/t)*i){
                    flg = false;
                    break;
                }
                if(flg == false) break;
                now++;
            }
            if(flg == false) break;
            now++;
        }
        if(flg) ans += add;
    }
    cout << ans.val() << endl;
    return 0;
}