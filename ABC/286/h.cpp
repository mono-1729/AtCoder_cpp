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

#include <iostream>
#include <math.h>
using namespace std;

struct Point
{
    double x = 0;
    double y = 0;

    void rot(double angle)
    {
        double new_x = x * cos(angle) - y * sin(angle);
        double new_y = x * sin(angle) + y * cos(angle);
        x = new_x;
        y = new_y;
    }

    void rot(int degree)
    {
        double pi = atan(1) * 4;
        double angle = double(degree) / 180 * pi;
        rot(angle);
    }

    double norm()
    {
        return sqrt(x * x + y * y);
    }

    double arg()
    {
        return atan2(y, x);
    }

    double operator*(Point &other)
    {
        return x * other.x + y * other.y;
    }

    double operator^(Point &other)
    {
        return x * other.y - y * other.x;
    }

    Point operator+(Point &other)
    {
        Point ans;
        ans.x = x + other.x;
        ans.y = y + other.y;
        return ans;
    }

    Point operator-(Point &other)
    {
        Point ans;
        ans.x = x - other.x;
        ans.y = y - other.y;
        return ans;
    }

    int ccw(Point B, Point C)
    {
        Point A = *this;
        Point AB = B - A;
        Point AC = C - A;
        double cross = AB ^ AC;
        if (cross > 0)
        {
            return 1;
        }
        else if (cross == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
        return true;
    }
    bool touch(Point A, Point B, Point C, Point D)
    {
        int f1 = ccw(B,C)*ccw(B,D);
        int f2 = B.ccw(A,C)*B.ccw(A,D);
        return (!f1 || !f2 || (f1 < 0 && f2 < 0));
    }
};

int main() {
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    vector<Point> points(n);
    rep(i, 0, n){
        cin >> points[i].x >> points[i].y;
    }
    Point s, t;
    cin >> s.x >> s.y >> t.x >> t.y;
    bool flg = true;
    rep(i,0,n) if(s.touch(s,t,points[i],points[(i+1)%n])) flg = false;
    if(flg){
        cout << (s-t).norm() << endl;
        cout << "a" << endl;
        return 0;
    }
    points.push_back(s);
    points.push_back(t);
    ll n2 = n + 2;
    ll sv = n, tv = n + 1;
    vector<vector<pair<ll,double>>> g(n2);
    auto add = [&](ll a, ll b, double c){
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    };
    auto addsp = [&](int v){
        rep(i,0,n){
            if(points[v].ccw(points[i], points[(i-1+n)%n]) * points[v].ccw(points[(i+1)%n], points[i]) >= 0){
                add(v,i,(points[v]-points[i]).norm());
            }
        }
    };
    addsp(sv); addsp(tv);
    rep(i,0,n) add(i,(i+1)%n,(points[i]-points[(i+1)%n]).norm());
    vector<double> dist(n2,INF);
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> pq;
    pq.push({0,sv}); dist[sv] = 0;
    while(pq.size()){
        auto [d,v] = pq.top(); pq.pop();
        if(dist[v] < d) continue;
        for(auto [to,c]:g[v]){
            if(dist[to] > dist[v] + c){
                dist[to] = dist[v] + c;
                pq.push({dist[to],to});
            }
        }
    }
    cout << dist[tv] << endl;
    return 0;
}