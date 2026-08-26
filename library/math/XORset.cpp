#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

class xor_set{
private:
    vector<ll> w;
public:
    xor_set () {}
    void insert(ll x) {
        for (ll v : w) {
            chmin(x, x ^ v);
        }
        if (x == 0) return;
        for (ll& v : w) {
            chmin(v, v ^ x);
        }
        w.push_back(x);
        sort(w.begin(), w.end(), greater<ll>());
    }
    ll count(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return 1;
        else return 0;
    }
    void to_msb_basis() {
        constexpr int B = 63;
        ll basis[B] = {};

        for(ll x : w){
            for (int i = B - 1; i >= 0; i--){
                if(((x >> i) & 1LL) == 0) continue;
                if(basis[i]) x ^= basis[i];
                else{
                    basis[i] = x;
                    break;
                }
            }
        }
        for(int i = 0; i < B; i++){
            if (basis[i] == 0) continue;
            for(int j = i + 1; j < B; j++){
                if((basis[j] >> i) & 1LL){
                    basis[j] ^= basis[i];
                }
            }
        }
        w.clear();
        for(int i = B - 1; i >= 0; i--){
            if(basis[i]){
                w.push_back(basis[i]);
            }
        }
    }
    vector<ll> get(){return w;}
};

int main() {
    xor_set st;
    vector<ll> w = st.get();
    sort(w.begin(),w.end(),greater<ll>());
    rep(i,0,w.size()){
        rep(j,0,i)chmin(w[i],w[i]^w[j]);
        rep(j,0,i)chmin(w[j],w[i]^w[j]);
    }
    sort(w.begin(),w.end());
    return 0;
}