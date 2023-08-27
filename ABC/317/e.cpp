#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
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

int main() {
	int h,w;cin>>h>>w;
	vector<string> a(h);
	rep(i,0,h)cin>>a[i];
	int sx,sy,gx,gy;
	rep(i,0,h){
		rep(j,0,w){
			if(a[i][j] == 'S'){
				sx = i;
				sy = j;
				a[i][j] = '.';
			}
			else if(a[i][j] == 'G'){
				gx = i;
				gy = j;
				a[i][j] = '.';
			}
			else if(a[i][j] == '^'){
				int p=i;
				while(p-1 >= 0 && (a[p-1][j] == '.'|| a[p-1][j] == '!')){
					a[p-1][j] = '!';
					p--;
				}
			}
			else if(a[i][j] == 'v'){
				int p=i;
				while(p+1 < h && (a[p+1][j] == '.'|| a[p+1][j] == '!')){
					a[p+1][j] = '!';
					p++;
				}
			}
			else if(a[i][j] == '<'){
				int p=j;
				while(p-1 >= 0 && (a[i][p-1] == '.'|| a[i][p-1] == '!')){
					a[i][p-1] = '!';
					p--;
				}
			}
			else if(a[i][j] == '>'){
				int p=j;
				while(p+1 < w && (a[i][p+1] == '.'|| a[i][p+1] == '!')){
					a[i][p+1] = '!';
					p++;
				}
			}
		}
	}
	if(a[sx][sy] == '#' || a[gx][gy] == '#'){
		cout << -1 << endl;
		return 0;
	}
	vector<vector<int>> dist(h, vector<int>(w, -1));
	queue<pii> que;
	que.push({sx, sy});
	dist[sx][sy] = 0;
	vector<pii>g={{1,0},{-1,0},{0,1},{0,-1}};
	while(!que.empty()){
        int qx=que.front().first,qy=que.front().second; que.pop();
        for(auto nq: g){
			int dx=qx+nq.first, dy=qy+nq.second;
            if(0<=dx&& dx<h&&dy>=0&&dy<w&& dist[dx][dy] == -1&& a[dx][dy] == '.'){
                dist[dx][dy] = dist[qx][qy]+1;
                que.push({dx,dy});
            }
        }
    }
	if(dist[gx][gy] == -1){
		cout << -1 << endl;
		return 0;
	}
	cout << dist[gx][gy] << endl;
	return 0;
}