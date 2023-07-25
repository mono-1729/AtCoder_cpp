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
	if (n % 2 == 1) val *= x;
	return val % MOD;
}

struct LazySegTree {
	private:
		int n,ide_ele;
		vector<int> node, lazy;
	public:
		LazySegTree(vector<int>& a,int nn){
			ide_ele=nn;
			// 配列のサイズを取得
			int sz = (int) a.size();
			// nはszを超える最⼩の2のべき乗
			n = 1;
			while(n < sz) n *= 2;
			// ノードの個数は2n-1
			node.resize(2*n-1, ide_ele);
			lazy.resize(2*n-1, 0);
			// 再下段にaの値を格納
			rep(i, 0, sz) node[i+n-1] = a[i];
			// 親を更新
			for(int j = n-2; j >= 0; j--) node[j] = segfunc(node[2*j+1], node[2*j+2]);
		}
		// k番⽬のノードについて遅延評価を⾏う
		void eval(int k) {
			// 遅延配列が空出ない場合、⾃ノードおよび⼦ノードへの
			// 値の伝播が起こる
			if(lazy[k] == 0) return;
			// 葉でなければ、⼦に伝播させる
			if(k < n-1) {
				lazy[2*k+1] = lazy[k];
				lazy[2*k+2] = lazy[k];
			}
			// 伝播が終わったら⾃ノードの遅延配列を空にする
			node[k] = lazy[k];
			lazy[k] = 0;
		}
		// 区間の更新処理
		void update(int a, int b, int val, int k=0, int l=0, int r=-1){
			// 最初に遅延評価を実⾏しないと前の区間更新の際に⼊れていた値が消える
			eval(k);
			if(r < 0) r = n;
			// 完全に内側の時
			if(a <= l && r <= b){
				lazy[k] = val;
				eval(k);
			}else if(a < r && l < b){
				// ⼀部区間がかぶるとき
				update(a, b, val, k*2+1, l, (l+r)/2); // 左の⼦
				update(a, b, val, k*2+2, (l+r)/2, r); // 右の⼦
				node[k] = segfunc(node[k*2+1], node[k*2+2]);
			}
		}
		// 取得処理
		int get_num(int a, int b, int k=0, int l=0, int r=-1){
			eval(k);
			if(r < 0) r = n;
			// 完全に外側の時
			if(r <= a || b <= l) return ide_ele;
			// 完全に内側の時
			if(a <= l && r <= b) return node[k];
			int v1 = get_num(a, b, 2*k+1, l, (l+r)/2);
			int v2 = get_num(a, b, 2*k+2, (l+r)/2, r);
			return segfunc(v1, v2);
		}
		int segfunc(int v1,int v2){
			return min(v1,v2);
		}
};


int main() {
	int n,q;cin>>n>>q;
	vector<int>rev(n,n-1);
	LazySegTree segx(rev,IINF);
	LazySegTree segy(rev,IINF);
	ll ans=1LL*(n-2)*(n-2);
	int minx=IINF,miny=IINF;
	rep(i,0,q){
		int num,x;cin>>num>>x;
		x--;
		if(num==1){
			int pos=segx.get_num(x,x+1);
			//cout<<pos<<endl;
			ans-=pos-1;
			segx.update(x,x+1,0);
			if (minx>=x)segy.update(0,pos,x);
			chmin(minx,x);
		}
		if(num==2){
			int pos=segy.get_num(x,x+1);
			//cout<<pos<<endl;
			ans-=pos-1;
			segy.update(x,x+1,0);
			if (miny>=x)segx.update(0,pos,x);
			chmin(miny,x);
		}
		//cout<<ans<<endl;
	}
	cout<<ans<<endl;
	return 0;
}