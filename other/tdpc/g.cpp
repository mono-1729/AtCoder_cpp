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

int main() {
    string s; cin >> s;
    ll n = s.size();
    ll k; cin >> k, k++;
    vector<ll> num(n+1);
    vector<vector<ll>> next(n+1,vector<ll>(26,INF));
    rep(i,0,n) next[i][s[i]-'a'] = i;
    rep(j,0,26)rrep(i,n-1,0) chmin(next[i][j],next[i+1][j]);
    
    rrep(i,n,0){
        num[i] = 1;
        rep(j,0,26){
            ll nxt = next[i][j];
            if(nxt != INF){
                num[i] += num[nxt+1];
                chmin(num[i],INF);
            }
        }
    }

    string ans = "";
    ll now = 0;
    while(true){
        k--;
        if(k == 0) break;
        // cout << now << " " << k << endl;
        ll nxt = -1;
        rep(j,0,26){
            ll id = next[now][j];
            if(id != INF){
                // cout << now << " " << id << " " << num[id] << endl;
                id++;
                if(num[id] < k) k -= num[id];
                else{
                    nxt = id;
                    ans.push_back(s[id-1]);
                    break;
                }
            }
        }
        if(nxt == -1){
            cout << "Eel" << endl;
            return 0;
        }
        now = nxt;
    }
    cout << ans << endl;
    return 0;
}