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
    int n; cin >> n;
    vector<int> p(2*n), q(2*n);
    rep(i,0,2*n) cin >> p[i], p[i]--;
    rep(i,0,2*n) cin >> q[2*n-i-1], q[2*n-i-1]--;
    vector<char> ans(2*n,'_');
    int l1 = -1, r1 = -1, l2 = -1, r2 = -1;
    int sum1 = 0, sum2 = 0; 
    set<int> st;
    rep(i,0,2*n) st.insert(i);
    rep(i,0,2*n){
        if(sum1 == 0){
            if(p[i] <= l1 || ans[p[i]] == ')'){
                cout << -1 << endl;
                return 0;
            }
            if(ans[p[i]] == '_'){
                ans[p[i]] = '(';
                st.erase(p[i]);
            }
            while(st.size()){
                auto it = st.begin();
                if(*it < p[i]){
                    ans[*it] = ')';
                    st.erase(it);
                }else break;
            }
            if(l1 > p[i]){
                cout << -1 << endl;
                return 0;
            }
            l1 = p[i];
            sum1++;
        }else{
            if(ans[p[i]] == '('){
                if(l1 > p[i]){
                    cout << -1 << endl;
                    return 0;
                }
                l1 = p[i];
                sum1++;   
            }else if(ans[p[i]] == ')'){
                if(r1 > p[i]){
                    cout << -1 << endl;
                    return 0;
                }
                r1 = p[i];
                sum1--;   
            }
        }
        if(sum2 == 0){
            if(q[i] <= r2 || ans[q[i]] == '('){
                cout << -1 << endl;
                return 0;
            }
            if(ans[q[i]] == '_'){
                ans[q[i]] = ')';
                st.erase(q[i]);
            }
            while(st.size()){
                auto it = st.begin();
                if(*it < q[i]){
                    ans[*it] = '(';
                    st.erase(it);
                }else break;
            }
            if(r2 > q[i]){
                cout << -1 << endl;
                return 0;
            }
            r2 = q[i];
            sum2--;
        }else{
            if(ans[q[i]] == '('){
                if(l2 > q[i]){
                    cout << -1 << endl;
                    return 0;
                }
                l2 = q[i];
                sum2++;   
            }else if(ans[q[i]] == ')'){
                if(r2 > q[i]){
                    cout << -1 << endl;
                    return 0;
                }
                r2 = q[i];
                sum2--;   
            }
        }
    }
    for(auto x:ans) cout << x;
    cout << endl;
    return 0;
}