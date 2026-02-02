#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

vector<ll> Z_algorithm(string S) {
	ll c = 0, n = S.size();
	vector<ll> Z(n, 0);
	for (ll i = 1; i < n; i++) {
		ll l = i - c;
		if (i + Z[l] < c + Z[c]) {
			Z[i] = Z[l];
		}
		else {
			ll j = max(0LL, c + Z[c] - i);
			while (i + j < n && S[j] == S[i + j])j++;
			Z[i] = j;
			c = i;
		}
	}
	Z[0] = n;
	return Z;
}


int main() {
    ll t; cin >> t;
    std::mt19937 rng(std::random_device{}());
    while(t--){
        ll n; cin >> n;
        vector<pair<string, vector<ll>>> s(n);
        rep(i,0,n){
            string x; cin >> x;
            s[i] = {x,Z_algorithm(x)};
        }
        sort(all(s), [](pair<string, vector<ll>> &x, pair<string, vector<ll>> &y){
            if(x.first.size() < y.first.size()){
                rep(i,0,x.first.size()){
                    if(y.first[i] < x.first[i]) return false;
                    else if(y.first[i] > x.first[i]) return true;
                }
                if(y.first.size() == x.first.size()) return false;
                ll num = y.second[x.first.size()];
                if(x.first.size()+num == y.first.size()){
                    rep(i,y.first.size(),y.first.size()+x.first.size()){
                        if(x.first[i-y.first.size()] < y.first[i-x.first.size()]) return false;
                        else if(x.first[i-y.first.size()] > y.first[i-x.first.size()]) return true;
                    }
                    return false;
                }else{
                    return y.first[num+x.first.size()] > y.first[num];
                }
            }
            rep(i,0,y.first.size()){
                if(x.first[i] < y.first[i]) return true;
                else if(x.first[i] > y.first[i]) return false;
            }
            if(x.first.size() == y.first.size()) return false;
            ll num = x.second[y.first.size()];
            if(y.first.size()+num == x.first.size()){
                rep(i,x.first.size(),x.first.size()+y.first.size()){
                    if(y.first[i-x.first.size()] < x.first[i-y.first.size()]) return true;
                    else if(y.first[i-x.first.size()] > x.first[i-y.first.size()]) return false;
                }
                return false;
            }else{
                return x.first[num+y.first.size()] < x.first[num];
            }
        });
        ll f = 0;
        rep(i,0,n-1){
            if(s[i].first+s[i+1].first == s[i+1].first+s[i].first){
                f = 1;
                break;
            }
        }
        if(f){
            for(auto x: s) cout << x.first;
            cout << endl;
            continue;
        }
        if(n == 2){
            swap(s[0], s[1]);
            for(auto x: s) cout << x.first;
            cout << endl;
            continue;
        }
        string s1 = "", s2 = "";
        swap(s[n-1], s[n-2]);
        for(auto x: s) s1 += x.first;
        swap(s[n-1], s[n-2]);
        swap(s[n-3], s[n-2]);
        for(auto x: s) s2 += x.first;
        cout << min(s1,s2) << endl;
    }
    return 0;
}