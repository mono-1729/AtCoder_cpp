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

struct merge_sort_tree {
    struct Data {
        int cnt = 0;
        ll sum = 0;
        Data& operator+=(const Data& rhs) {
            cnt += rhs.cnt;
            sum += rhs.sum;
            return *this;
        }
    };

    int M = 0, S = 1;
    vector<ll> val;

private:
    int D = 0, NODE = 1, LEAF = 0;
    vector<int> level_off, branch;
    vector<vector<int>> cand;
    vector<int> len, item_off, fw_off, up;
    vector<int> leaf_off, leaf_pos, root_pos;
    vector<int> bit_cnt;
    vector<ll> bit_sum;
    vector<int> edge_bit_off, edge_pref_off, edge_pref;
    vector<uint64_t> edge_bits;
    vector<int> hash_slot;
    int hash_mask = 0;
    bool root_dense = false;
    int root_first = 0;

    mutable uint64_t version = 0, cache_version = ~0ULL;
    mutable int cache_l = 0, cache_r = 0, cache_L = 0, cache_R = 0;
    mutable ll cache_sum = 0;

    static uint64_t mix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    void make_hash() {
        int z = 1;
        while (z < max(2, 2 * M)) z <<= 1;
        hash_slot.assign(z, -1);
        hash_mask = z - 1;
        for (int i = 0; i < M; i++) {
            int h = (int)(mix64((uint64_t)val[i]) & hash_mask);
            while (hash_slot[h] != -1) h = (h + 1) & hash_mask;
            hash_slot[h] = i;
        }
    }

    static void merge2(const vector<int>& a, const vector<int>& b, vector<int>& c) {
        c.clear();
        c.reserve(a.size() + b.size());
        int i = 0, j = 0;
        while (i < (int)a.size() && j < (int)b.size()) {
            if (a[i] < b[j]) c.push_back(a[i++]);
            else if (b[j] < a[i]) c.push_back(b[j++]);
            else c.push_back(a[i]), ++i, ++j;
        }
        c.insert(c.end(), a.begin() + i, a.end());
        c.insert(c.end(), b.begin() + j, b.end());
    }

    int level_size(int d) const {
        return d == D ? S : level_off[d + 1] - level_off[d];
    }

    inline int child_base(int v, int d) const {
        return level_off[d + 1] + (v - level_off[d]) * branch[d];
    }

    inline int parent_of(int v, int d) const {
        return level_off[d - 1] + (v - level_off[d]) / branch[d - 1];
    }

    inline int child_rank(int child, int parent, int p) const {
        if (p <= 0 || len[child] == 0) return 0;
        if (p >= len[parent]) return len[child];
        int w = p >> 6, b = p & 63;
        uint64_t mask = b ? (1ULL << b) - 1 : 0;
        return edge_pref[edge_pref_off[child] + w]
             + __builtin_popcountll(edge_bits[edge_bit_off[child] + w] & mask);
    }

    inline void add_node(int v, int p, int dc, ll ds) {
        int n = len[v], base = fw_off[v];
        for (int i = p + 1; i <= n; i += i & -i) {
            bit_cnt[base + i] += dc;
            bit_sum[base + i] += ds;
        }
    }

    inline void add_node_sum(int v, int p, ll ds) {
        int n = len[v], base = fw_off[v];
        for (int i = p + 1; i <= n; i += i & -i) bit_sum[base + i] += ds;
    }

    inline int prefix_count_node(int v, int p) const {
        const int* bit = bit_cnt.data() + fw_off[v];
        int ret = 0;
        for (int i = p; i; i -= i & -i) ret += bit[i];
        return ret;
    }

    inline ll prefix_sum_node(int v, int p) const {
        const ll* bit = bit_sum.data() + fw_off[v];
        ll ret = 0;
        for (int i = p; i; i -= i & -i) ret += bit[i];
        return ret;
    }

    inline int range_count_idx(int v, int l, int r) const {
        return prefix_count_node(v, r) - prefix_count_node(v, l);
    }

