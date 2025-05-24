#pragma GCC optimize ("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
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

// https://atcoder.jp/contests/chokudai_S001/submissions/22179950
 
namespace range_lis_query_impl {

    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    using vec = std::vector<u32>;
    
    u32 popcount(u64 x) {
    #ifdef __GNUC__
      return __builtin_popcountll(x);
    #else
      x -= x >> 1 & 0x5555555555555555;
      x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
      x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
      return x * 0x0101010101010101 >> 56 & 0x7f;
    #endif
    }
    
    class bit_vector {
      class node_type {
      public:
        u64 bit;
        u32 sum;
    
        node_type() : bit(0), sum(0) {}
      };
    
      std::vector<node_type> v;
    
    public:
      explicit bit_vector(const u32 n) : v((n + 63) / 64 + 1, node_type()) {}
    
      void set(const u32 i) {
        v[i / 64].bit |= static_cast<u64>(1) << i;
        v[i / 64 + 1].sum += 1;
      }
      void build() {
        for (u32 i = 1; i != v.size(); i += 1) {
          v[i].sum += v[i - 1].sum;
        }
      }
    
      u32 rank(const u32 i) const {
        return v[i / 64].sum +
               popcount(v[i / 64].bit & ~(~static_cast<u64>(0) << i % 64));
      }
    
      u32 all() const { return v.back().sum; }
    };
    
    class wavelet_matrix {
    private:
      static bool test(const u32 x, const u32 k) { return x >> k & 1; }
    
      u32 n;
      std::vector<bit_vector> mat;
    
    public:
      explicit wavelet_matrix(const u32 bit_length, vec a)
          : n(a.size()), mat(bit_length, bit_vector(n)) {
        vec v0, v1;
        v0.reserve(n);
        v1.reserve(n);
        for (u32 p = bit_length; p != 0;) {
          p -= 1;
          {
            bit_vector &v = mat[p];
            for (u32 i = 0; i != n; i += 1) {
              if (test(a[i], p)) {
                v.set(i);
              }
            }
            v.build();
          }
          {
            for (const u32 e : a) {
              if (!test(e, p)) {
                v0.push_back(e);
              } else {
                v1.push_back(e);
              }
            }
            const auto itr = std::copy(v0.begin(), v0.end(), a.begin());
            std::copy(v1.begin(), v1.end(), itr);
            v0.clear();
            v1.clear();
          }
        }
      }
    
      u32 count_less(u32 first, const u32 key) const {
        u32 last = n;
        u32 ret = 0;
        for (u32 p = mat.size(); p != 0;) {
          p -= 1;
          const bit_vector &v = mat[p];
          const u32 rank_f = v.rank(first);
          const u32 rank_l = v.rank(last);
          if (!test(key, p)) {
            first -= rank_f;
            last -= rank_l;
          } else {
            ret += (last - first) - (rank_l - rank_f);
            const u32 z = n - v.all();
            first = z + rank_f;
            last = z + rank_l;
          }
        }
        return ret;
      }
    
      u32 size() const { return n; }
    };
    
    using Iter = typename vec::iterator;
    
    static constexpr u32 none = -1;
    
    bool is_permutation(const vec &p) {
      const u32 n = p.size();
      std::vector<bool> used(n, false);
      for (const u32 e : p) {
        if (e == none || e >= n || used[e]) {
          return false;
        }
        used[e] = true;
      }
      return true;
    }
    
    vec inverse(const vec &p) {
      const u32 n = p.size();
      vec q(n, none);
      for (u32 i = 0; i != n; i += 1) {
        if (p[i] != none) {
          q[p[i]] = i;
        }
      }
      return q;
    }
    
    void unit_monge_dmul(const u32 n, Iter stack, const Iter a, const Iter b) {
      if (n == 1) {
        stack[0] = 0;
        return;
      }
      const Iter c_row = stack;
      stack += n;
      const Iter c_col = stack;
      stack += n;
    
      const auto map = [=](const u32 len, const auto f, const auto g) {
        const Iter a_h = stack + 0 * len;
        const Iter a_m = stack + 1 * len;
        const Iter b_h = stack + 2 * len;
        const Iter b_m = stack + 3 * len;
        const auto split = [=](const Iter v, Iter v_h, Iter v_m) {
          for (u32 i = 0; i != n; i += 1) {
            if (f(v[i])) {
              *v_h = g(v[i]);
              ++v_h;
              *v_m = i;
              ++v_m;
            }
          }
        };
        split(a, a_h, a_m);
        split(b, b_h, b_m);
        const Iter c = stack + 4 * len;
        unit_monge_dmul(len, c, a_h, b_h);
        for (u32 i = 0; i != len; i += 1) {
          const u32 row = a_m[i];
          const u32 col = b_m[c[i]];
          c_row[row] = col;
          c_col[col] = row;
        }
      };
      const u32 mid = n / 2;
      map(mid, [mid](const u32 x) { return x < mid; },
          [](const u32 x) { return x; });
      map(n - mid, [mid](const u32 x) { return x >= mid; },
          [mid](const u32 x) { return x - mid; });
    
      class d_itr {
      public:
        u32 delta;
        u32 col;
        d_itr() : delta(0), col(0) {}
      };
      u32 row = n;
      const auto right = [&](d_itr &it) {
        if (b[it.col] < mid) {
          if (c_col[it.col] >= row) {
            it.delta += 1;
          }
        } else {
          if (c_col[it.col] < row) {
            it.delta += 1;
          }
        }
        it.col += 1;
      };
      const auto up = [&](d_itr &it) {
        if (a[row] < mid) {
          if (c_row[row] >= it.col) {
            it.delta -= 1;
          }
        } else {
          if (c_row[row] < it.col) {
            it.delta -= 1;
          }
        }
      };
      d_itr neg, pos;
      while (row != 0) {
        while (pos.col != n) {
          d_itr temp = pos;
          right(temp);
          if (temp.delta == 0) {
            pos = temp;
          } else {
            break;
          }
        }
        row -= 1;
        up(neg);
        up(pos);
        while (neg.delta != 0) {
          right(neg);
        }
        if (neg.col > pos.col) {
          c_row[row] = pos.col;
        }
      }
    }
    
