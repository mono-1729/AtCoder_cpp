#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

// https://github.com/mono-1729/AtCoder_cpp/blob/main/library/tree/Binary-Trie.cpp

struct BinaryTrieEmpty {};

template <class UInt = std::uint64_t,
          int BITS = std::numeric_limits<UInt>::digits,
          class Extra = BinaryTrieEmpty>
struct BinaryTrie {
    static_assert(std::is_integral_v<UInt> && std::is_unsigned_v<UInt> &&
                  !std::is_same_v<UInt, bool>, "UInt must be an unsigned integer");
    static_assert(1 <= BITS && BITS <= std::numeric_limits<UInt>::digits,
                  "BITS must fit in UInt");

    using key_type = UInt;
    using size_type = std::size_t;
    static constexpr int bit_width = BITS;
    static constexpr int root = 0;
    static constexpr int nil = -1;

    struct Node : Extra {
        int ch[2] = {nil, nil};
        size_type cnt = 0; 
    };
    using Path = std::array<int, BITS + 1>;

    std::vector<Node> nodes;

    BinaryTrie() : nodes(1) {}

    Node& operator[](int v) { return nodes[v]; }
    const Node& operator[](int v) const { return nodes[v]; }

    size_type size(int v = root) const {
        return v == nil ? 0 : nodes[v].cnt;
    }
    bool empty(int v = root) const { return size(v) == 0; }

    static bool in_range(UInt x) {
        if constexpr (BITS == std::numeric_limits<UInt>::digits) return true;
        else return (x >> BITS) == 0;
    }

    int child(int v, int b) const {
        assert(b == 0 || b == 1);
        if (v == nil) return nil;
        int u = nodes[v].ch[b];
        return empty(u) ? nil : u;
    }

    Path path(UInt x) const {
        Path p;
        p.fill(nil);
        if (!in_range(x)) return p;
        p[0] = root;
        for (int d = 0; d < BITS && p[d] != nil; ++d) {
            int b = int((x >> (BITS - 1 - d)) & UInt{1});
            p[d + 1] = child(p[d], b);
        }
        return p;
    }

    int find(UInt x) const { return path(x).back(); }
    size_type count(UInt x) const { return size(find(x)); }
    bool contains(UInt x) const { return find(x) != nil; }

    struct Noop {
        void operator()(int, int) const {}
    };

    template <class Pull = Noop>
    int insert(UInt x, Pull pull = {}) {
        if (!in_range(x)) throw std::out_of_range("BinaryTrie::insert");
        Path p;
        int v = p[0] = root;
        for (int d = 0; d < BITS; ++d) {
            int b = int((x >> (BITS - 1 - d)) & UInt{1});
            int u = nodes[v].ch[b];
            if (u == nil) {
                if (nodes.size() >= std::size_t(std::numeric_limits<int>::max()))
                    throw std::length_error("BinaryTrie: too many nodes");
                u = int(nodes.size());
                nodes.emplace_back();
                nodes[v].ch[b] = u;
            }
            v = p[d + 1] = u;
        }
        for (int u : p) ++nodes[u].cnt;
        pull_path(p, pull);
        return v;
    }

    template <class Pull = Noop>
    bool erase(UInt x, Pull pull = {}) {
        Path p = path(x);
        if (p.back() == nil) return false;
        for (int v : p) --nodes[v].cnt;
        pull_path(p, pull);
        return true;
    }

    std::optional<UInt> kth(size_type k) const {
        if (k >= size()) return std::nullopt;
        int v = root;
        UInt x = 0;
        for (int bit = BITS - 1; bit >= 0; --bit) {
            int l = child(v, 0);
            size_type n = size(l);
            if (k < n) {
                v = l;
            } else {
                k -= n;
                x |= UInt{1} << bit;
                v = child(v, 1);
            }
        }
        return x;
    }

    std::optional<UInt> min_element() const { return kth(0); }
    std::optional<UInt> max_element() const {
        if (empty()) return std::nullopt;
        return kth(size() - 1);
    }

    size_type count_less(UInt x) const {
        if (!in_range(x)) return size();
        size_type ans = 0;
        int v = root;
        for (int bit = BITS - 1; bit >= 0 && v != nil; --bit) {
            int b = int((x >> bit) & UInt{1});
            if (b) ans += size(child(v, 0));
            v = child(v, b);
        }
        return ans;
    }

    std::optional<UInt> lower_bound(UInt x) const {
        return kth(count_less(x));
    }
    std::optional<UInt> upper_bound(UInt x) const {
        return kth(count_less(x) + count(x));
    }

private:
    template <class Pull>
    void pull_path(const Path& p, Pull& pull) {
        for (int d = BITS; d >= 0; --d)
            pull(p[d], BITS - 1 - d);
    }
};


struct Info {
    int mx = 0; 
};

using Trie = BinaryTrie<uint32_t, 30, Info>;

int query(const Trie& tr, uint32_t x, uint32_t k){
    int ans = 0;
    int v = Trie::root;
    for (int bit = Trie::bit_width - 1; bit >= 0 && v != Trie::nil; --bit){
        int b = int((x >> bit) & 1u);
        if((k >> bit) & 1u){
            int u = tr.child(v, b);
            if(u != Trie::nil) ans = max(ans, tr[u].mx);
            v = tr.child(v, b ^ 1);
        }else{
            v = tr.child(v, b);
        }
    }
    if (v != Trie::nil) {
        ans = max(ans, tr[v].mx);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; uint32_t k; cin >> n >> k;
    Trie tr;
    int ans = 0;
    for (int i = 0; i < n; ++i){
        uint32_t x;
        cin >> x;
        int dp = query(tr, x, k) + 1;
        tr.insert(x, [&](int v, int) {
            tr[v].mx = max(tr[v].mx, dp);
        });
        ans = max(ans, dp);
    }

    cout << ans << '\n';
    return 0;
}