    inline ll range_sum_idx(int v, int l, int r) const {
        return prefix_sum_node(v, r) - prefix_sum_node(v, l);
    }

    inline int root_bound(int p) const {
        if (root_dense) {
            if (p <= root_first) return 0;
            int d = p - root_first;
            return d >= len[1] ? len[1] : d;
        }
        return lower_bound(root_pos.begin(), root_pos.end(), p) - root_pos.begin();
    }

    inline int leaf_index(int rank, int position) const {
        int b = leaf_off[rank], e = leaf_off[rank + 1];
        auto it = lower_bound(leaf_pos.begin() + b, leaf_pos.begin() + e, position);
        return (int)(it - (leaf_pos.begin() + b));
    }

    void modify_rank(int rank, int position, int delta) {
        int v = LEAF + rank, p = leaf_index(rank, position);
        ll ds = (ll)delta * val[rank];
        for (int d = D;; --d) {
            add_node(v, p, delta, ds);
            if (d == 0) break;
            p = up[item_off[v] + p];
            v = parent_of(v, d);
        }
        ++version;
    }

    template<bool Sum>
    auto value_prefix(int p, int L, int R) const {
        using T = conditional_t<Sum, ll, int>;
        if (p <= 0 || L >= R) return T(0);
        if (p >= M) {
            if constexpr (Sum) return T(range_sum_idx(1, L, R));
            else return T(range_count_idx(1, L, R));
        }

        T ret = 0;
        int v = 1, lo = 0, span = S;
        for (int d = 0; d < D && L < R && lo < p; d++) {
            int b = branch[d], sub = span / b, t = (p - lo) / sub;
            if (t >= b) t = b - 1;
            int cb = child_base(v, d);
            for (int j = 0; j < t; j++) {
                int ch = cb + j;
                int a = child_rank(ch, v, L), z = child_rank(ch, v, R);
                if constexpr (Sum) ret += range_sum_idx(ch, a, z);
                else ret += range_count_idx(ch, a, z);
            }
            int ch = cb + t;
            L = child_rank(ch, v, L);
            R = child_rank(ch, v, R);
            v = ch;
            lo += t * sub;
            span = sub;
        }
        if (L < R && lo < p) {
            if constexpr (Sum) ret += range_sum_idx(v, L, R);
            else ret += range_count_idx(v, L, R);
        }
        return ret;
    }

public:
    merge_sort_tree() = default;

    merge_sort_tree(vector<ll> vals) {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        val = move(vals);
        M = (int)val.size();

        int H = 0;
        while (S < M) S <<= 1, ++H;
        D = (H + 1) / 2;
        branch.assign(D, 4);
        if (H & 1) branch[0] = 2;

        level_off.assign(D + 1, 0);
        level_off[0] = 1;
        int width = 1;
        for (int d = 0; d < D; d++) {
            level_off[d + 1] = level_off[d] + width;
            width *= branch[d];
        }
        LEAF = level_off[D];
        NODE = LEAF + S;
        cand.resize(M);
        make_hash();
    }

    int rank_of(ll value) const {
        int h = (int)(mix64((uint64_t)value) & hash_mask);
        while (true) {
            int p = hash_slot[h];
            if (p == -1) {
                assert(false);
                return -1;
            }
            if (val[p] == value) return p;
            h = (h + 1) & hash_mask;
        }
    }

    void add_candidate(ll value, int position) {
        cand[rank_of(value)].push_back(position);
    }

