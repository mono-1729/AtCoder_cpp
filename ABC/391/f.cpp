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

int main() {
    ll n, k; cin >> n >> k;
    k--;
    vector<ll> a(n), b(n), c(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i];
    rep(i,0,n) cin >> c[i];
    sort(a.begin(), a.end(), greater<ll>());
    sort(b.begin(), b.end(), greater<ll>());
    sort(c.begin(), c.end(), greater<ll>());
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    priority_queue<tuple<ll,ll,ll,ll>> pq2;
    pq2.push({a[0]+b[0]+c[0], 0, 0, 0});
    pq.push(a[0]+b[0]+c[0]);
    unordered_set<ll> st;
    st.insert(0);
    while(!pq2.empty()){
        auto [sum, ai, bi, ci] = pq2.top();
        pq2.pop();
        if(ai+1 < n && st.find((ai+1)*n*n+bi*n+ci) == st.end()){
            if(pq.size() < k){
                ll nnum = a[ai+1]*b[bi]+b[bi]*c[ci]+c[ci]*a[ai+1];
                pq.push(nnum);
                pq2.push(make_tuple(nnum, ai+1, bi, ci));
                st.insert((ai+1)*n*n+bi*n+ci);
            }else{
                ll nnum = a[ai+1]*b[bi]+b[bi]*c[ci]+c[ci]*a[ai+1];
                if(nnum > pq.top()){
                    pq.pop();
                    pq.push(nnum);
                    pq2.push(make_tuple(nnum, ai+1, bi, ci));
                    st.insert((ai+1)*n*n+bi*n+ci);
                }
            }
        }
        if(bi+1 < n && st.find(ai*n*n+(bi+1)*n+ci) == st.end()){
            if(pq.size() < k){
                ll nnum = a[ai]*b[bi+1]+b[bi+1]*c[ci]+c[ci]*a[ai];
                pq.push(nnum);
                pq2.push(make_tuple(nnum, ai, bi+1, ci));
                st.insert(ai*n*n+(bi+1)*n+ci);
            }else{
                ll nnum = a[ai]*b[bi+1]+b[bi+1]*c[ci]+c[ci]*a[ai];
                if(nnum > pq.top()){
                    pq.pop();
                    pq.push(nnum);
                    pq2.push(make_tuple(nnum, ai, bi+1, ci));
                    st.insert(ai*n*n+(bi+1)*n+ci);
                }
            }
        }
        if(ci+1 < n && st.find(ai*n*n+bi*n+ci+1) == st.end()){
            if(pq.size() < k){
                ll nnum = a[ai]*b[bi]+b[bi]*c[ci+1]+c[ci+1]*a[ai];
                pq.push(nnum);
                pq2.push(make_tuple(nnum, ai, bi, ci+1));
                st.insert(ai*n*n+bi*n+ci+1);
            }else{
                ll nnum = a[ai]*b[bi]+b[bi]*c[ci+1]+c[ci+1]*a[ai];
                if(nnum > pq.top()){
                    pq.pop();
                    pq.push(nnum);
                    pq2.push(make_tuple(nnum, ai, bi, ci+1));
                    st.insert(ai*n*n+bi*n+ci+1);
                }
            }
        }
    }
    cout << pq.top() << endl;
    return 0;
}