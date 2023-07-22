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
		int n;
		vector<int> node, lazy;
	public:
		LazySegTree(vector<int> a){
			// 配列のサイズを取得
			int sz = (int) a.size();
			// nはszを超える最⼩の2のべき乗
			n = 1;
			while(n < sz) n *= 2;
			// ノードの個数は2n-1
			node.resize(2*n-1,0);
			lazy.resize(2*n-1, IINF);
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
				lazy[2*k+1] += lazy[k]/2;
				lazy[2*k+2] += lazy[k]/2;
			}
			// 伝播が終わったら⾃ノードの遅延配列を空にする
			node[k] = lazy[k];
			lazy[k] = 0;
		}
		// 区間の更新処理
		void add(int a, int b, int val, int k=0, int l=0, int r=-1){
			// 最初に遅延評価を実⾏しないと前の区間更新の際に⼊れていた値が消える
			eval(k);
			if(r < 0) r = n;
			// 完全に内側の時
			if(a <= l and r <= b){
				lazy[k] += (r-l)*val;
				eval(k);
			}else if(a < r and l < b){
				// ⼀部区間がかぶるとき
				add(a, b, val, k*2+1, l, (l+r)/2); // 左の⼦
				add(a, b, val, k*2+2, (l+r)/2, r); // 右の⼦
				node[k] = segfunc(node[k*2+1], node[k*2+2]);
			}
		}
		// 取得処理
		int get_num(int a, int b, int k=0, int l=0, int r=-1){
			eval(k);
			if(r < 0) r = n;
			// 完全に外側の時
			if(r <= a or b <= l) return IINF;
			// 完全に内側の時
			if(a <= l and r <= b) return node[k];
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
	string s;cin>>s;
	vector<int>num(n+1);
	rep(i,0,n){
		if (s[i]=='(') num[i+1]=num[i]+1;
		else num[i+1]=num[i]-1;
	}
	LazySegTree seg(num);
	rep(i,0,n) cout<<seg.get_num(i+1,i+2)<<endl;
	rep(i,0,q){
		int op,l,r;cin>>op>>l>>r;
		if (op==1){
			if (s[l-1]==s[r-1]) continue;
			if (s[l-1]=='('){
				seg.add(l,r,-2);
				s[l-1]=')';
				s[r-1]='(';
			}
			else{
				seg.add(l,r,2);
				s[l-1]='(';
				s[r-1]=')';
			}
		}
		if (op==2){
			cout<<seg.get_num(l,r+1)<<" "<<seg.get_num(l-1,l)<<" "<<seg.get_num(r,r+1)<<endl;
			if (seg.get_num(l,r+1)<0 or (seg.get_num(l-1,l)-seg.get_num(r,r+1)!=0)) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}
	}
	return 0;
}