#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
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

using S = long long;
S op(S x1, S x2) {
    return x1 + x2;
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    ll q,k;cin>>q>>k;
    set<pll> st;
    set<ll> s;
    vector<ll> type(q), x(q);
    rep(i,0,q) cin>>type[i]>>x[i];
    vector<ll> vec(x.begin(), x.end());
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    unordered_map<ll, ll> mp;
    rep(i,0,vec.size()) mp[vec[i]] = i;
    segtree<S, op, e> seg(vec.size());
    rep(i,0,q){
        if(type[i] == 1){
            if(s.find(x[i]) != s.end()){
                s.erase(x[i]);
                seg.set(mp[x[i]], 0);
                auto it = st.lower_bound({x[i],INF});
                it--;
                pll t = *it;
                st.erase(it);
                if(t.first == x[i] && t.second == x[i]) continue;
                else if(t.first == x[i]){
                    auto it2 = s.lower_bound(x[i]);
                    st.insert({*it2, t.second});
                }
                else if(t.second == x[i]){
                    auto it2 = s.lower_bound(x[i]);
                    it2--;
                    st.insert({t.first, *it2});
                }
                else{
                    auto it2 = s.lower_bound(x[i]);
                    ll r = *it2;
                    ll l = *prev(it2);
                    if(r - l <= k)st.insert(t);
                    else{
                        st.insert({t.first, l});
                        st.insert({r, t.second});
                    }
                }
            }
            else{
                s.insert(x[i]);
                seg.set(mp[x[i]], 1);
                pll t = {x[i], x[i]};
                auto it = st.lower_bound(t);
                if(it!=st.begin()){
                    auto it2 = it;
                    pll t2 = *(--it2);
                    if(t2.first<=x[i] && x[i]<=t2.second) continue;
                    if(x[i] - t2.second <= k){
                        t.first = t2.first;
                        st.erase(t2);
                    }
                }
                it = st.lower_bound(t);
                if(it!=st.end()){
                    pll t2 = *it;
                    if(t2.first - x[i] <= k){
                        t.second = t2.second;
                        st.erase(it);
                    }
                }
                st.insert(t);
            } 
        }else{
            auto it = st.lower_bound({x[i],INF});
            it--;
            ll l = it->first, r = it->second;
            cout << seg.prod(mp[l], mp[r]+1) << endl;
        }
    }
    return 0;
}