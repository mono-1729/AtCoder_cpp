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
// 0ならば素数, 0でないなら最⼩の素因数
vector<int> erat(600001);
void init_e(){
	rep(i, 2, sqrt(600000)){
		if(erat[i] == 0){
			for(int j = i*i; j <= 600000; j += i){
				if(erat[j] == 0) erat[j] = i;
			}
		}
	}
}