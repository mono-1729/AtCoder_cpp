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
// 素因数分解や素因数の数も求めることが可能
int max_num=1000005;
vector<int> erat(max_num);
void init_e(){
	rep(i, 2, sqrt(max_num-1)){
		if(erat[i] == 0){
			for(int j = i*i; j <= max_num-1; j += i){
				if(erat[j] == 0) erat[j] = i;
			}
		}
	}
}