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
ll cnt = 0;

class node{
    public:
        ll idx;
        ll val;
        node(ll a, ll b){
            idx = a;
            val = b;
        }
        bool operator<(const node &n) const{
            if(idx!=-1 && n.idx!=-1) return idx < n.idx;
            cout<<"? "<<val<<" "<<n.val<<endl;
            cnt++;
            if(cnt>2) while(1);
            int res;cin>>res;
            return res == 1;
        }
};

int main() {
    ll n;cin>>n;
    vector<ll> a(n);
    rep(i,0,n) a[i] = i+1;
    stable_sort(a.begin(),a.end(),[&](ll x, ll y){
        cout<<"? "<<x<<" "<<y<<endl;
        cnt++;
        if(cnt>2) while(1);
        int res;cin>>res;
        return res == 1;
    });
    vector<node> num;
    rep(i,0,n)num.push_back( node(i, a[i]));
    set<node> st(num.begin(),num.end());
    while(st.size() > 1){
        auto itr = st.begin();
        auto itr2 = st.end();
        itr2--;
        node n1 = *itr, n2 = *itr2;
        st.erase(itr);
        st.erase(itr2);
        cout << "+ " << n1.val << " " << n2.val << endl;
        int res;cin>>res;
        st.insert(node(-1,res));
    }
    cout << "!" <<  endl;
    return 0;
}