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

using S = long long;
S op(S a, S b) {
    return min(a,b);
} 
bool f(S x){
    return 1;
}
S e() {return INF;}

template< typename T >
struct SparseTable {
  vector< vector< T > > st, st2;
  vector< int > lookup;

  SparseTable(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    st2.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
      st2[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        st2[i][j] = min(st2[i - 1][j], st2[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  inline T rmq(int l, int r) {
    int b = lookup[r - l];
    return max(st[b][l], st[b][r - (1 << b)]);
  }
  inline T rmiq(int l, int r) {
    int b = lookup[r - l];
    return min(st2[b][l], st2[b][r - (1 << b)]);
  }
};


int main() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    vector<pll> ai(n);
    rep(i,0,n) cin >> a[i], ai[i] = {a[i],-i};
    SparseTable<pll> st(ai);
    vector<ll> ans(q,INF), l(q), r(q);
    rep(i,0,q){
        cin >> l[i] >> r[i];
        l[i]--;
        chmin(ans[i],a[l[i]]+a[r[i]-1]+st.rmq(l[i]+1,r[i]-1).first);
        chmin(ans[i],a[l[i]]+a[l[i]+1]+st.rmq(l[i]+2,r[i]).first);
        chmin(ans[i],a[r[i]-2]+a[r[i]-1]+st.rmq(l[i],r[i]-2).first);
    }
    rep(_,0,2){
        // for(auto x: ans) cout << x << " ";
        // cout << endl;
        vector<vector<ll>> query(n);
        rep(i,0,q) query[r[i]-1].push_back(i);
        segtree<S,op,e> seg(n);
        vector<ll> stk{-1};
        rep(i,0,n){
            ll j = stk.back();
            while(j >= 0 && a[j] < a[i]){
                stk.pop_back();
                seg.set(j,INF);
                j = stk.back();
            }
            if(j >= 0 && j+1 < i) seg.set(i,a[i]+st.rmiq(j+1,i).first);
            stk.push_back(i);
            for(auto id: query[i]){
                auto [x,left] = st.rmq(l[id],r[id]);
                left = -left;
                if(left+2 < r[id]) chmin(ans[id],x+seg.prod(left+2,r[id]));
            }
        }
        reverse(all(a));
        rep(i,0,n/2) swap(ai[i].first,ai[n-i-1].first);
        st = SparseTable<pll>(ai);
        rep(i,0,q){
            ll nl = n-r[i], nr = n-l[i];
            l[i] = nl, r[i] = nr;
        }
    }
    for(auto x: ans) cout << x << endl;
    return 0;
}