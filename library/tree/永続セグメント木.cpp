#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

// https://ei1333.github.io/library/structure/segment-tree/persistent-segment-tree.hpp.html
// https://atcoder.jp/contests/abc453/tasks/abc453_g

// https://atcoder.jp/contests/abc453/submissions/74928562
// ↑二分探索もあるよ！
template <typename S2, typename Op, typename E>
struct LambdaMonoid {
    using S = S2;
    S op(const S& a, const S& b) const { return _op(a, b); }
    S e() const { return _e(); }
    LambdaMonoid(Op _op, E _e) : _op(_op), _e(_e) {}

    private:
    Op _op;
    E _e;
};

template <typename Op, typename E>
LambdaMonoid(Op _op, E _e) -> LambdaMonoid<decltype(_e()), Op, E>;

template <typename Monoid>
struct PersistentSegmentTree {
    using S = typename Monoid::S;
    struct Node {
        S d;
        Node *l, *r;
    };
    using NP = Node*;

private:
    int n{};
    Monoid m;

    NP merge(NP l, NP r) const { return new Node{m.op(l->d, r->d), l, r}; }

    NP build(int l, int r, const vector<S>& v) const {
        if (l + 1 == r) return new Node{v[l], nullptr, nullptr};
        NP lp = build(l, (l + r) / 2, v);
        NP rp = build((l + r) / 2, r, v);
        return merge(lp, rp);
    }

    NP set(int a, const S& x, NP k, int l, int r) const {
        if (r <= a || a + 1 <= l) {
            return k;
        } else if (a <= l && r <= a + 1) {
            return new Node{x, nullptr, nullptr};
        } else {
            return merge(set(a, x, k->l, l, (l + r) >> 1),
                         set(a, x, k->r, (l + r) >> 1, r));
        }
    }

    NP apply(int a, const S& x, NP k, int l, int r) const {
        if (r <= a || a + 1 <= l) {
            return k;
        } else if (a <= l && r <= a + 1) {
            return new Node{m.op(k->d, x), nullptr, nullptr};
        } else {
            return merge(apply(a, x, k->l, l, (l + r) >> 1),
                         apply(a, x, k->r, (l + r) >> 1, r));
        }
    }

    S prod(int a, int b, NP k, int l, int r) const {
        if (r <= a || b <= l) {
            return m.e();
        } else if (a <= l && r <= b) {
            return k->d;
        } else {
            return m.op(prod(a, b, k->l, l, (l + r) >> 1),
                        prod(a, b, k->r, (l + r) >> 1, r));
        }
    }

 
public:
    PersistentSegmentTree() = default;

    explicit PersistentSegmentTree(Monoid m, int n) : m(m), n(n) {}

    NP build(const vector<S>& v) const {
        assert(n == (int)v.size());
        return build(0, n, v);
    }

    NP set(NP t, int k, const S& x) const { return set(k, x, t, 0, n); }

    S get(NP t, int k) const {
        int l = 0, r = n;
        while (l + 1 < r) {
            int p = (l + r) / 2;
            if (k < p) {
            t = t->l;
            r = p;
            } else {
            t = t->r;
            l = p;
            }
        }
        return t->d;
    }

    NP apply(NP t, int k, const S& x) const { return apply(k, x, t, 0, n); }

    S prod(NP t, int a, int b) const { return prod(a, b, t, 0, n); }

    S all_prod(NP t) const { return t->d; }
};

int main() {
    ll n, m, q; cin >> n >> m >> q;
    auto f = [](ll a, ll b) { return a + b; };
    auto e = []() { return 0ll; };
    auto monoid = LambdaMonoid(f, e);
    PersistentSegmentTree  seg(monoid, m);
    // segv[i]: バージョンiのセグ木
    vector< decltype(seg)::NP > segv(n);

    segv[0] = seg.build(vector<ll>(m,0));
    rep(i,1,n) segv[i] = segv[0];

    while(q--){
        ll t; cin >> t;
        if(t == 1){
            ll x, y; cin >> x >> y;
            x--;y--;
            segv[x] = segv[y];
        }
        if(t == 2){
            ll x, y, z; cin >> x >> y >> z;
            x--;y--;
            segv[x] = seg.set(segv[x],y,z);
        }
        if(t == 3){
            ll x, y, z; cin >> x >> y >> z;
            x--;y--;
            cout << seg.prod(segv[x],y,z) << endl;
        }
    }
}