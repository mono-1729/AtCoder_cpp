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

template<typename T> class CHT {
private:
    struct node {
        node *left, *right;
        static const T inf = numeric_limits<T>::max();
        T a, b;
        node() : node(0, inf){}
        node(const T _a, const T _b)
            : left(nullptr), right(nullptr), a(_a), b(_b){}
        T f(const T x) const { return a * x + b; }
    };
    static void swap(node *x, node *y){
        std::swap(x->a, y->a), std::swap(x->b, y->b);
    }
    void _add_line(node *cur, node *nw, T l, T r){
        while(true){
            if(nw->f(l) < cur->f(l)) swap(cur, nw);
            if(cur->f(r - 1) <= nw->f(r - 1)) break;
            const T mid = (l + r) / 2;
            if(cur->f(mid) <= nw->f(mid)){
                if(!cur->right){
                    cur->right = new node(*nw);
                    break;
                }else{
                    cur = cur->right, l = mid;
                }
            }else{
                swap(cur, nw);
                if(!cur->left){
                    cur->left = new node(*nw);
                    break;
                }else{
                    cur = cur->left, r = mid;
                }
            }
        }
    }
    T query(node *cur, const T k, T l, T r) const {
        T ans = numeric_limits<T>::max();
        while(cur){
            ans = min(ans, cur->f(k));
            const T mid = (l + r) / 2;
            if(k < mid){
                cur = cur->left, r = mid;
            }else{
                cur = cur->right, l = mid;
            }
        }
        return ans;
    }
    void clear(node *cur){
        if(cur->left) clear(cur->left);
        if(cur->right) clear(cur->right);
        delete cur;
    }
    const T lpos, rpos;
    node *root;
public:
    CHT(const T _lpos, const T _rpos) : lpos(_lpos), rpos(_rpos), root(new node()){
        assert(lpos < rpos);
    }
    // ~CHT(){ clear(root); }
    // f(x) = a * x + b を挿入
    void add_line(const T a, const T b){
        node nw(a, b);
        return _add_line(root, &nw, lpos, rpos);
    }
    // x = k での最小値
    T query(const T k) const {
        return query(root, k, lpos, rpos);
    }
};

int main() {
    ll n, c; cin >> n >> c;
    vector<ll> h(n);
    rep(i,0,n) cin >> h[i];
    CHT<ll> cht(0,1000005);
    cht.add_line(-2*h[0],c+h[0]*h[0]);
    rep(i,1,n){
        ll cost = cht.query(h[i]);
        if(i == n-1) cout << cost+h[i]*h[i] << endl;
        cht.add_line(-2*h[i],cost+2*h[i]*h[i]+c);
    }
    return 0;
}