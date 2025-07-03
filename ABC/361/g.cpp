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
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

struct Row{
    ll l, r, id;
    Row(ll l, ll r, ll id):  l(l), r(r), id(id){}
    ll in(Row a){
        return max(l, a.l) <= min(r,a.r);
    }
};

int main() {
    ll n; cin >> n;
    ll m = 200005;
    vector<vector<ll>> field(m);
    rep(i,0,n){
        ll x, y; cin >> x >> y;
        field[x+1].push_back(y+1);
    }
    vector<vector<Row>> rows(m);
    vector<Row> vec;
    ll ans = 0;
    ll cnt = 0;
    rep(i,0,m){
        sort(all(field[i]));
        if(field[i].empty()){
            rows[i].push_back(Row(0,m,cnt++));
            for(auto row: rows[i]) vec.push_back(row);
            continue;
        }
        rows[i].push_back(Row(0,field[i][0]-1,cnt++));
        rep(j,0,field[i].size()-1){
            if(field[i][j]+1 < field[i][j+1]) rows[i].push_back(Row(field[i][j]+1,field[i][j+1]-1,cnt++));
        }
        rows[i].push_back(Row(field[i].back()+1,m,cnt++));
        for(auto row: rows[i]) vec.push_back(row);
    }
    vector<vector<ll>> g(cnt);
    rep(i,0,m-1){
        ll l = -1, r = 0;
        ll k = rows[i+1].size();
        for(auto row: rows[i]){
            l = max(r-1,0LL);
            while(l < k && rows[i+1][l].r < row.l) l++;
            r = l;
            while(r < k && row.in(rows[i+1][r])) r++;
            rep(id,l,r){
                g[row.id].push_back(rows[i+1][id].id);
                g[rows[i+1][id].id].push_back(row.id);
            }
        }
    }
    rep(i,0,m)for(auto row: rows[i]) ans += row.r-row.l+1;
    queue<ll> q;
    vector<ll> check(cnt);
    q.push(0);
    check[0] = 1;
    while(!q.empty()){
        ll id = q.front(); q.pop();
        ans -= vec[id].r-vec[id].l+1;
        for(auto nv: g[id]){
            if(!check[nv]){
                check[nv] = 1;
                q.push(nv);
            }
        }
    }
    cout << ans << endl;
    return 0;
}