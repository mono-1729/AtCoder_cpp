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

using mint = modint;

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

class UnionFind {
    vector<ll> parent, maxi, mini;
    inline ll root(ll n){
        return (parent[n] < 0? n:parent[n] = root(parent[n]));
    }
public:
    UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_){
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }

    inline bool same(ll x, ll y){
        return root(x) == root(y);
    }

    inline void unite(ll x, ll y){
        ll rx = root(x);
        ll ry = root(y);
        if(rx == ry) return;
        if(parent[rx] > parent[ry]) swap(rx, ry);
        parent[rx] += parent[ry];
        parent[ry] = rx;
        maxi[rx] = std::max(maxi[rx],maxi[ry]);
        mini[rx] = std::min(mini[rx],mini[ry]);
    }

    inline ll min(ll x){
        return mini[root(x)];
    }

    inline ll max(ll x){
        return maxi[root(x)];
    }

    inline ll size(ll x){
        return (-parent[root(x)]);
    }

    inline ll operator[](ll x){
        return root(x);
    }

    inline void print(){
        rep(i, 0, (ll)parent.size()) cout << root(i) << " ";
        cout << endl;
    }

    void clear(){
        rep(i, 0, (ll)parent.size()){
            parent[i] = -1;
        }
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }
};

int main() {
    ll p, a, b; cin >> p >> a >> b;
    modint::set_mod(p);
    if(a > b) swap(a, b);
    if(a == 1){
        vector<ll> ans = {1};
        while(true){
            ans.push_back((ans.back()*b)%p);
            if(ans.back() == 1) break;
        }
        if(ans.size() == p){
            cout << "Yes" << endl;
            for(auto x: ans) cout << x << " ";
            cout << endl;
        }else cout << "No" << endl;
    }else{
        ll n, m = 1, pre = 1;
        UnionFind uf(p);
        rep(i,1,p-1) uf.unite(i,(i*a)%p);
        n = uf.size(1);
        while((pre * b)%p != 1){
            m++;
            uf.unite(pre, (pre * b)%p);
            pre = (pre * b)%p;
        }
        if(uf.size(1) != p-1){
            cout << "No" << endl;
            return 0;
        }
        if(n%2 == 1){
            swap(a,b);
            swap(n,m);
        }
        m = (p-1)/n;
        vector<mint> ans = {1};
        mint bb = (mint)1/b;
        rep(i,0,n/2){
            rep(j,0,m-1) ans.push_back(ans.back()*b);
            ans.push_back(ans.back()*a);
            rep(j,0,m-1) ans.push_back(ans.back()*bb);
            ans.push_back(ans.back()*a);
        }
        cout << "Yes" << endl;
        for(auto x: ans) cout << x.val() << " ";
        cout << endl;
    }
    return 0;
}