    void build() {
        vector<vector<int>> xs(NODE);
        for (int r = 0; r < M; r++) {
            auto& a = cand[r];
            sort(a.begin(), a.end());
            a.erase(unique(a.begin(), a.end()), a.end());
            xs[LEAF + r] = move(a);
        }

        vector<int> t1, t2;
        for (int d = D - 1; d >= 0; d--) {
            int b = branch[d], width = level_size(d);
            for (int k = 0; k < width; k++) {
                int v = level_off[d] + k;
                int cb = level_off[d + 1] + k * b;
                if (b == 2) {
                    merge2(xs[cb], xs[cb + 1], xs[v]);
                } else {
                    merge2(xs[cb], xs[cb + 1], t1);
                    merge2(xs[cb + 2], xs[cb + 3], t2);
                    merge2(t1, t2, xs[v]);
                }
            }
        }

        len.assign(NODE, 0);
        item_off.assign(NODE, 0);
        fw_off.assign(NODE, 0);
        int items = 0, fw = 0;
        for (int v = 0; v < NODE; v++) {
            len[v] = (int)xs[v].size();
            item_off[v] = items;
            items += len[v];
            fw_off[v] = fw;
            if (len[v]) fw += len[v] + 1;
        }
        up.assign(items, -1);

        edge_bit_off.assign(NODE, -1);
        edge_pref_off.assign(NODE, -1);
        vector<int> words(NODE, 0);
        size_t total_words = 0, total_pref = 0;
        for (int d = 1; d <= D; d++) {
            int width = level_size(d);
            for (int k = 0; k < width; k++) {
                int v = level_off[d] + k;
                if (!len[v]) continue;
                int pa = parent_of(v, d);
                int w = (len[pa] + 63) >> 6;
                words[v] = w;
                edge_bit_off[v] = (int)total_words;
                total_words += w;
                edge_pref_off[v] = (int)total_pref;
                total_pref += w + 1;
            }
        }

        edge_bits.assign(total_words, 0);
        edge_pref.assign(total_pref, 0);
        for (int d = 1; d <= D; d++) {
            int width = level_size(d);
            for (int k = 0; k < width; k++) {
                int v = level_off[d] + k;
                if (!len[v]) continue;
                int pa = parent_of(v, d);
                int j = 0, bo = edge_bit_off[v], po = edge_pref_off[v];
                const auto& ch = xs[v];
                const auto& par = xs[pa];
                for (int i = 0; i < (int)ch.size(); i++) {
                    while (par[j] < ch[i]) ++j;
                    assert(par[j] == ch[i]);
                    up[item_off[v] + i] = j;
                    edge_bits[bo + (j >> 6)] |= 1ULL << (j & 63);
                }
                for (int w = 0; w < words[v]; w++) {
                    edge_pref[po + w + 1]
                        = edge_pref[po + w] + __builtin_popcountll(edge_bits[bo + w]);
                }
            }
        }

        leaf_off.assign(M + 1, 0);
        for (int r = 0; r < M; r++) leaf_off[r + 1] = leaf_off[r] + len[LEAF + r];
        leaf_pos.resize(leaf_off[M]);
        for (int r = 0; r < M; r++) {
            copy(xs[LEAF + r].begin(), xs[LEAF + r].end(), leaf_pos.begin() + leaf_off[r]);
        }

        root_pos = move(xs[1]);
        root_dense = !root_pos.empty();
        if (root_dense) {
            root_first = root_pos[0];
            for (int i = 1; i < (int)root_pos.size(); i++) {
                if (root_pos[i] != root_first + i) {
                    root_dense = false;
                    break;
                }
            }
        }

        vector<vector<int>>().swap(cand);
        vector<vector<int>>().swap(xs);
        bit_cnt.assign(fw, 0);
        bit_sum.assign(fw, 0);
        ++version;
    }

    void insert(ll value, int position) {
        modify_rank(rank_of(value), position, +1);
    }

    void erase(ll value, int position) {
        modify_rank(rank_of(value), position, -1);
    }

    void update(ll old_value, ll new_value, int position) {
        int a = rank_of(old_value), b = rank_of(new_value);
        if (a == b) return;

        int va = LEAF + a, vb = LEAF + b;
        int pa = leaf_index(a, position), pb = leaf_index(b, position);
        int d = D;

        while (va != vb) {
            add_node(va, pa, -1, -old_value);
            add_node(vb, pb, +1, +new_value);
            pa = up[item_off[va] + pa];
            pb = up[item_off[vb] + pb];
            va = parent_of(va, d);
            vb = parent_of(vb, d);
            --d;
        }

        ll ds = new_value - old_value;
        int p = pa;
        while (true) {
            add_node_sum(va, p, ds);
            if (d == 0) break;
            p = up[item_off[va] + p];
            va = parent_of(va, d);
            --d;
        }
        ++version;
    }