    vec subunit_monge_dmul(vec a, vec b) {
      const u32 n = a.size();
      vec a_inv = inverse(a);
      vec b_inv = inverse(b);
      std::swap(b, b_inv);
      vec a_map, b_map;
      for (u32 i = n; i != 0;) {
        i -= 1;
        if (a[i] != none) {
          a_map.push_back(i);
          a[n - a_map.size()] = a[i];
        }
      }
      std::reverse(a_map.begin(), a_map.end());
      {
        u32 cnt = 0;
        for (u32 i = 0; i != n; i += 1) {
          if (a_inv[i] == none) {
            a[cnt] = i;
            cnt += 1;
          }
        }
      }
      for (u32 i = 0; i != n; i += 1) {
        if (b[i] != none) {
          b[b_map.size()] = b[i];
          b_map.push_back(i);
        }
      }
      {
        u32 cnt = b_map.size();
        for (u32 i = 0; i != n; i += 1) {
          if (b_inv[i] == none) {
            b[cnt] = i;
            cnt += 1;
          }
        }
      }
      vec c([](u32 n) {
        u32 ret = 0;
        while (n != 1) {
          ret += 2 * n;
          n = (n + 1) / 2;
          ret += 4 * n;
        }
        ret += 1;
        return ret;
      }(n));
      unit_monge_dmul(n, c.begin(), a.begin(), b.begin());
    
      vec c_pad(n, none);
      for (u32 i = 0; i != a_map.size(); i += 1) {
        const u32 t = c[n - a_map.size() + i];
        if (t < b_map.size()) {
          c_pad[a_map[i]] = b_map[t];
        }
      }
      return c_pad;
    }
    
    vec seaweed_doubling(const vec &p) {
      const u32 n = p.size();
      if (n == 1) {
        return vec({none});
      }
      const u32 mid = n / 2;
      vec lo, hi;
      vec lo_map, hi_map;
      for (u32 i = 0; i != n; i += 1) {
        const u32 e = p[i];
        if (e < mid) {
          lo.push_back(e);
          lo_map.push_back(i);
        } else {
          hi.push_back(e - mid);
          hi_map.push_back(i);
        }
      }
      lo = seaweed_doubling(lo);
      hi = seaweed_doubling(hi);
      vec lo_pad(n), hi_pad(n);
      std::iota(lo_pad.begin(), lo_pad.end(), u32(0));
      std::iota(hi_pad.begin(), hi_pad.end(), u32(0));
      for (u32 i = 0; i != mid; i += 1) {
        if (lo[i] == none) {
          lo_pad[lo_map[i]] = none;
        } else {
          lo_pad[lo_map[i]] = lo_map[lo[i]];
        }
      }
      for (u32 i = 0; mid + i != n; i += 1) {
        if (hi[i] == none) {
          hi_pad[hi_map[i]] = none;
        } else {
          hi_pad[hi_map[i]] = hi_map[hi[i]];
        }
      }
      return subunit_monge_dmul(std::move(lo_pad), std::move(hi_pad));
    }
    
    class range_lis_query {
      static bool is_permutation(const std::vector<int> &p) {
        const u32 n = p.size();
        std::vector<bool> used(n, false);
        for (const int e : p) {
          if (e < 0 || n <= e || used[e]) {
            return false;
          }
          used[e] = true;
        }
        return true;
      }
    
      static wavelet_matrix convert(const std::vector<int> &p) {
        assert(is_permutation(p));
        u32 n = p.size();
        vec row;
        if (n != 0) {
          row = seaweed_doubling(vec(p.begin(), p.end()));
        }
        for (u32 &e : row) {
          if (e == none) {
            e = n;
          }
        }
        u32 bit_length = 0;
        while (n != 0) {
          bit_length += 1;
          n /= 2;
        }
        return wavelet_matrix(bit_length, std::move(row));
      }
    
      wavelet_matrix wm;
    
    public:
      range_lis_query() : range_lis_query(std::vector<int>()) {}
      range_lis_query(const std::vector<int> &p) : wm(convert(p)) {}
    
      int query(const int left, const int right) const {
        assert(0 <= left && left <= right && right <= wm.size());
        return (right - left) - wm.count_less(left, right);
      }
    };
    
} // namespace range_lis_query_impl
    
using range_lis_query_impl::range_lis_query;

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<int> a(n), b(n);
        rep(i,0,n) cin >> a[i], a[i]--, b[i] = n-a[i]-1;
        range_lis_query r1(a), r2(b);
        ll ans = 0;
        ll now = 1;
        rep(i,0,n){
            chmax(now, min(i+3, n));
            while(now < n && r1.query(i, now+1)+r2.query(i, now+1) == now-i+2){
                now++;
            }
            ans += now-i;
        }
        cout << ans << '\n';
    }
    return 0;
}