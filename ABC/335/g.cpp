#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll __int128_t
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}


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

ll powMod(ll x, ll n, ll p) {
    if (n == 0) return 1 % p;
    ll val = powMod(x, n / 2, p);
    val *= val;
    val %= p;
    if (n % 2 == 1) val *= x;
    return val % p;
}

int main() {
    long long n, p; cin >> n >> p;
    vector<long long> a(n);
    rep(i,0,n) cin >> a[i];
    unordered_map<ll,ll> pmp, amp;
    ll pp = p-1;
    rep(i,2,(ll)sqrt((double)p)+2){
        ll cnt = 0;
        while(pp%i == 0) cnt++, pp /= i;
        if(cnt) pmp[i] = cnt;
    }
    if(pp > 1) pmp[pp] = 1;
    rep(i,0,n){
        ll x = p-1;
        for(auto [base, cnt]: pmp){
            ll y = 1;
            rep(j,0,cnt){
                y *= base;
                if(powMod(a[i], (p-1)/y, p) == 1) x /= base;
                else break;
            }
        }
        amp[x]++;
    }
    vector<ll> divs;
    long long ans = 0;
    {
        vector<pll> vec(pmp.begin(), pmp.end());
        auto calc = [&](auto calc, ll num, ll i) -> void {
            if(i == vec.size()){
                divs.push_back(num);
                return;
            }
            ll po = 1;
            rep(j,0,vec[i].second+1){
                calc(calc, num*po, i+1);
                po *= vec[i].first;
            }
        };
        calc(calc,1,0);
        sort(all(divs));
        unordered_map<ll,ll> mp = amp;
        for(auto [x,y]: vec){
            for(auto k: divs){
                if((p-1)%(k*x) == 0) mp[k*x] += mp[k]; 
            }
        }
        for(auto [x,y]: amp){
            ans += y*mp[x];
        }
    }
    cout << ans << endl;
    return 0;
}