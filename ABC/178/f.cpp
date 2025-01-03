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
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i];
    unordered_map<ll,ll> mpa, mpb;
    rep(i,0,n) mpa[a[i]]++, mpb[b[i]]++;

    for(auto [key, val]:mpa){
        if(val+mpb[key] > n){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;

    vector<tuple<ll,ll,ll>> vec;
    unordered_map<ll,ll> check;
    rep(i,0,n){
        if(!check[a[i]]){
            vec.push_back({mpa[a[i]]+mpb[a[i]],mpa[a[i]],a[i]});
            check[a[i]] = 1;
        }
        if(!check[b[i]]){
            vec.push_back({mpa[b[i]]+mpb[b[i]],mpa[b[i]],b[i]});
            check[b[i]] = 1;
        }
    }
    sort(vec.begin(),vec.end(),greater<tuple<ll,ll,ll>>());

    vector<ll> ansa(n,-1), ansb(n,-1);
    ll cnt = 0, acnt = 0, bcnt = 0;
    ll aidx = 0, bidx = 0;
    auto add = [&](ll val, ll flg) {
        if(flg == 0){
            while(ansa[aidx] != -1)aidx++;
            ansa[aidx] = val;
        }else{
            while(ansb[bidx] != -1)bidx++;
            ansb[bidx] = val;
        }
    };
    for(auto [sum, asum, val]:vec){
        if(cnt + sum <= n){
            rep(i,0,asum) ansa[cnt+i] = val, acnt++;
            rep(i,0,sum-asum) ansb[cnt+asum+i] = val, bcnt++;
            cnt += sum;
        }else if(cnt < n){
            while(cnt < n){
                if(sum-asum > 0 && bcnt >= asum){
                    ansb[cnt] = val;
                    sum--;
                }else{
                    ansa[cnt] = val;
                    asum--;
                    sum--;
                }
                cnt++;
            }
            rep(i,0,asum) add(val,0);   
            rep(i,0,sum-asum) add(val,1);
        }else{
            rep(i,0,asum) add(val,0);   
            rep(i,0,sum-asum) add(val,1);
        }
    }
    // rep(i,0,n) cout << ansa[i] << " ";  
    // cout << endl;
    // rep(i,0,n) cout << ansb[i] << " ";
    // cout << endl;
    vector<pll> ans(n);
    rep(i,0,n) ans[i] = {ansa[i],ansb[i]};
    sort(ans.begin(),ans.end());
    for(auto [x,y]:ans) cout << y << " ";
    cout << endl;
    return 0;
}