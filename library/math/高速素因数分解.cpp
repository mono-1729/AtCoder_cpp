#include <iostream>
#include <vector>

//n以下の整数について最小の素因数を求めた結果の配列を返す
//min_factor[i]はiを割り切る最小の数（iの素因数のうち最小のもの）
//min_factor[i] == iならiは素数（i=0, 1のときを除く）
std::vector<int> sieve(int n){
    //素数候補を管理する配列
    std::vector<int> min_factor(n+1);
    //2以上の数を一度素数候補に入れる
    for(int i = 0; i <= n; i++) min_factor[i] = i;
    //それぞれの数について最小の素因数を求める
    for(int i = 2; i*i <= n; i++){
        if(min_factor[i] == i){
            for(int j = 2; i*j <= n; j++){
                if(min_factor[i*j] > i){
                    min_factor[i*j] = i;
                }
            }
        }
    }
    return min_factor;
}

//配列min_factorを使ってmを素因数分解する
//配列ansにはmの素因数が小さい順に格納される
std::vector<int> factor(std::vector<int> &min_factor, int m){
    std::vector<int> ans;
    while(m > 1){
        ans.push_back(min_factor[m]);
        m /= min_factor[m];
    }
    return ans;
}

int main(){
    int n = 10000;
    //前処理
    std::vector<int> min_factor = sieve(n);

    //素因数分解
    std::vector<int> ans = factor(min_factor, 2020);

    //素因数分解の結果を出力
    for(int i = 0; i < ans.size(); i++) std::cout << ans[i] << " ";
    std::cout << std::endl;
    return 0;
}