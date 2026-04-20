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
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

// using mint = modint998244353;

ll gcd(ll a, ll b){
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

std::ostream &operator<<(std::ostream &dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}

__int128 parse(string &s) {
  __int128 ret = 0;
  for (int i = 0; i < s.length(); i++)
    if ('0' <= s[i] && s[i] <= '9')
      ret = 10 * ret + s[i] - '0';
  return ret;
}

template <typename T>
pair<vector<vector<int>>, int> CartesianTree(vector<T> &a) {
  int N = (int)a.size();
  vector<vector<int>> g(N);
  vector<int> p(N, -1), st;
  st.reserve(N);
  for (int i = 0; i < N; i++) {
    int prv = -1;
    while (!st.empty() && a[i] > a[st.back()]) {
      prv = st.back();
      st.pop_back();
    }
    if (prv != -1) p[prv] = i;
    if (!st.empty()) p[i] = st.back();
    st.push_back(i);
  }
  int root = -1;
  for (int i = 0; i < N; i++) {
    if (p[i] != -1)
      g[p[i]].push_back(i);
    else
      root = i;
  }
  return make_pair(g, root);
}

#define lt __int128_t
string s = "11156668546152666229236877884630071";

lt mod = parse(s);

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    ll b = 200025;
    ll c = 20;
    vector<lt> pow2(b,1),suml(n+1), sumr(n+1);
    unordered_map<lt,vector<ll>> mpl, mpr;
    mpl.reserve((n+1)*2);
    mpr.reserve((n+1)*2);
    rep(i,1,b) pow2[i] = (pow2[i-1]*2)%mod;
    rep(i,0,n) suml[i+1] += pow2[a[i]], suml[i+1] += suml[i], suml[i+1] %= mod;
    rrep(i,n-1,0) sumr[i] += pow2[a[i]], sumr[i] += sumr[i+1], sumr[i] %= mod;
    vector<vector<ll>> vecl, vecr;
    rep(i,0,n+1){
        mpl[suml[i]].push_back(i);
        mpr[sumr[i]].push_back(i);
        // cout << suml[i] << endl;
    }
    auto [g, p] = CartesianTree(a);
    ll ans = 0;
    auto dfs = [&](auto&dfs, ll v, ll l, ll r) -> void {
        // cout << v << " " << l << " " << r << endl;
        if(v-l < r-v){
            rep(left,l,v+1)rep(bit,a[v],a[v]+c){
                // if(bit <= a[v]+2) cout << pow2[bit] << endl;
                lt num = (suml[n]-pow2[bit]-suml[left]+mod*2)%mod;
                auto it = mpr.find(num);
                if(it == mpr.end()) continue;
                ll len = upper_bound(all(mpr[num]),r+1)-lower_bound(all(mpr[num]),v+1);
                ans += len;
            }
        }else{
            rep(right,v+1,r+2)rep(bit,a[v],a[v]+c){
                lt num = (suml[n]-pow2[bit]-sumr[right]+mod*2)%mod;
                auto it = mpl.find(num);
                if(it == mpl.end()) continue;
                ll len = upper_bound(all(mpl[num]),v)-lower_bound(all(mpl[num]),l);
                ans += len;
            }
        }
        for(auto nv: g[v]){
            if(nv < v) dfs(dfs,nv,l,v-1);
            else dfs(dfs,nv,v+1,r);
        }
    };

    dfs(dfs,p,0,n-1);

    cout << ans << endl;
    return 0;
}