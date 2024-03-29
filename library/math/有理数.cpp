#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define ll long long

pair<ll, ll> rev(pair<ll, ll> x) {
    ll a = x.first;
    ll b = x.second;
    if (b < 0) return make_pair(-a, -b);
    return make_pair(a, b);
}
int main() {
	return 0;
}