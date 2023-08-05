
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
struct SegmentTree {
	private:
		int n,ide_ele;
		vector<int> node;
	public:
		SegmentTree(vector<int> a,int nn){
			ide_ele=nn;
			// 配列のサイズを取得
			int sz = (int) a.size();
			// nはszを超える最⼩の2のべき乗
			n = 1;
			while(n < sz) n *= 2;
			// ノードの個数は2n-1
			node.resize(2*n-1, ide_ele);
			// 再下段にaの値を格納
			rep(i, 0, sz) node[i+n-1] = a[i];
			// 親を更新
			for(int j = n-2; j >= 0; j--) node[j] = segfunc(node[2*j+1], node[2*j+2]);
		}
		// 更新処理
		void add(int x, int val){
			// 再下段の指定した位置の値を更新
			x += n-1;
			node[x] += val;
			// 親の値を更新しながら上る
			while(x > 0){
				x = (x-1)/2;
				node[x]=segfunc(node[x*2+1],node[x*2+2]);
			}
		}
		void update(int x, int val){
			// 再下段の指定した位置の値を更新
			x += n-1;
			node[x] = val;
			// 親の値を更新しながら上る
			while(x > 0){
				x = (x-1)/2;
				node[x]=segfunc(node[x*2+1],node[x*2+2]);
			}
		}
		// 取得処理
		int get_num(int a, int b, int k=0, int l=0, int r=-1){
			if(r < 0) r = n;
			if(r <= a or b <= l) return ide_ele;
			if(a <= l and r <= b) return node[k];
			int v1 = get_num(a, b, 2*k+1, l, (l+r)/2);
			int v2 = get_num(a, b, 2*k+2, (l+r)/2, r);
			return segfunc(v1, v2);
		}
		int segfunc(int v1,int v2){
			return min(v1,v2);
		}
};
