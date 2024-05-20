#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
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

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

// 0ならば素数, 0でないなら最⼩の素因数
// 素因数分解や素因数の数も求めることが可能
ll max_num=1000005;
vector<ll> erat(max_num);
void init_e(){
    rep(i, 2, sqrt((double)max_num)+1){
        if(erat[i] == 0){
            for(ll j = i*i; j <= max_num-1; j += i){
                if(erat[j] == 0) erat[j] = i;
            }
        }
    }
}

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
    init_e();
    ll n,q;cin>>n>>q;
    vector<ll> a(n);
    rep(i,0,n)cin>>a[i];
    vector<vector<pii>> prime(n);
    rep(i,0,n){
        ll ai_ = a[i];
        while(ai_>1){
            ll num = erat[ai_]==0?ai_:erat[ai_];
            if(prime[i].size()==0 || prime[i].back().first!=num){
                prime[i].push_back({num,1});
            }
            else{
                prime[i].back().second++;
                if(prime[i].back().second==3) prime[i].pop_back();
            }
            ai_/=num;
        }
    }
    Mo mo(n);
    rep(i,0,q){
        ll l,r;cin>>l>>r;
        l--;
        mo.add(l,r);
    }
    int wa = 0;
    vector<int> cnt(1000006,0);
    vector<bool> ans(q);
    auto add = [&](int i) {
        for(auto [x,y]:prime[i]){
            if(cnt[x]==0) wa++;
            cnt[x]+=y;cnt[x]%=3;
            if(cnt[x]==0) wa--;
        }
    };
    auto erase = [&](int i) {
        for(auto [x,y]:prime[i]){
            if(cnt[x]==0) wa++;
            cnt[x]+=3-y;cnt[x]%=3;
            if(cnt[x]==0) wa--;
        }
    };
    auto out = [&](int q) {
        ans[q]= wa==0;
    };
    mo.build(add, erase, out);
    for(auto x:ans){
        if(x) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}