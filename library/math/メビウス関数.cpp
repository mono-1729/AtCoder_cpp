// https://qiita.com/drken/items/3beb679e54266f20ab63
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long

struct Eratosthenes {
    // テーブル
    vector<bool> isprime;
    
    // 整数 n を割り切る最小の素数
    vector<int> minfactor;

    // メビウス関数値
    vector<int> mobius;

    // コンストラクタで篩を回す
    Eratosthenes(int N) : isprime(N+1, true),
                          minfactor(N+1, -1),
                          mobius(N+1, 1) {
        // 1 は予めふるい落としておく
        isprime[1] = false;
        minfactor[1] = 1;

        // 篩
        for (int p = 2; p <= N; ++p) {
            // すでに合成数であるものはスキップする
            if (!isprime[p]) continue;

            // p についての情報更新
            minfactor[p] = p;
            mobius[p] = -1;
            
            // p 以外の p の倍数から素数ラベルを剥奪
            for (int q = p * 2; q <= N; q += p) {
                // q は合成数なのでふるい落とす
                isprime[q] = false;
                
                // q は p で割り切れる旨を更新
                if (minfactor[q] == -1) minfactor[q] = p;
                if ((q / p) % p == 0) mobius[q] = 0;
                else mobius[q] = -mobius[q];
            }
        }
    }
};
