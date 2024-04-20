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

char change_char(char s){
    if(s >='A' && s <= 'Z') return s - 'A' + 'a';
    else return s - 'a' + 'A';
}

int main() {
    string s;cin>>s;
    ll n = s.size();
    ll num = 0;
    vector<ll> p(n,0);
    vector<ll> stack;
    // 大文字と小文字を変換する 
    rep(i,0,n){
        if(s[i]=='('){
            num++;
            stack.push_back(i);
        }
        else if(s[i]==')'){
            p[stack.back()] = i;
            p[i] = stack.back();
            stack.pop_back();
            num--;
        }
        else{
            if(num%2==1)s[i] = change_char(s[i]);
        }
    }
    ll now = 0; // 現在の位置
    ll vec = 1; // 1: 右向き -1: 左向き
    while(now<n){
        if(s[now]=='(' || s[now]==')'){
            vec*=-1;
            now = p[now];
        }
        else  cout<<s[now];
        now+=vec;
    }
    cout<<endl;
    return 0;
} 