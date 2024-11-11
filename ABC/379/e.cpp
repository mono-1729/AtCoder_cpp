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

template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()> 
class LazySegmentTree {
    ll _n, size, log;
    vector<T> d;
    vector<F> lz;

    void update(ll k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    void all_apply(ll k, F f){
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }

    void push(ll k){
        all_apply(2*k, lz[k]);
        all_apply(2*k+1, lz[k]);
        lz[k] = id();
    }

public:
    LazySegmentTree() : LazySegmentTree(0) {}
    explicit LazySegmentTree(ll n) : LazySegmentTree(vector<T>(n, e())) {} // explicit で明示的に型を指定する
    explicit LazySegmentTree(const vector<T> &v) : _n(int(v.size())) {
        // sizeは_nを超える最小の2のべき乗
        size = 1;
        while(size < _n) size *= 2, log++; 

        // log は木の高さ（sizeの桁数）
        log = 0;
        while (!(size & (1 << log))) log++;

        d = vector<T>(2*size, e());
        lz = vector<F>(size, id());

        for(ll i = 0; i < _n; i++) d[size+i] = v[i];
        for(ll i = size-1; i >= 1; i--){
            update(i);
        }
    }

    void set(ll p, T x){
        assert(0 <= p && p < _n);
        p += size;
        for(ll i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for(ll i = 1; i <= log; i++) update(p >> i);
    }

    T get(ll p) {
        assert(0 <= p && p < _n);
        p += size;
        for(ll i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }


    T prod(ll l, ll r) {
        assert(0 <= l && l <= r && r <= _n);
        if(l == r) return e();

        l += size;
        r += size;

        for(ll i = log; i >= 1; i--){
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r-1) >> i);
        }
        
        T sml = e(), smr = e();
        while(l < r){
            if(l&1) sml = op(sml, d[l++]);
            if(r&1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    T all_prod() {return d[1]; }

    void apply(ll p, F f){
        assert(0 <= p && p < _n);
        p += size;
        for(ll i = log; i >= 1; i--) push(p >> i); 
        d[p] = mapping(f, d[p]);
        for(ll i = 1; i <= log; i++) update(p >> i);
    }

    void apply(ll l, ll r, F f){
        assert(0 <= l && l <= r && r <= _n);
        if(l == r) return;

        l += size;
        r += size;

        for(ll i = log; i >= 1; i--){
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r-1) >> i);
        }

        {
            ll l2 = l, r2 = r;
            while(l < r){
                if(l&1) all_apply(l++, f);
                if(r&1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for(ll i = 1; i <= log; i++){
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r-1) >> i);
        }
    }

    // f(op(a[l], a[l + 1], ..., a[r - 1])) = trueとなる最大のｒ
    template <bool (*g)(T)> ll max_right(ll l) {
        return max_right(l, [](T x) { return g(x); });
    }
    template <class G> ll max_right(ll l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (ll i = log; i >= 1; i--) push(l >> i);
        T sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // f(op(a[l], a[l + 1], ..., a[r - 1])) = trueとなる最小のl
    template <bool (*g)(T)> ll min_left(ll r) {
        return min_left(r, [](T x) { return g(x); });
    }
    template <class G> ll min_left(ll r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (ll i = log; i >= 1; i--) push((r - 1) >> i);
        T sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

//区間加算・区間最大値取得
using S = long long;
using F = long long;

S op(S a, S b){ return std::max(a, b); }
S e(){ return 0; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }
// ll n;
// vector<S> v(n);
// LazySegmentTree<S, op, e, F, mapping, composition, id> seg(v);

int main() {
    ll n; cin >> n;
    string s; cin >> s;
    vector<S> v(n, 0);
    LazySegmentTree<S, op, e, F, mapping, composition, id> seg(v);
    rep(i,0,n){
        ll num = (i+1LL)*(s[i] - '0');
        seg.apply(0, n-i, num);
    }
    vector<ll> ans(n+1);
    rep(i,0,n) ans[i] = seg.get(i);
    rep(i,0,n){
        if(ans[i] >= 10){
            ll num = ans[i]/10;
            ans[i] %= 10;
            ans[i+1] += num;
        }
    }
    while(ans.back() >= 10){
        ll num = ans.back()/10;
        ans.back() %= 10;
        ans.push_back(num);
    }
    if(ans.back() == 0) ans.pop_back();
    rrep(i,ans.size()-1,0) cout << ans[i];
    cout << endl;
    return 0;
}