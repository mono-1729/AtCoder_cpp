#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}
template<int MOD> struct ModInt {
	static const int Mod = MOD; unsigned x; ModInt() : x(0) { }
	ModInt(signed sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
	ModInt(signed long long sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
	int get() const { return (int)x; }
	ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
	ModInt &operator/=(ModInt that) { return *this *= that.inverse(); }
	ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
	ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
	ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
	ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
	ModInt inverse() const { long long a = x, b = MOD, u = 1, v = 0;
		while (b) { long long t = a / b; a -= t * b; std::swap(a, b); u -= t * v; std::swap(u, v); }
		return ModInt(u); }
	bool operator==(ModInt that) const { return x == that.x; }
	bool operator!=(ModInt that) const { return x != that.x; }
	ModInt operator-() const { ModInt t; t.x = x == 0 ? 0 : Mod - x; return t; }
};
template<int MOD> ostream& operator<<(ostream& st, const ModInt<MOD> a) { st << a.get(); return st; };
template<int MOD> ModInt<MOD> operator^(ModInt<MOD> a, unsigned long long k) {
	ModInt<MOD> r = 1; while (k) { if (k & 1) r *= a; a *= a; k >>= 1; } return r; }
typedef ModInt<998244353> mint;

int gcd(int a, int b){
	if(a%b == 0){
	  return b;
	}else{
	  return gcd(b, a%b);
	}
}

int lcm(int a, int b){
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

// ここから
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
        maxi[x] = std::max(maxi[x],maxi[y]);
        mini[x] = std::min(mini[x],mini[y]);
    }

    inline ll min(ll x){
        return mini[root(x)];
    }

    inline ll max(int x){
        return mini[root(x)];
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
	int n;cin>>n;
	vector<int>p(n-1),q(n-1),index(n);
    vector<vector<int>>v(n);
	rep(i,0,n-1) {
        cin>>p[i]>>q[i];
        p[i]--;q[i]--;
    }
    rep(i,0,n){
        index[i]=i;
        v[i].push_back(i);
    }
    UnionFind uf(n);
    rep(i,0,n-1){
        if(uf.size(p[i])>uf.size(q[i])) swap(p[i],q[i]);
        int tmp=index[p[i]];
        for(auto j:v[index[p[i]]]){
            v[index[q[i]]].push_back(j);
            index[j]=index[q[i]];
        }
        v[tmp].clear();
        uf.unite(p[i],q[i]);
    }
    UnionFind uf2(n);
    vector<ll>ans(n+1,0);
    vector<int>nums(n),index2(n);
    rep(i,0,n){
        if(v[i].size()==0) continue;
        copy(v[i].begin(),v[i].end(),nums.begin());
    }
    rep(i,0,n){
        index[nums[i]]=i;
        index2[nums[i]]=i;
    }
    rep(i,0,n-1){
        ll ssize=uf2.size(p[i]),lsize=uf2.size(q[i]);
        ll sum=powMod(ssize+lsize,MOD-2);
        ans[index[p[i]]]+=(sum*ssize)%MOD;
        ans[index[q[i]]]+=(sum*lsize)%MOD;
        ans[index[p[i]]+ssize]-=(sum*ssize)%MOD;
        ans[index[q[i]]+lsize]-=(sum*lsize)%MOD;
        //cout<<ssize<<" "<<lsize<<" "<<index[p[i]]<<" "<<index[q[i]]<<endl;
        int tmp=index[p[i]];
        rep(j,0,ssize){
            index[nums[tmp+j]]=index[q[i]];
        }
        uf2.unite(p[i],q[i]);
    }
    rep(i,0,n){
        ans[i+1]+=ans[i];
    }
    rep(i,0,n){
        cout<<ans[index2[i]]%MOD<<" ";
    }
    cout<<endl;
	return 0;
}