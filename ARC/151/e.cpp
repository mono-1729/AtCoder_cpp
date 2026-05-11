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
    if(b == 0) return a;
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

template< typename T >
struct SparseTable {
  vector< vector< T > > st;
  vector< int > lookup;

  SparseTable(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  inline T rmq(int l, int r) {
    int b = lookup[r - l];
    return min(st[b][l], st[b][r - (1 << b)]);
  }
};


template <class T>
struct SuffixArray {
    vector<int> SA;
    vector<T> s;

    SuffixArray() = default;

    SuffixArray(const vector<T>& v) : s(v) {
        build();
    }

    SuffixArray(const string& str) {
        s.assign(str.begin(), str.end());
        build();
    }

    void build() {
        int n = (int)s.size();
        SA.resize(n);
        iota(SA.begin(), SA.end(), 0);

        if (n == 0) return;

        vector<T> vals = s;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        vector<int> rnk(n), tmp(n);
        for (int i = 0; i < n; i++) {
            rnk[i] = std::lower_bound(vals.begin(), vals.end(), s[i]) - vals.begin() + 1;
        }

        for (int k = 1; k < n; k <<= 1) {
            auto cmp = [&](int i, int j) {
                if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];

                int ri = (i + k < n ? rnk[i + k] : 0);
                int rj = (j + k < n ? rnk[j + k] : 0);
                return ri < rj;
            };

            sort(SA.begin(), SA.end(), cmp);

            tmp[SA[0]] = 1;
            for (int i = 1; i < n; i++) {
                tmp[SA[i]] = tmp[SA[i - 1]] + (cmp(SA[i - 1], SA[i]) ? 1 : 0);
            }

            rnk.swap(tmp);

            if (rnk[SA[n - 1]] == n) break;
        }
    }

    int operator[](int k) const {
        return SA[k];
    }

    int size() const {
        return (int)SA.size();
    }

    int compare_suffix_pattern(const vector<T>& t, int si) const {
        int n = (int)s.size();
        int m = (int)t.size();

        int i = si, j = 0;
        while (i < n && j < m) {
            if (s[i] < t[j]) return -1;
            if (t[j] < s[i]) return 1;
            i++;
            j++;
        }

        if (j == m) return 0;   
        return -1;            
    }

    int lower_bound(const vector<T>& t) const {
        int low = -1, high = size();

        while (high - low > 1) {
            int mid = (low + high) / 2;

            if (compare_suffix_pattern(t, SA[mid]) < 0) {
                low = mid;
            } else {
                high = mid;
            }
        }

        return high;
    }

    int upper_bound(const vector<T>& t) const {
        int low = -1, high = size();

        while (high - low > 1) {
            int mid = (low + high) / 2;

            if (compare_suffix_pattern(t, SA[mid]) <= 0) {
                low = mid;
            } else {
                high = mid;
            }
        }

        return high;
    }

    pair<int, int> lower_upper_bound(const vector<T>& t) const {
        return {lower_bound(t), upper_bound(t)};
    }

    int lower_bound(const string& t) const {
        vector<T> v(t.begin(), t.end());
        return lower_bound(v);
    }

    int upper_bound(const string& t) const {
        vector<T> v(t.begin(), t.end());
        return upper_bound(v);
    }

    pair<int, int> lower_upper_bound(const string& t) const {
        vector<T> v(t.begin(), t.end());
        return lower_upper_bound(v);
    }

    bool contains(const vector<T>& t) const {
        auto [l, r] = lower_upper_bound(t);
        return l < r;
    }

    bool contains(const string& t) const {
        vector<T> v(t.begin(), t.end());
        return contains(v);
    }
};


// LCP[i] = i 番目と i+1 番目の共通接頭次長
template <class T>
struct LongestCommonPrefixArray {
    const SuffixArray<T>& SA;
    vector<int> LCP, rank;

    LongestCommonPrefixArray(const SuffixArray<T>& SA)
        : SA(SA), LCP(max(0, SA.size() - 1)), rank(SA.size()) {

        int n = SA.size();

        for (int i = 0; i < n; i++) {
            rank[SA[i]] = i;
        }

        for (int i = 0, h = 0; i < n; i++) {
            int r = rank[i];

            if (r + 1 < n) {
                int j = SA[r + 1];
                while (i + h < n && j + h < n && SA.s[i + h] == SA.s[j + h]) {
                    ++h;
                }
                LCP[r] = h;
                if (h > 0) --h;
            } else {
                if (h > 0) --h;
            }
        }
    }

    int operator[](int k) const {
        return LCP[k];
    }

    int size() const {
        return (int)LCP.size();
    }

    void output() const {
        for (int i = 0; i < size(); i++) {
            cout << i << ": LCP = " << LCP[i] << endl;
            cout << "  suffix SA[" << i << "] = " << SA[i] << ": ";
            for (int j = SA[i]; j < (int)SA.s.size(); j++) {
                cout << SA.s[j] << " ";
            }
            cout << endl;
            cout << "  suffix SA[" << i + 1 << "] = " << SA[i + 1] << ": ";
            for (int j = SA[i + 1]; j < (int)SA.s.size(); j++) {
                cout << SA.s[j] << " ";
            }
            cout << endl;
        }
    }
};
int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i], a[i]--;
    ll p; cin >> p;
    vector<ll> x(p);
    rep(i,0,p) cin >> x[i], x[i]--;
    ll q; cin >> q;
    vector<ll> y(q);
    rep(i,0,q) cin >> y[i], y[i]--;
    ll f = 0;
    vector<ll> c(n,0);
    {
        rep(i,0,p) c[x[i]] |= 1;
        rep(i,0,q) c[y[i]] |= 2;
        rep(i,0,n) if(c[i] == 3) f = 1;
    }
    if(f){
        vector<ll> vec;
        rep(i,0,p) vec.push_back(x[i]);
        rep(i,0,q) vec.push_back(y[i]);
        SuffixArray<ll> sa(vec);
        LongestCommonPrefixArray lcp(sa);
        SparseTable<int> st(lcp.LCP);
        ll ans = INF;
        rep(i,0,p+q-1){
            ll li = sa[i], ri = sa[i+1];
            if(inr(0,li,p) != inr(0,ri,p)){
                ll len = st.rmq(i,i+1);
                chmin(len,p);
                chmin(len,q);
                chmin(ans,p-len+q-len);
            }
        }
        cout << ans << endl;

    }else{
        ll s = n, t = n+1;
        vector<vector<pll>> g(n+2);
        rep(i,0,n){
            if(i > 0){
                g[a[i-1]].push_back({a[i],2LL});
                g[a[i]].push_back({a[i-1],2LL});
            }
            if(c[a[i]] & 1) g[s].push_back({a[i],p-1});
            if(c[a[i]] & 2) g[a[i]].push_back({t,q-1});
        }
        vector<ll> dist(n+2,INF);
        dist[s] = 0;
        priority_queue<pll,vector<pll>,greater<pll>> pq;
        pq.push({0,s});
        while(!pq.empty()){
            auto [d,v] = pq.top(); pq.pop();
            if(d > dist[v]) continue;
            for(auto [nv, cc] : g[v]){
                ll nd = d+cc;
                if(nd < dist[nv]){
                    dist[nv] = nd;
                    pq.push({nd,nv});
                }
            }
        }
        cout << dist[t] << endl;
    }
    return 0;
}