#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

template <ll MOD> class modint {
	ll val;
	static vector<modint<MOD>> factorial_vec;
public:

	ll get() const { return (ll)val; }
	// コンストラクタ
	modint(ll x = 0){
		val = x % MOD;
		if(val < 0) x += MOD;
	}

	// 入出力ストリーム
	friend constexpr istream &operator>>(istream &is, modint<MOD> &x){
		ll y; is >> y;
		x = y;
		return is;
	}
	friend constexpr ostream &operator<<(ostream &os, const modint<MOD> &x){
		return os << x.val;
	}

	// 算術演算子
	modint<MOD> operator -(){return modint<MOD>(-val);}
	modint<MOD> operator +(const modint<MOD> &r) const { return modint<MOD>(*this) += r; }
	modint<MOD> operator -(const modint<MOD> &r) const { return modint<MOD>(*this) -= r; }
	modint<MOD> operator *(const modint<MOD> &r) const { return modint<MOD>(*this) *= r; }
	modint<MOD> operator /(const modint<MOD> &r) const { return modint<MOD>(*this) /= r; }

	// 代入演算子
	modint<MOD> &operator +=(const modint<MOD> &r){
		val += r.val;
		if(val >= MOD) val -= MOD;
		return *this;
	}
	modint<MOD> &operator -=(const modint<MOD> &r){
		if(val < r.val) val += MOD;
		val -= r.val;
		return *this;
	}
	modint<MOD> &operator *=(const modint<MOD> &r){
		val = val*r.val%MOD;
		if(val < 0) val += MOD;
		return *this;
	}
	modint<MOD> &operator /=(const modint<MOD> &r){
		*this *= inv(r);
		return *this;
	}

	//等価比較演算子
	bool operator ==(const modint<MOD>& r){return this -> val == r.val;}
	bool operator !=(const modint<MOD>& r){return this -> val != r.val;}
	bool operator <(const modint<MOD>& r){return this -> val < r.val;}
	bool operator <=(const modint<MOD>& r){return this -> val <= r.val;}
	bool operator >(const modint<MOD>& r){return this -> val > r.val;}
	bool operator >=(const modint<MOD>& r){return this -> val >= r.val;}

	// 累乗
	static modint<MOD> modpow(modint<MOD> num, ll exp){
		if(!exp) return modint<MOD>(1); // 0乗
		modint<MOD> ret(1);
		modint<MOD> tmp = num;
		while(exp){
			if(exp&1) ret *= tmp;
			tmp *= tmp;
			exp >>= 1;
		}
		return ret;
	}

	// 逆元
	static modint<MOD> inv(modint<MOD> num){
		return modpow(num, MOD-2);
	}

	// 階乗
	static modint<MOD> factorial(ll n){
		modint<MOD> ret(1);
		if(n == 0) return ret;
		if((ll)factorial_vec.size() >= n) return factorial_vec[n-1];
		ret = factorial(n-1)*n;
		factorial_vec.push_back(ret);
		return ret;
	}

	// コンビネーション
	static modint<MOD> combination(ll n, ll r){
		return factorial(n) / factorial(r) / factorial(n-r);
	}

};

using mint = modint<MOD>;
template <ll MOD> vector<modint<MOD>> modint<MOD>::factorial_vec;

int getrandmax() {
    static uint32_t y = time(NULL);
    y ^= (y << 13); y ^= (y >> 17);
    y ^= (y << 5);
    return abs((int)y);
}
// [l, r]
int getrand(int l, int r) {
    return getrandmax() % (r - l + 1) + l;
}
typedef modint<1000000007> mint1;
typedef modint<1000000009> mint2;
int primes[10] = { 10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093 };
bool isShuffle = false;
struct RollingHash {
    mint1 p1; mint2 p2;
    int n;
    vector<mint1> m1; vector<mint2> m2;
    vector<mint1> v1; vector<mint2> v2;
    vector<mint1> r1; vector<mint2> r2;

    RollingHash() {
        if (!isShuffle) {
            rep(i, 0, 101) { int a = getrand(0, 9); int b = getrand(0, 9); swap(primes[a], primes[b]); }
            isShuffle = true;
        }
        p1 = primes[0], p2 = primes[1];
    }

    void init(string s, char o = 'a') {
        vector<int> v;
        for(auto c: s) v.push_back(c - o + 1);
        init(v);
    }

    void init(vector<int> s) {
        n = s.size();
        m1.resize(n); m2.resize(n); v1.resize(n); v2.resize(n); r1.resize(n); r2.resize(n);

        m1[0] = 1; m2[0] = 1;
        v1[0] = s[0]; v2[0] = s[0];

        rep(i, 1, n) {
            m1[i] = m1[i - 1] * p1;
            m2[i] = m2[i - 1] * p2;
            v1[i] = v1[i - 1] + m1[i] * s[i];
            v2[i] = v2[i - 1] + m2[i] * s[i];
        }

        r1[n - 1] = mint1(1) / m1[n - 1];
        rrep(i, n - 2, 0) r1[i] = r1[i + 1] * p1;

        r2[n - 1] = mint2(1) / m2[n - 1];
        rrep(i, n - 2, 0) r2[i] = r2[i + 1] * p2;
    }
    // s[l..r]
    inline pair<mint1, mint2> hash(int l, int r) {
        if (l > r) return make_pair(0,0);
        assert(l <= r); assert(r < n);
        mint1 a = v1[r];
        if (l) a -= v1[l - 1];
        a *= r1[l];

        mint2 b = v2[r];
        if (l) b -= v2[l - 1];
        b *= r2[l];

        return make_pair(a, b);
    }
    // s[l..r]
	inline ll llhash(int l, int r) {
		auto h = hash(l, r);
		return (ll)h.first.get() * (ll)1000000009 + (ll)h.second.get();
	}
};


int main() {
    int t; cin >> t;
    while(t--){
        string s; cin >> s;
        string x, y; cin >> x >> y;
        int x0 = 0, x1 = 0, y0 = 0, y1 = 0;
        for(char c : x){
            if(c == '0') x0++;
            else x1++;
        }
        for(char c : y){
            if(c == '0') y0++;
            else y1++;
        }
        int n = s.size();
        RollingHash rh;
        rh.init(s);
        ll num = 1;
        rep(i, 1, n+1){
            if(n%i != 0) continue;
            bool ok = true;
            for(int j = 0; j<n; j+=i){
                if(rh.llhash(j, j+i-1) != rh.llhash(0, i-1)){
                    ok = false;
                    break;
                }
            }
            if(!ok) continue;
            num = n/i;
            break;
        }
        
        if(x0 == y0) cout << "Yes" << endl;
        else if(x1 == y1) cout << "No" << endl;
        else{
            if((num*(x0-y0))%(y1-x1) == 0 && (num*(x0-y0))/(y1-x1) >=0) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}