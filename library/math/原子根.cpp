#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;

__int128 powX(__int128 x, __int128 n, __int128 mod) {
    if (n == 0) return 1 % mod;
    __int128 val = powX(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

ll PrimitiveRoot(__int128 m) {
  __int128 divs[30] = {};
  divs[0] = 2;
  int cnt = 1;
  __int128 x = (m - 1) / 2;
  while (x % 2 == 0) x /= 2;
  for (__int128 i = 3; i * i <= x; i += 2) {
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x > 1) {
    divs[cnt++] = x;
  }
  for (__int128 g = 2;; g++) {
    bool ok = true;
    for (int i = 0; i < cnt; i++) {
      if (powX(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}