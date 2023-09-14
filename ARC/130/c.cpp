#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll mod = 1000000007;
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

int main() {
	string a,b;cin>>a>>b;
	bool swaped = false;
	vector<ll>anum_(10), bnum_(10);
	int max_num=0;
	if(a.size() > b.size()){
		swap(a, b);
		swaped = true;
	}
	string aans=a,bans=b;
	rep(i, 0, a.size()) anum_[a[i]-'0']++;
	rep(i, 0, b.size()) bnum_[b[i]-'0']++;
	rep(i,1,10){
		int num=0;
		vector<ll>anum=anum_, bnum=bnum_;
		if(anum[i]==0)continue;
		string atmp=a, btmp=b;
		bool flg=true;
		rep(j,10-i,10){
			if(bnum[j]==0)continue;
			flg=false;
			atmp[a.size()-1]='0'+i;
			btmp[b.size()-1]='0'+j;
			anum[i]--;
			bnum[j]--;
			num++;
			break;
		}
		if(flg)continue;
		int count=2;
		rep(j,0,10){
			rep(k,1,10){
				if(9+j-k>=10)continue;
				while(anum[k]>0 && bnum[9+j-k]>0){
					atmp[a.size()-count]='0'+k;
					btmp[b.size()-count]='0'+9+j-k;
					anum[k]--;
					bnum[9+j-k]--;
					count++;
					num++;
				}
			}
		}
		if(count>a.size()) num+=bnum[9];
		int acnt=count,bcnt=count;
		rrep(j,9,1){
			rep(k,0,anum[j]){
				atmp[a.size()-acnt]='0'+j;
				acnt++;
			}
		}
		rrep(j,9,1){
			rep(k,0,bnum[j]){
				btmp[b.size()-bcnt]='0'+j;
				bcnt++;
			}
		}
		if(max_num<num){
			max_num=num;
			aans=atmp;
			bans=btmp;
		}
		//cout<<i<<" "<<num<<" "<<atmp<<" "<<btmp<<endl;
	}
	if (swaped) swap(aans, bans);
	cout<<aans<<endl<<bans<<endl;
	return 0;
}