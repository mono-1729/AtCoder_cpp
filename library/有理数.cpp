#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define ll long long

pair<ll, ll> rev(pair<ll, ll> x) {
    ll a = -x.first;
    ll b = x.second;

    if (a < 0) return make_pair(-b, -a);
    return make_pair(b, a);
}
int main() {
	return 0;
}