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
    string s; cin >> s;
    ll n = s.size();
    ll k; cin >> k;
    ll xsum = 0, ysum = 0;
    {
        rep(i,0,s.size()){
            if(s[i] == 'U') ysum--;
            if(s[i] == 'D') ysum++;
            if(s[i] == 'L') xsum--;
            if(s[i] == 'R') xsum++;
        }
        if(xsum < 0){
            xsum = -xsum;
            rep(i,0,n){
                if(s[i] == 'L') s[i] = 'R';
                else if(s[i] == 'R') s[i] = 'L';
            }
        }
        if(ysum < 0){
            ysum = -ysum;
            rep(i,0,n){
                if(s[i] == 'U') s[i] = 'D';
                else if(s[i] == 'D') s[i] = 'U';
            }
        }
        if(ysum == 0){
            rep(i,0,n){
                if(s[i] == 'U') s[i] = 'L';
                else if(s[i] == 'D') s[i] = 'R';
                else if(s[i] == 'L') s[i] = 'U';
                else if(s[i] == 'R') s[i] = 'D';
            }
            swap(xsum, ysum);
        }
    }
    if(xsum == 0 && ysum == 0){
        unordered_set<ll> st = {0};
        ll x = 0, y = 0;
        rep(i,0,n){
            if(s[i] == 'U') y--;
            if(s[i] == 'D') y++;
            if(s[i] == 'L') x--;
            if(s[i] == 'R') x++;
            st.insert(x*IINF+y);
        }
        cout << st.size() << endl;
    }else if(xsum == 0){
        unordered_map<ll,vector<ll>> mp;
        unordered_set<ll> st;
        ll x = n+1, y = n+1;
        st.insert(x*IINF+y);
        mp[x*IINF+y%ysum].push_back(y/ysum);
        rep(i,0,n){
            if(s[i] == 'U') y--;
            if(s[i] == 'D') y++;
            if(s[i] == 'L') x--;
            if(s[i] == 'R') x++;
            if(st.find(x*IINF+y) != st.end()) continue;
            // cout << x << " " << y << endl;
            st.insert(x*IINF+y);
            mp[x*IINF+y%ysum].push_back(y/ysum);
        }
        ll ans = 0;
        for(auto [key,vec]: mp){
            sort(vec.begin(), vec.end());
            ll m = vec.size();
            rep(i,0,m-1){
                ans += min(k,vec[i+1]-vec[i]);
            }
            ans += k;
        }
        cout << ans << endl;
    }else{
        unordered_map<ll,vector<ll>> mp;
        unordered_set<ll> st;
        ll x = n+1, y = n+1;
        st.insert(x*IINF+y);
        mp[(x%xsum)*1000000000000+(y%ysum)*1000000+x/xsum-y/ysum].push_back(y/ysum);
        rep(i,0,n){
            if(s[i] == 'U') y--;
            if(s[i] == 'D') y++;
            if(s[i] == 'L') x--;
            if(s[i] == 'R') x++;
            if(st.find(x*IINF+y) != st.end()) continue;
            st.insert(x*IINF+y);
            mp[(x%xsum)*1000000000000+(y%ysum)*1000000+x/xsum-y/ysum].push_back(y/ysum);
        }
        ll ans = 0;
        for(auto [key,vec]: mp){
            sort(vec.begin(), vec.end());
            ll m = vec.size();
            rep(i,0,m-1){
                ans += min(k,vec[i+1]-vec[i]);
            }
            ans += k;
        }
        cout << ans << endl;
    }
    return 0;
}