    int range_count(int l, int r) const {
        int L = root_bound(l), R = root_bound(r);
        return range_count_idx(1, L, R);
    }

    ll range_sum(int l, int r) const {
        int L = root_bound(l), R = root_bound(r);
        ll ret = range_sum_idx(1, L, R);
        cache_version = version;
        cache_l = l;
        cache_r = r;
        cache_L = L;
        cache_R = R;
        cache_sum = ret;
        return ret;
    }

    int cntLess(int l, int r, ll query) const {
        int p = lower_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return value_prefix<false>(p, L, R);
    }

    int cntLesseq(int l, int r, ll query) const {
        int p = upper_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return value_prefix<false>(p, L, R);
    }

    int cntMore(int l, int r, ll query) const {
        int p = upper_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return range_count_idx(1, L, R) - value_prefix<false>(p, L, R);
    }

    int cntMoreeq(int l, int r, ll query) const {
        int p = lower_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return range_count_idx(1, L, R) - value_prefix<false>(p, L, R);
    }

    ll sumLess(int l, int r, ll query) const {
        int p = lower_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return value_prefix<true>(p, L, R);
    }

    ll sumLesseq(int l, int r, ll query) const {
        int p = upper_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return value_prefix<true>(p, L, R);
    }

    ll sumMore(int l, int r, ll query) const {
        int p = upper_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return range_sum_idx(1, L, R) - value_prefix<true>(p, L, R);
    }

    ll sumMoreeq(int l, int r, ll query) const {
        int p = lower_bound(val.begin(), val.end(), query) - val.begin();
        int L = root_bound(l), R = root_bound(r);
        return range_sum_idx(1, L, R) - value_prefix<true>(p, L, R);
    }

    int min_count(int l, int r, ll k) const {
        if (k <= 0) return 0;

        int L, R;
        ll total;
        if (cache_version == version && cache_l == l && cache_r == r) {
            L = cache_L;
            R = cache_R;
            total = cache_sum;
        } else {
            L = root_bound(l);
            R = root_bound(r);
            total = range_sum_idx(1, L, R);
        }
        if (total < k) return -1;

        int ans = 0, v = 1;
        for (int d = 0; d < D; d++) {
            int cb = child_base(v, d);
            bool found = false;
            for (int j = branch[d] - 1; j >= 1; j--) {
                int ch = cb + j;
                int a = child_rank(ch, v, L), b = child_rank(ch, v, R);
                ll s = range_sum_idx(ch, a, b);
                if (s >= k) {
                    v = ch;
                    L = a;
                    R = b;
                    found = true;
                    break;
                }
                if (s) {
                    ans += range_count_idx(ch, a, b);
                    k -= s;
                }
            }
            if (!found) {
                int ch = cb;
                L = child_rank(ch, v, L);
                R = child_rank(ch, v, R);
                v = ch;
            }
        }

        int rank = v - LEAF;
        return ans + (int)((k - 1) / val[rank] + 1);
    }
};



int main(){
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<tuple<ll,ll,ll,ll,ll>> query(q);
    rep(i,0,q){
        ll c, x, l, r, k; cin >> c >> x >> l >> r >> k;
        c--;l--;
        query[i] = {c,x,l,r,k};
        a.push_back(x);
    }
    merge_sort_tree mst(a);
    rep(i,0,n) mst.add_candidate(a[i],i);
    for(auto [c,x,l,r,k]: query) mst.add_candidate(x,c);
    mst.build();
    rep(i,0,n) mst.insert(a[i],i);
    for(auto [c,x,l,r,k]: query){
        mst.update(a[c],x,c);
        a[c] = x;
        ll all = mst.range_sum(l,r);
        if(all < k){
            cout << -1 << endl;
            continue;
        }
        cout << mst.min_count(l,r,k) << endl;
    }
    return 0;
}