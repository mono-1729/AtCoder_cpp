// https://betrue12.hateblo.jp/entry/2020/09/23/005940
#include <bits/stdc++.h>
using namespace std;
#define ll long long

template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()> 
class LazySegmentTree {
    int _n, size, log;
    vector<T> d;
    vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    void all_apply(int k, F f){
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }

    void push(int k){
        all_apply(2*k, lz[k]);
        all_apply(2*k+1, lz[k]);
        lz[k] = id();
    }

public:
    LazySegmentTree() : LazySegmentTree(0) {}
    explicit LazySegmentTree(int n) : LazySegmentTree(vector<T>(n, e())) {} // explicit で明示的に型を指定する
    explicit LazySegmentTree(const vector<T> &v) : _n(int(v.size())) {
        // sizeは_nを超える最小の2のべき乗
        size = 1;
        while(size < _n) size *= 2, log++; 

        // log は木の高さ（sizeの桁数）
        log = 0;
        while (!(size & (1 << log))) log++;

        d = vector<T>(2*size, e());
        lz = vector<F>(size, id());

        for(int i = 0; i < _n; i++) d[size+i] = v[i];
        for(int i = size-1; i >= 1; i--){
            update(i);
        }
    }

    void set(int p, T x){
        assert(0 <= p && p < _n);
        p += size;
        for(int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for(int i = 1; i <= log; i++) update(p >> i);
    }

    T get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for(int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }


    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if(l == r) return e();

        l += size;
        r += size;

        for(int i = log; i >= 1; i--){
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

    void apply(int p, F f){
        assert(0 <= p && p < _n);
        p += size;
        for(int i = log; i >= 1; i--) push(p >> i); 
        d[p] = mapping(f, d[p]);
        for(int i = 1; i <= log; i++) update(p >> i);
    }

    void apply(int l, int r, F f){
        assert(0 <= l && l <= r && r <= _n);
        if(l == r) return;

        l += size;
        r += size;

        for(int i = log; i >= 1; i--){
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r-1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while(l < r){
                if(l&1) all_apply(l++, f);
                if(r&1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for(int i = 1; i <= log; i++){
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r-1) >> i);
        }
    }

    // f(op(a[l], a[l + 1], ..., a[r - 1])) = trueとなる最大のｒ
    template <bool (*g)(T)> int max_right(int l) {
        return max_right(l, [](T x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
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

    template <bool (*g)(T)> int min_left(int r) {
        return min_left(r, [](T x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
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

// 遅延セグメント木の準備
using S =  ll;
S op(S a, S b) { return min(a, b); }
S e() { return 9e18; }
// 一次関数 a x + b によって恒等写像と代入を表現
using F = ll;
S mapping(F a, S x) { return min(a, x); }
F composition(F a, F b) { return min(a, b); }
F id() { return 9e18; }


int main(){
    //LazySegmentTree<S, op, e, F, mapping, composition, id> lst(initial);
    return 0;
}

// 区間加算・区間最小値取得
// using S = long long;
// using F = long long;

// const S INF = 8e18;

// S op(S a, S b){ return std::min(a, b); }
// S e(){ return INF; }
// S mapping(F f, S x){ return f+x; }
// F composition(F f, F g){ return f+g; }
// F id(){ return 0; }

// int main(){
//     int N;
//     std::vector<S> v(N);
//     atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
// }


//区間加算・区間最大値取得
// using S = long long;
// using F = long long;

// const S INF = 8e18;

// S op(S a, S b){ return std::max(a, b); }
// S e(){ return -INF; }
// S mapping(F f, S x){ return f+x; }
// F composition(F f, F g){ return f+g; }
// F id(){ return 0; }

// int main(){
//     int N;
//     std::vector<S> v(N);
//     atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
// }

//区間加算・区間和取得
// struct S{
//     long long value;
//     int size;
// };
// using F = long long;

// S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
// S e(){ return {0, 0}; }
// S mapping(F f, S x){ return {x.value + f*x.size, x.size}; }
// F composition(F f, F g){ return f+g; }
// F id(){ return 0; }

// int main(){
//     int N;
//     std::vector<S> v(N, {0, 1});
//     atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
// }

//区間変更・区間最小値取得
// using S = long long;
// using F = long long;

// const S INF = 8e18;
// const F ID = 8e18;

// S op(S a, S b){ return std::min(a, b); }
// S e(){ return INF; }
// S mapping(F f, S x){ return (f == ID ? x : f); }
// F composition(F f, F g){ return (f == ID ? g : f); }
// F id(){ return ID; }

// int main(){
//     int N;
//     std::vector<S> v(N);
//     atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
// }

//区間変更・区間最大値取得
// using S = long long;
// using F = long long;

// const S INF = 8e18;
// const F ID = 8e18;

// S op(S a, S b){ return std::max(a, b); }
// S e(){ return -INF; }
// S mapping(F f, S x){ return (f == ID ? x : f); }
// F composition(F f, F g){ return (f == ID ? g : f); }
// F id(){ return ID; }

// int main(){
//     int N;
//     std::vector<S> v(N);
//     atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
// }

//区間変更・区間和取得
// struct S{
//     long long value;
//     int size;
// };
// using F = long long;

// const F ID = 8e18;

// S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
// S e(){ return {0, 0}; }
// S mapping(F f, S x){
//     if(f != ID) x.value = f*x.size;
//     return x;
// }
// F composition(F f, F g){ return (f == ID ? g : f); }
// F id(){ return ID; }

// int main(){
//     int N;
//     std::vector<S> v(N, {0, 1});
//     atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
// }