#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define ll long long


// https://lorent-kyopro.hatenablog.com/entry/2021/03/12/025644

template <class S, S (*op)(S, S), S (*e)()> class dynamic_segtree {
    public:
        dynamic_segtree(size_t n) : n(n), root(nullptr) {}
    
        void set(size_t p, S x) {
            assert(p < n);
            set(root, 0, n, p, x);
        }
    
        S get(size_t p) const {
            assert(p < n);
            return get(root, 0, n, p);
        }
    
        S prod(size_t l, size_t r) const {
            assert(l <= r && r <= n);
            return prod(root, 0, n, l, r);
        }
    
        S all_prod() const { return root ? root->product : e(); }
    
    private:
        struct node;
        using node_ptr = std::unique_ptr<node>;
    
        struct node {
            size_t index;
            S value, product;
            node_ptr left, right;
    
            node(size_t index, S value)
                : index(index),
                  value(value),
                  product(value),
                  left(nullptr),
                  right(nullptr) {}
    
            void update() {
                product = op(op(left ? left->product : e(), value),
                             right ? right->product : e());
            }
        };
    
        const size_t n;
        node_ptr root;
    
        void set(node_ptr& t, size_t a, size_t b, size_t p, S x) const {
            if (!t) {
                t = std::make_unique<node>(p, x);
                return;
            }
            if (t->index == p) {
                t->value = x;
                t->update();
                return;
            }
            size_t c = (a + b) >> 1;
            if (p < c) {
                if (t->index < p) std::swap(t->index, p), std::swap(t->value, x);
                set(t->left, a, c, p, x);
            } else {
                if (p < t->index) std::swap(p, t->index), std::swap(x, t->value);
                set(t->right, c, b, p, x);
            }
            t->update();
        }
    
        S get(const node_ptr& t, size_t a, size_t b, size_t p) const {
            if (!t) return e();
            if (t->index == p) return t->value;
            size_t c = (a + b) >> 1;
            if (p < c) return get(t->left, a, c, p);
            else return get(t->right, c, b, p);
        }
    
        S prod(const node_ptr& t, size_t a, size_t b, size_t l, size_t r) const {
            if (!t || b <= l || r <= a) return e();
            if (l <= a && b <= r) return t->product;
            size_t c = (a + b) >> 1;
            S result = prod(t->left, a, c, l, r);
            if (l <= t->index && t->index < r) result = op(result, t->value);
            return op(result, prod(t->right, c, b, l, r));
        }
};

struct S{
    ll odd;
    ll even;
    ll cnt;
};
S op(S a, S b) {
    if(a.cnt) return {a.odd+b.even, a.even+b.odd, a.cnt^b.cnt};
    else return {a.odd+b.odd, a.even+b.even, a.cnt^b.cnt};
} 
bool f(S x){
    return 1;
}
S e() {return {0,0,0};}

int main() {
    ll q; cin >> q;
    ll m = 1e9;
    ll ans = 0;
    dynamic_segtree<S,op,e> seg(m+1);
    while(q--){
        ll y; cin >> y;
        y = (y+ans)%m+1;
        seg.set(y,op(seg.get(y),{y,0,1}));
        ans = seg.all_prod().odd;
        cout << ans << endl;
    }
    return 0;
} 