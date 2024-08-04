#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
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
    int n, m; cin >> n >> m;
    vector<vector<int>> time(n);
    vector<pii> tp(m);
    rep(i,0,m){
        int t, p; cin >> t >> p;
        p--;
        time[p].push_back(t);
        tp[i] = {t, p};
    }
    int border = 500;
    unordered_map<int, int> bigidx,rev;
    int cnt = 0;
    rep(i,0,n){
        if(time[i].size() >= border){
            bigidx[i] = cnt++;
            rev[bigidx[i]] = i;
        }
    }
    vector<vector<int>> memo(cnt, vector<int>(n, 0));
    rep(i,0,n){
        if(time[i].size() < border) continue;
        vector<int> sum(m+1, 0);
        int f = 0, pre = 0;
        rep(j,0,m){
            if(f) sum[j+1] = tp[j].first - pre;
            if(tp[j].second == i){
                f = 1 - f;
            }
            pre = tp[j].first;
        }
        rep(j,0,m){
            sum[j+1] = sum[j] + sum[j+1];
        }
        vector<int> pr(n, 0), flg(n, 0);
        rep(j,0,m){
            auto [t, p] = tp[j];
            if(flg[p]){
                memo[bigidx[i]][p] += sum[j+1] - sum[pr[p]];
            }
            flg[p] = 1 - flg[p];
            pr[p] = j+1;
        }
    }
    int q; cin >> q;
    rep(i,0,q){
        int a, b; cin >> a >> b;
        a--;
        b--;
        if(time[a].size() >= border){
            cout << memo[bigidx[a]][b] << endl;
            continue;
        }
        if(time[b].size() >= border){
            cout << memo[bigidx[b]][a] << endl;
            continue;
        }
        int ans = 0;
        int pre = 0;
        int fa = 0, fb = 0;
        int idxa = 0, idxb = 0;
        while(idxa < time[a].size() || idxb < time[b].size()){
            if(idxa == time[a].size()){
                if(fa && fb) ans += time[b][idxb] - pre;
                pre = time[b][idxb];
                idxb++;
                fb = 1 - fb;
            }else if(idxb == time[b].size()){
                if(fa && fb) ans += time[a][idxa] - pre;
                pre = time[a][idxa];
                idxa++;
                fa = 1 - fa;
            }else if(time[a][idxa] < time[b][idxb]){
                if(fa && fb) ans += time[a][idxa] - pre;
                pre = time[a][idxa];
                idxa++;
                fa = 1 - fa;
            }else{
                if(fa && fb) ans += time[b][idxb] - pre;
                pre = time[b][idxb];
                idxb++;
                fb = 1 - fb;
            }
        }
        cout << ans << endl;
    }
    return 0;
}