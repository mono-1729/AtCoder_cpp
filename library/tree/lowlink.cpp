// https://sen-comp.hatenablog.com/entry/2022/11/17/233858

// 関節点
// https://onlinejudge.u-aizu.ac.jp/status/users/Sen/submissions/1/GRL_3_A/judge/7107478/C++14

// 橋
// https://onlinejudge.u-aizu.ac.jp/status/users/Sen/submissions/1/GRL_3_B/judge/7107473/C++14

#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#include<iomanip>
#include<cmath>
#include<tuple>
#include<functional>
#include<map>
#include<bitset>

using namespace std;

typedef long long ll;

class LowLink {
	typedef std::vector<std::vector<ll>> Edge;

	/**
	 * 訪問したことがある頂点かどうか.
	 */
	vector<bool> visited;
	/**
	 * 順序.
	 */
	vector<ll> order;
	/**
	 * 配列low. low[親] < low[子]なら、ブリッジとなる。
	 */
	vector<ll> low;

public:
	/**
	 * 与えられる木。隣接リスト形式でコストは含まれない.親は-1とする。
	 */
	Edge E;
	/**
	 * 関節点　その点を取り除くと全体が不連結になる点.
	 */
	vector<ll> articulation_points;
	/**
	 * 橋。pair<int, int>でfirst < secondで橋となる両端を入れる.
	 */
	vector<pair<ll, ll>> bridge;

private:

	void dfs(ll now, ll parent, ll& count) {
		visited[now] = true;
		order[now] = count;
		low[now] = order[now];
		count++;
		bool is_art = false;/* 関節点であるかどうか */
		ll son_count = 0;
		for (auto next : E[now]) {
			if (!visited[next]) {
				son_count++;
				dfs(next, now, count);
				if (next != parent)
					low[now] = min(low[now], low[next]);
				//関節点か イコールがつくのは、ひとまとまりのグループ内のlow[]は関節点のlow[]と同じ値だから。端はもうこれ以上伸びないので、関節点にカウントしない
				if (parent != -1 && order[now] <= low[next])
					is_art = true;
				//橋か
				if (order[now] < low[next])
					bridge.push_back(make_pair(min(now, next), max(now, next)));
			}
			else {
				//すでに行ったことある頂点=後退辺
				if (next != parent)
					low[now] = min(low[now], order[next]);
			}

		}
		//根は2つ以上の子があるなら、関節点
		if (parent == -1 && son_count >= 2)
			is_art = true;
		if (is_art)
			articulation_points.push_back(now);
	}

public:
	/**
	 * 渡すのは隣接リスト形式のグラフ。辺の長さは受け付けない.
	 *
	 * \param e
	 */
	LowLink(const Edge& e) {
		E = e;
		visited.assign(E.size(), 0);
		order.assign(E.size(), 0);
		low.assign(E.size(), 0);
	}
	/**
	 * 計算の際に呼び出す。各連結成分ごとにDFSしている。.
	 *
	 */
	void build() {
		ll count = 0;
		for (ll i = 0; i < E.size(); i++) {
			if (!visited[i])
				dfs(i, -1, count);
		}
	}
};

ll v, e;
vector<vector<ll>> E;

int main() {
	cin >> v >> e;
	E.assign(v, vector<ll>());
	for (ll i = 0; i < e; i++) {
		ll b, e;
		cin >> b >> e;
		E[b].push_back(e);
		E[e].push_back(b);
	}

	LowLink lowlink(E);
	lowlink.build();

	auto b = lowlink.bridge;
	sort(b.begin(), b.end());
	for (auto a : b) {
		cout << a.first << " " << a.second << endl;
	}
	return 0;
}