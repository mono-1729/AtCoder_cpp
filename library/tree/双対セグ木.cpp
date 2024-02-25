//双対セグ木
#include<bits/stdc++.h>
using namespace std;
#define rep(i,l,r)for(int i=(l);i<(r);i++)

class segtree{
public:
	vector<set<pair<int,int>>> data;//
	int n;

	segtree(int _n){
		n=_n;
		data.resize(2*n);
	}
    //
	void ins(int p,int time,int val){
		if(time<0)data[p].erase({val,-time});
		else data[p].insert({val,time});
	}
    //
	void upd(int l,int r,int time,int val){
		for(l+=n,r+=n;l!=r;l=(l+1)>>1,r>>=1){
			if(l&1)ins(l,time,val);
			if(r&1)ins(r-1,time,val);
		}
	}
    //
	int get(int i){
		int ans=-1;
		for(i+=n;i;i>>=1){
			auto it=data[i].end();
			if(data[i].size())ans=max(ans,(--it)->first);
		}
		return ans;
	}
};


int main(){
	int n;
	cin >> n;
	segtree seg(n);
	rep(i,0,n){
		int a;
		cin >> a;
		seg.upd(i,i+1,0,a);
	}

	int q;
	cin >> q;
	vector<array<int,3>>query(q+1);
	for(int i=1;i<=q;i++){
		int t;
		cin >> t;
		if(t==1){
			int l,r,val;
			cin >> l >> r >> val;
			l--;
			seg.upd(l,r,i,val);
			query[i]={l,r,val};
		}else if(t==2){
			int ii;
			cin >> ii;
			seg.upd(query[ii][0],query[ii][1],-ii,query[ii][2]);
		}else{
			int ii;
			cin >> ii;
			cout << seg.get(ii-1) << endl;
		}
	}
}