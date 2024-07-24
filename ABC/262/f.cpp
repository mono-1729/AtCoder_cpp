#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
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

using S = struct{
    int num;
    int idx;
};
S op(S x1, S x2) {
    if(x1.num > x2.num) return x2;
    else if(x1.num < x2.num) return x1;
    else if(x1.idx < x2.idx) return x1;
    else return x2;
} 
bool f(S x){
    return 1;
}
S e() {return {IINF,-1};}

int main() {
    int n, k; cin >> n >> k;
    vector<int> p(n);
    rep(i,0,n) cin >> p[i];
    pii min_num = {IINF,-1};
    rep(i,0,n){
        if(min(i,n-i) <= k && min_num.first > p[i]) min_num = {p[i],i};
    }
    auto solve = [](int x, vector<int> q) -> vector<int> {
        int m = q.size();
        vector<int> res;
        vector<S>tmp(m);
        rep(i,0,m) tmp[i] = {q[i],i};
        segtree<S,op,e> seg(tmp);
        int now = 0;
        while(now < m){
            S query = seg.prod(now,min(m,now+x+1));
            x -= query.idx - now;
            res.push_back(query.num);
            now = query.idx+1;
        }
        rep(i,0,x)res.pop_back();
        return res;
    };
    int idx = min_num.second;
    auto solve2 = [](int x, vector<int> q,int idx, int n) -> vector<int> {
        int m = q.size();
        vector<int> res;
        vector<S>tmp(m);
        rep(i,0,m) tmp[i] = {q[i],i};
        segtree<S,op,e> seg(tmp);
        int now = 0;
        while(now < m){
            S query = seg.prod(now,min(m,now+x+1));
            x -= query.idx - now;
            if(query.idx < n-idx) x--;
            res.push_back(query.num);
            now = query.idx+1;
        }
        rep(i,0,x)res.pop_back();
        return res;
    };
    vector<int> ans1 =  idx <= k ? solve(k,p):vector<int>(n,IINF);
    vector<int> ans2;
    if(n-idx <= k){
        vector<int> vec;
        rep(i,idx,n) vec.push_back(p[i]);
        rep(i,0,idx) vec.push_back(p[i]);
        for(auto x:solve2(k,vec,idx,n)) ans2.push_back(x);
    }else ans2 = vector<int>(n,IINF);
    vector<int> ans = min(ans1,ans2);
    for(auto x:ans) cout << x << " ";
    cout << endl;
    return 0;
}