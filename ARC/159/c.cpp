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
    vector<int> a(n);
    ll sum = 0;
    rep(i,0,n){
        cin >> a[i];
        sum += a[i];
    }
    vector<vector<ll>> ans;
    if(n == 2){
        cout << "Yes" << endl;
        ll num = abs(a[1] - a[0]);
        cout << num << endl;
        rep(i,0,num){
            if(a[0] > a[1]) cout << "1 2" << endl;
            else cout << "2 1" << endl;
        }
    }
    else if((n%2 == 0) && sum%n == 0){
        cout << "Yes" << endl;
        while(true){
            pll ma = {0,0};
            pll mi = {INF,0};
            rep(i,0,n){
                if(ma.first < a[i]) ma = make_pair(a[i],i);
                if(mi.first > a[i]) mi = make_pair(a[i],i);
            }
            if(ma.first == mi.first) break;
            vector<ll> tmp1(n),tmp2(n);
            vector<ll> use1(n+1,1),use2(n+1,1);
            use1[n/2] = 0;
            use1[n/2-1] = 0;
            use2[n/2+1] = 0;
            use2[n/2+2] = 0;
            int idx = 1;
            rep(i,0,n){
                if(ma.second == i){
                    tmp1[i] = n/2 - 1;
                    tmp2[i] = n/2 + 1;
                }else if(mi.second == i){
                    tmp1[i] = n/2;
                    tmp2[i] = n/2 + 2;
                    a[i]+=2;
                }else{
                    if(use1[idx]){
                        tmp1[i] = idx;
                        tmp2[i] = n+1-idx;
                        use1[idx] = 0;
                    }
                    else{
                        tmp2[i] = idx;
                        tmp1[i] = n+1-idx;
                        idx++;
                    }
                    a[i]+=1;
                }
            }
            ans.push_back(tmp1);
            ans.push_back(tmp2);
        }
        cout << ans.size() << endl;
        rep(i,0,ans.size()){
            for(auto x: ans[i]) cout << x << " ";
            cout << endl;
        }
    }
    else if((n%2 == 0) && sum%n == n/2){
        cout << "Yes" << endl;
        ans.push_back(vector<ll>(n,0));
        vector<pll> x(n);
        rep(i,0,n) x[i] = {a[i],i};
        sort(x.begin(),x.end());
        reverse(x.begin(),x.end());
        rep(i,0,n) a[x[i].second] += i+1;
        rep(i,0,n) ans.back()[x[i].second] = i+1;
        while(true){
            pll ma = {0,0};
            pll mi = {INF,0};
            rep(i,0,n){
                if(ma.first < a[i]) ma = make_pair(a[i],i);
                if(mi.first > a[i]) mi = make_pair(a[i],i);
            }
            if(ma.first == mi.first) break;
            vector<ll> tmp1(n),tmp2(n);
            vector<ll> use1(n+1,1),use2(n+1,1);
            use1[n/2] = 0;
            use1[n/2-1] = 0;
            use2[n/2+1] = 0;
            use2[n/2+2] = 0;
            int idx = 1;
            rep(i,0,n){
                if(ma.second == i){
                    tmp1[i] = n/2 - 1;
                    tmp2[i] = n/2 + 1;
                }else if(mi.second == i){
                    tmp1[i] = n/2;
                    tmp2[i] = n/2 + 2;
                    a[i]+=2;
                }else{
                    if(use1[idx]){
                        tmp1[i] = idx;
                        tmp2[i] = n+1-idx;
                        use1[idx] = 0;
                    }
                    else{
                        tmp2[i] = idx;
                        tmp1[i] = n+1-idx;
                        idx++;
                    }
                    a[i]+=1;
                }
            }
            ans.push_back(tmp1);
            ans.push_back(tmp2);
        }
        cout << ans.size() << endl;
        rep(i,0,ans.size()){
            for(auto x: ans[i]) cout << x << " ";
            cout << endl;
        }
    }
    else if(sum%n == 0){
        cout << "Yes" << endl;
        while(true){
            pll ma = {0,0};
            pll mi = {INF,0};
            rep(i,0,n){
                if(ma.first < a[i]) ma = make_pair(a[i],i);
                if(mi.first > a[i]) mi = make_pair(a[i],i);
            }
            if(ma.first == mi.first) break;
            vector<ll> tmp1(n),tmp2(n);
            vector<ll> use1(n+1,1),use2(n+1,1);
            use1[n/2] = 0;
            use1[n/2+1] = 0;
            use2[n/2+1] = 0;
            use2[n/2+2] = 0;
            int idx = 1;
            rep(i,0,n){
                if(ma.second == i){
                    tmp1[i] = n/2;
                    tmp2[i] = n/2 + 1;
                }else if(mi.second == i){
                    tmp1[i] = n/2 + 1;
                    tmp2[i] = n/2 + 2;
                    a[i]+=2;
                }else{
                    if(use1[idx]){
                        tmp1[i] = idx;
                        tmp2[i] = n+1-idx;
                        use1[idx] = 0;
                    }
                    else{
                        tmp2[i] = idx;
                        tmp1[i] = n+1-idx;
                        idx++;
                    }
                    a[i]+=1;
                }
            }
            ans.push_back(tmp1);
            ans.push_back(tmp2);
        }
        cout << ans.size() << endl;
        rep(i,0,ans.size()){
            for(auto x: ans[i]) cout << x << " ";
            cout << endl;
        }
    }
    else cout << "No" << endl;
    return 0;
}