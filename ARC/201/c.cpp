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
#define all(x) (x).begin(), (x).end()
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

vector<mint> pow2(1000001, 1);

struct Trie{
    struct Node {
        int c1 = -1, c2 = -1;
        int par = -1;
        int cnt = 0;
        int total = 0; 
        mint val = 0;
        Node() {}
        Node(int c1, int c2, int par = -1) : c1(c1), c2(c2), par(par) {}
    };
    vector<Node> nodes;
    Trie() {
        nodes.push_back(Node(1, 2));
        nodes.push_back(Node(-1, -1, 0));
        nodes.push_back(Node(-1, -1, 0));

    }
    void insert(string &s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - '0';
            if (nodes[cur].c1 == -1 && idx == 0) {
                nodes[cur].c1 = nodes.size();
                nodes.push_back(Node(-1, -1, cur));
            } else if (nodes[cur].c2 == -1 && idx == 1) {
                nodes[cur].c2 = nodes.size();
                nodes.push_back(Node(-1, -1, cur));
            }
            cur = (idx == 0) ? nodes[cur].c1 : nodes[cur].c2;
        }
        nodes[cur].cnt += 1;
        // cout << "inserted: " << s << " at node " << cur << endl;
        calc(cur);
    }
    void calc(int node_id) {
        while(node_id != -1) {
            nodes[node_id].total = nodes[node_id].cnt;
            mint num1 = 0, num2 = 0;
            if(nodes[node_id].c1 != -1) nodes[node_id].total += nodes[nodes[node_id].c1].total, num1 = nodes[nodes[node_id].c1].val;
            if(nodes[node_id].c2 != -1) nodes[node_id].total += nodes[nodes[node_id].c2].total, num2 = nodes[nodes[node_id].c2].val;
            nodes[node_id].val = pow2[nodes[node_id].total] - pow2[nodes[node_id].total-nodes[node_id].cnt] + num1*num2;
            // cout << node_id << " " << nodes[node_id].val.val() << " " << nodes[node_id].total << " " << nodes[node_id].cnt << endl;
            node_id = nodes[node_id].par;
        }
    }

};


int main() {
    rep(i, 1, 1000001) {
        pow2[i] = pow2[i-1] * 2;
    }
    ll n; cin >> n;
    Trie trie;
    rep(i,0,n){
        string s; cin >> s;
        for(auto &c : s) c == 'A' ? c = '0' : c = '1';
        trie.insert(s);
        cout << trie.nodes[0].val.val() << endl;
    }
    return 0;
}