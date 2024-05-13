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
    mint div2 = mint(2).inv();
    vector<mint> divs(200005,1);
    rep(i,1,200005) divs[i]=divs[i-1]*div2;
    ll n,h;cin>>n>>h;
    ll n2 = powMod(2,n);
    vector<pll> x(n);
    vector<vector<pll>> idxs_;
    rep(i,0,n){
        ll k;cin>>k;
        x[i] = {k,i};
    }
    sort(x.begin(),x.end());
    ll id = 0;
    while(id<n){
        if(idxs_.size()==0 || idxs_.back().back().first+h<x[id].first){
            idxs_.push_back({x[id]});
        }
        else{
            idxs_.back().push_back(x[id]);
        }
        id++;
    }
    vector<vector<ll>> idxs;
    rep(i,0,idxs_.size()){
        vector<ll> tmp;
        rep(j,0,idxs_[i].size()) tmp.push_back(idxs_[i][j].second);
        idxs.push_back(tmp);
    }
    vector<vector<pll>> p,np;
    rep(i,0,idxs.size()){
        map<ll,ll> pos;
        rep(j,0,idxs[i].size()){
            pos[idxs[i][j]]=j;
        }
        vector<mint>right(idxs[i].size()+1,1);
        vector<mint>left(idxs[i].size()+1,1);
        vector<ll> stack;
        ll cnt = 0;
        for(auto j:idxs[i]){
            while(stack.size() && stack.back()>j){
                stack.pop_back();
            }
            left[cnt]=divs[stack.size()];
            stack.push_back(j);
            cnt++;
        }
        stack.clear();
        rrep(j,idxs[i].size()-1,0){
            while(stack.size() && stack.back()>idxs[i][j]){
                stack.pop_back();
            }
            right[j]=divs[stack.size()];
            stack.push_back(idxs[i][j]);
        }
        // for(auto va:left){
        //     cout<<va.val()<<" ";
        // }
        // cout<<endl;
        // for(auto va:right){
        //     cout<<va.val()<<" ";
        // }
        // cout<<endl;
        vector<pll> tmp;
        for(auto [key,val]:pos){
            mint num = 1;
            num*=left[val];
            num*=right[val];
            num*=div2;
            ll tmp_=0;
            if(val == 0 || key>idxs[i][val-1]) tmp_++;
            if(val == idxs[i].size()-1 || key>idxs[i][val+1]) tmp_++;
            num*=tmp_;
            tmp.push_back({key,num.val()});
        }
        p.push_back(tmp);
    } 
    // for(auto z:p){
    //     for(auto zz:z){
    //         cout<<zz.first<<" "<<zz.second<<endl;
    //     }
    //     cout<<endl;
    // }

    while(p.size()>=2){
        while(p.size()){
            if(p.size()==1){
                np.push_back(p[0]);
                p.pop_back();
            }
            else{
                vector<pll> vec1,vec2,nvec;
                vec1 = p.back();p.pop_back();
                vec2 = p.back();p.pop_back();
                mint num1 =0,num2=0;
                reverse(vec1.begin(),vec1.end());
                reverse(vec2.begin(),vec2.end());
                while(vec1.size()>0 || vec2.size()>0){
                    if(vec1.size()==0){
                        pll tmp = vec2.back();
                        tmp.second*=num1.val();
                        tmp.second%=MOD;
                        nvec.push_back(tmp);
                        vec2.pop_back();
                    }
                    else if(vec2.size()==0){
                        pll tmp = vec1.back();
                        tmp.second*=num2.val();
                        tmp.second%=MOD;
                        nvec.push_back(tmp);
                        vec1.pop_back();
                    }
                    else if(vec1.back().first<vec2.back().first){
                        pll tmp = vec1.back();
                        num1 = num1+vec1.back().second;
                        tmp.second*=num2.val();
                        tmp.second%=MOD;
                        nvec.push_back(tmp);
                        vec1.pop_back();
                    }
                    else{
                        pll tmp = vec2.back();
                        num2 = num2+vec2.back().second;
                        tmp.second*=num1.val();
                        tmp.second%=MOD;
                        nvec.push_back(tmp);
                        vec2.pop_back();
                    }
                }
                np.push_back(nvec);
            }
        }
        swap(p,np);
        np.clear();
    }
    // rep(i,0,n){
    //     cout<<(p[0][i].second)%MOD<<" ";
    // }
    // cout<<endl;

    rep(i,0,n){
        cout<<(p[0][i].second*n2)%MOD<<" ";
    }
    cout<<endl;
    return 0;
}