#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i = 0; i < (n); ++i)

// https://atcoder.jp/contests/abc268/submissions/34765119

struct Aho {
  using MP = unordered_map<char,int>;
  vector<MP> to;
  vector<int> cnt, fail;
  Aho(): to(1), cnt(1) {}
  int add(const string& s) {
    int v = 0;
    for (char c : s) {
      if (!to[v].count(c)) {
        to[v][c] = to.size();
        to.push_back(MP());
        cnt.push_back(0);
      }
      v = to[v][c];
    }
    cnt[v]++;
    return v;
  }
  void init() {
    fail = vector<int>(to.size(), -1);
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto [c,u] : to[v]) {
        fail[u] = (*this)(fail[v],c);
        cnt[u] += cnt[fail[u]];
        q.push(u);
      }
    }
  }
  int operator()(int v, char c) const {
    while (v != -1) {
      auto it = to[v].find(c);
      if (it != to[v].end()) return it->second;
      v = fail[v];
    }
    return 0;
  }
  int operator[](int v) const { return cnt[v];}
};

int main() {
  string s;
  cin >> s;
  int n;
  cin >> n;
  Aho d;
  rep(i,n) {
    string t;
    cin >> t;
    d.add(t);
  }
  d.init();

  int ans = 0, v = 0;
  for (char c : s) {
    v = d(v,c);
    if (d[v]) {
      ans++;
      v = 0;
    }
  }
  cout << ans << endl;
  return 0;
}