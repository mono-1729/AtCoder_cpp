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
    void insert(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return;
        for(ll& v : w) if(x & -x & v) v ^= x;
        w.push_back(x);
    }
    // 独立か判定
    ll count(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return 1;
        else return 0;
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