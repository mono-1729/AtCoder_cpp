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

template<typename U = unsigned, int B = 32>
class binary_trie {
    struct node {
        int cnt;
        node *ch[2];
        node() : cnt(0), ch{ nullptr, nullptr } {}
    };
    node* add(node* t, U val, int b = B - 1) {
        if (!t) t = new node;
        t->cnt += 1;
        if (b < 0) return t;
        bool f = (val >> (U)b) & (U)1;
        t->ch[f] = add(t->ch[f], val, b - 1);
        return t;
    }
    node* sub(node* t, U val, int b = B - 1) {
        assert(t);
        t->cnt -= 1;
        if (t->cnt == 0) return nullptr;
        if (b < 0) return t;
        bool f = (val >> (U)b) & (U)1;
        t->ch[f] = sub(t->ch[f], val, b - 1);
        return t;
    }
    U get_min(node* t, U val, int b = B - 1) const {
        assert(t);
        if (b < 0) return 0;
        bool f = (val >> (U)b) & (U)1; f ^= !t->ch[f];
        return get_min(t->ch[f], val, b - 1) | ((U)f << (U)b);
    }
    U get(node* t, int k, int b = B - 1) const {
        if (b < 0) return 0;
        int m = t->ch[0] ? t->ch[0]->cnt : 0;
        return k < m ? get(t->ch[0], k, b - 1) : get(t->ch[1], k - m, b - 1) | ((U)1 << (U)b);
    }
    int count_lower(node* t, U val, int b = B - 1) {
        if (!t || b < 0) return 0;
        bool f = (val >> (U)b) & (U)1;
        return (f && t->ch[0] ? t->ch[0]->cnt : 0) + count_lower(t->ch[f], val, b - 1);
    }
    node *root;
public:
    binary_trie() : root(nullptr) {}
    int size() const {
        return root ? root->cnt : 0;
    }
    bool empty() const {
        return !root;
    }
    void insert(U val) {
        root = add(root, val);
    }
    void erase(U val) {
        root = sub(root, val);
    }
    U max_element(U bias = 0) const {
        return get_min(root, ~bias);
    }
    U min_element(U bias = 0) const {
        return get_min(root, bias);
    }
    int lower_bound(U val) { // return id
        return count_lower(root, val);
    }
    int upper_bound(U val) { // return id
        return count_lower(root, val + 1);
    }
    U operator[](int k) const {
        assert(0 <= k && k < size());
        return get(root, k);
    }
    int count(U val) const {
        if (!root) return 0;
        node *t = root;
        for (int i = B - 1; i >= 0; i--) {
            t = t->ch[(val >> (U)i) & (U)1];
            if (!t) return 0;
        }
        return t->cnt;
    }
    long long cc(U x, U k) const {
        if (!root) return 0;
        node* t = root;
        long long res = 0;
        for (int i = B - 1; i >= 0; i--) {
            if (!t) break;
            int xb = (x >> i) & 1;
            int kb = (k >> i) & 1;
            if (kb == 1) {
                if(t->ch[xb]) res += t->ch[xb]->cnt;
                t = t->ch[xb ^ 1];
            }else t = t->ch[xb];
        }
        if (t) res += t->cnt;
        return res;
    }
};

class xor_set{
private:
    vector<ll> w;
public:
    xor_set () {}
    void insert(ll x) {
        for (ll v : w) {
            chmin(x, x ^ v);
        }
        if (x == 0) return;
        for (ll& v : w) {
            chmin(v, v ^ x);
        }
        w.push_back(x);
        sort(w.begin(), w.end(), greater<ll>());
    }
    ll count(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return 1;
        else return 0;
    }
    void to_msb_basis() {
        constexpr int B = 63;
        ll basis[B] = {};

        for(ll x : w){
            for (int i = B - 1; i >= 0; i--){
                if(((x >> i) & 1LL) == 0) continue;
                if(basis[i]) x ^= basis[i];
                else{
                    basis[i] = x;
                    break;
                }
            }
        }
        for(int i = 0; i < B; i++){
            if (basis[i] == 0) continue;
            for(int j = i + 1; j < B; j++){
                if((basis[j] >> i) & 1LL){
                    basis[j] ^= basis[i];
                }
            }
        }
        w.clear();
        for(int i = B - 1; i >= 0; i--){
            if(basis[i]){
                w.push_back(basis[i]);
            }
        }
    }
    vector<ll> get(){return w;}
};

int main() {
    ll t; cin >> t;
    while(t--){
        ll n, m, k; cin >> n >> m >> k;
        vector<vector<pll>> g(n);
        rep(i,0,m){
            ll u, v, w; cin >> u >> v >> w;
            u--;v--;
            g[u].push_back({v,w});
            g[v].push_back({u,w});
        } 
        binary_trie bt;
        xor_set st;
        vector<ll> check(n), num(n);
        ll now = 0;
        auto dfs = [&](auto dfs, ll v) -> void {
            check[v] = 1;
            num[v] = now;
            for(auto [nv, w]: g[v]){
                if(check[nv]) st.insert(num[v]^num[nv]^w);
                else{
                    now ^= w;
                    dfs(dfs,nv);
                    now ^= w;
                }
            }
        };
        dfs(dfs,0);
        ll ans = 0;
        st.to_msb_basis();
        rep(i,0,n){
            ll x = num[i];
            for(auto a: st.get()) chmin(x,x^a);
            ans += bt.cc(x,k);
            bt.insert(x);
        }
        cout << ans << endl;
    }
    return 0;
}