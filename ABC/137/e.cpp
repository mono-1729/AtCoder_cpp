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

// 辺
struct Edge
{
	int from;
	int to;
	int cost;
};

// ベルマンフォード法 (基本実装)
// 負閉路が存在する場合 true を返す
// distances は頂点数と同じサイズ, 全要素 INF で初期化しておく
void BellmanFord(vector<Edge> &edges, vector<ll> &dist, int start){
    fill(dist.begin(), dist.end(), INF);
	dist[start] = 0;
    // 負の閉路がなければ、(頂点数-1)回の更新で最短路が決まる
	rep(i, 0, (int)dist.size()-1){
		// 各辺について
		for (const auto& edge : edges){
			// to までの新しい距離
			const ll d = (dist[edge.from] + edge.cost);
			// d が現在の記録より小さければ更新
			if (d < dist[edge.to]&& dist[edge.from] != INF){
				dist[edge.to] = d;
			}
		}
	}
	rep(i, 0, (int)dist.size()){
		// 各辺について
		for (const auto& edge : edges){
			// to までの新しい距離
			const ll d = (dist[edge.from] + edge.cost);
			// d が現在の記録より小さければ更新
			if (d < dist[edge.to]&& dist[edge.from] != INF){
				dist[edge.to] = -INF;
			}
		}
	}
}



int main() {
	int n,m,p;cin>>n>>m>>p;
	vector<Edge> edges(n);
	rep(i,0,m){
		int a,b,c;cin>>a>>b>>c;
		a--;b--;
		edges.push_back({a,b,p-c});
	}
	vector<ll> dist(n);
	BellmanFord(edges, dist, 0);
	if (dist[n-1] == -INF) cout<<-1<<endl;
	else cout<<max(0LL,-dist[n-1])<<endl;
	return 0;
}