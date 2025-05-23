#define ll long long
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
// https://ei1333.hateblo.jp/entry/2017/09/11/211011
struct Mo {
  int n;
  vector< pair< int, int > > lr;

  explicit Mo(int n) : n(n) {}

  void add(int l, int r) { /* [l, r) */
    lr.emplace_back(l, r);
  }

  template< typename AL, typename AR, typename EL, typename ER, typename O >
  void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
    int q = (int) lr.size();
    int bs = n / min< int >(n, sqrt((double)q));
    vector< int > ord(q);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [&](int a, int b) {
      int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
      if(ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
    });
    int l = 0, r = 0;
    for(auto idx : ord) {
      while(l > lr[idx].first) add_left(--l);
      while(r < lr[idx].second) add_right(r++);
      while(l < lr[idx].first) erase_left(l++);
      while(r > lr[idx].second) erase_right(--r);
      out(idx);
    }
  }

  template< typename A, typename E, typename O >
  void build(const A &add, const E &erase, const O &out) {
    build(add, add, erase, erase, out);
  }
};

int main() {
  int N;
  cin >> N;
  vector< int > A(N);
  for(auto &a: A) cin >> a;
  int Q;
  cin >> Q;
  Mo mo(N);
  for(int i = 0; i < Q; i++) {
    int a, b;
    cin >> a >> b;
    mo.add(a - 1, b);
  }
  vector< int > cnt(1000001), ans(Q);
  int sum = 0;
  auto add = [&](int i) {
    if(cnt[A[i]]++ == 0) ++sum;
  };
  auto erase = [&](int i) {
    if(--cnt[A[i]] == 0) --sum;
  };
  auto out = [&](int q) {
    ans[q] = sum;
  };
  mo.build(add, erase, out);
  for(auto &p: ans) cout << p << "\n";
}

// struct Mo {
//   int width;
//   vector<int> left, right, order;

//   Mo(int N, int Q) : order(Q) {
//     width = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
//     iota(begin(order), end(order), 0);
//   }

//   void insert(int l, int r) { /* [l, r) */
//     left.emplace_back(l);
//     right.emplace_back(r);
//   }

//   template <typename AL, typename AR, typename DL, typename DR, typename REM>
//   void run(const AL &add_left, const AR &add_right, const DL &delete_left,
//            const DR &delete_right, const REM &rem) {
//     assert(left.size() == order.size());
//     sort(begin(order), end(order), [&](int a, int b) {
//       int ablock = left[a] / width, bblock = left[b] / width;
//       if (ablock != bblock) return ablock < bblock;
//       if (ablock & 1) return right[a] < right[b];
//       return right[a] > right[b];
//     });
//     int nl = 0, nr = 0;
//     for (auto idx : order) {
//       while (nl > left[idx]) add_left(--nl);
//       while (nr < right[idx]) add_right(nr++);
//       while (nl < left[idx]) delete_left(nl++);
//       while (nr > right[idx]) delete_right(--nr);
//       rem(idx);
//     }
//   }
// };