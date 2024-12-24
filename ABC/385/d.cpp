#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, n) for (int i = (s); i < (int)(n); i++)
#include <atcoder/all>
using namespace atcoder;
using mint1 = modint1000000007;
using mint2 = modint998244353;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
ld pi=3.141592653589793;
const int inf=2e9;
const ll linf=2e18;
const ld eps=1e-14;
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl

ll dx[4]={1,0,-1,0};
ll dy[4]={0,1,0,-1};

struct edge{
    ll to;
    ll leng;
};

int main() {
    //////////////////
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //////////////////

    ll n,m,sx,sy;
    cin >> n >> m >> sx >> sy;
    vector<ll> x(n),y(n),c(m);
    vector<char> d(m);
    map<ll,set<ll>> mpx,mpy;
    for(ll i=0; i<n; i++) {
        cin >> x[i] >> y[i];
        mpx[x[i]].insert(y[i]);
        mpy[y[i]].insert(x[i]);
    }
    for(ll i=0; i<m; i++) {
        cin >> d[i] >> c[i];
    }

    ll ans=0;
    for(ll i=0; i<m; i++) {
        if (d[i]=='U') {
            auto it=mpx[sx].upper_bound(sy);

            vector<ll> e;
            while (it != mpx[sx].end()) {
                if (*it>sy+c[i]) break;
                e.push_back(*it);
                ans++;
                it++;
            }
            sy+=c[i];

            for(ll j=0; j<e.size(); j++) {
                mpx[sx].erase(e[j]);
                mpy[e[j]].erase(sx);
            }
        }else if(d[i]=='D') {
            auto it=mpx[sx].lower_bound(sy);

            vector<ll> e;
            while (it != mpx[sx].begin()) {
                it--;
                if (*it<sy-c[i]) break;
                e.push_back(*it);
                ans++;
            }
            sy-=c[i];

            for(ll j=0; j<e.size(); j++) {
                mpx[sx].erase(e[j]);
                mpy[e[j]].erase(sx);
            }
        }else if(d[i]=='L') {
            auto it=mpy[sy].lower_bound(sx);

            vector<ll> e;
            while (it != mpy[sy].begin()) {
                it--;
                if (*it<sx-c[i]) break;
                e.push_back(*it);
                ans++;
            }
            sx-=c[i];

            for(ll j=0; j<e.size(); j++) {
                mpy[sy].erase(e[j]);
                mpx[e[j]].erase(sy);
            }
        }else {
            auto it=mpy[sy].upper_bound(sx);

            vector<ll> e;
            while (it != mpy[sy].end()) {
                if (*it>sx+c[i]) break;
                e.push_back(*it);
                ans++;
                it++;
            }
            sx+=c[i];

            for(ll j=0; j<e.size(); j++) {
                mpy[sy].erase(e[j]);
                mpx[e[j]].erase(sy);
            }
        }
    }
    cout << sx << " " << sy << " " << ans << endl;
}