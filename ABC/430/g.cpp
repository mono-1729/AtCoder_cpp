#include <bits/stdc++.h>
using namespace std;

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
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

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
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

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) {
            lz[k] = composition(f, lz[k]);
            if (d[k].fail) push(k), update(k);
        }
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

} // namespace atcoder

// ===== 問題用 SegmentTreeBeats (fail版) =====

static inline uint64_t BIT(int x){ return 1ULL << (x-1); } // x in [1,60]

struct S {
    int mx;        // popcount 最大
    int cnt_mx;    // mx の個数
    int len;       // 区間長
    uint64_t andm; // 区間のマスク AND
    uint64_t orm;  // 区間のマスク OR
    bool fail;     // mapping 失敗フラグ
};

struct F {
    uint64_t set1; // このbitを1にする（OR）
    uint64_t set0; // このbitを0にする（AND）
};

// op: 区間結合
S op(S a, S b){
    if(a.len == 0) return b;
    if(b.len == 0) return a;
    S r;
    r.len = a.len + b.len;
    r.andm = a.andm & b.andm;
    r.orm  = a.orm  | b.orm;
    r.mx = max(a.mx, b.mx);
    r.cnt_mx = 0;
    if(a.mx == r.mx) r.cnt_mx += a.cnt_mx;
    if(b.mx == r.mx) r.cnt_mx += b.cnt_mx;
    r.fail = false;
    return r;
}

// e: 単位元
S e(){
    return S{INT_MIN/4, 0, 0, ~0ULL, 0ULL, false};
}

// composition: f∘g（先にg、その後f）
// 強制は後勝ち。disjoint を保つように整理する。
F composition(F f, F g){
    // まず g を残しつつ、f の指定で上書き
    uint64_t res1 = (g.set1 & ~f.set0) | f.set1;
    uint64_t res0 = (g.set0 & ~f.set1) | f.set0;
    // 念のため disjoint 化（理屈上は不要だが安全）
    res1 &= ~res0;
    res0 &= ~res1;
    return F{res1, res0};
}

F id(){ return F{0ULL, 0ULL}; }

// mapping: 区間に f を適用できるならまとめて適用、混在bitが必要なら fail
S mapping(F f, S x){
    if(x.len == 0) return x;
    x.fail = false;

    // 混在しているbit集合 = (OR=1) かつ (AND=0)
    uint64_t mixed = x.orm & ~x.andm;

    // 混在bitを 1 に/0 にしようとしたら、このノードでは処理不能 → fail
    if ((f.set1 & mixed) || (f.set0 & mixed)) {
        x.fail = true;
        return x;
    }

    // ここまで来たら、各 bit は「全0」か「全1」かのどちらかなので一括でOK
    // set1 で変化するのは「全0」のbit（= ORに含まれていないbit）
    uint64_t to1 = f.set1 & ~x.orm;
    // set0 で変化するのは「全1」のbit（= ANDに含まれているbit）
    uint64_t to0 = f.set0 & x.andm;

    int delta = __builtin_popcountll(to1) - __builtin_popcountll(to0);
    x.mx += delta;
    // 区間一様に +delta なので cnt_mx は変わらない

    // mask を更新（強制なので AND/OR とも確定的に更新できる）
    x.andm |= f.set1;
    x.orm  |= f.set1;
    x.andm &= ~f.set0;
    x.orm  &= ~f.set0;

    return x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    // 初期：全て空集合（mask=0, popcount=0）
    vector<S> init(N);
    for(int i=0;i<N;i++){
        init[i] = S{0, 1, 1, 0ULL, 0ULL, false};
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);

    while(Q--){
        int t; cin >> t;
        if(t == 1){
            int L,R,x; cin >> L >> R >> x;
            seg.apply(L-1, R, F{BIT(x), 0ULL});
        }else if(t == 2){
            int L,R,x; cin >> L >> R >> x;
            seg.apply(L-1, R, F{0ULL, BIT(x)});
        }else{
            int L,R; cin >> L >> R;
            auto ans = seg.prod(L-1, R);
            cout << ans.mx << " " << ans.cnt_mx << "\n";
        }
    }
    return 0;
}

