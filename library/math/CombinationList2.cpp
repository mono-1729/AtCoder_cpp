#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

template<typename T>
vector<vector<T>> combination(vector<T> &elems, int r) {
    vector<vector<T>> v{};
    vector<T> v1(r);
    map<T,int> m{};
    for(T &i: elems)m[i]++;
    vector<T> elem{};
    for(auto iter = m.begin(); iter != m.end(); iter++)elem.push_back(iter->first);

    int n = elems.size();
    function<void(int,int)> _dfs = [&](int now,int num_decided){
        if(num_decided > r)
            return;
        if (num_decided == r) {
            v.push_back(v1);
            return;
        }
        if(now == elem.size())
            return;
        for(int i=0;i<=m[elem[now]];i++){
            // i==0の時は追加しないとき
            if(i==0){
                _dfs(now+1,num_decided);
            }else{
                v1[num_decided+(i-1)] = elem[now];
                _dfs(now+1,num_decided+i);
            }
        }
    };
    _dfs(0,0);
    return v;
}

int main()
{
    int N=6,R=3;
    vector<int> elems{0,1,1,1,2,3};
    vector<vector<int>> c = combination(elems, R);
    for(auto i: c){
        for(int j: i){
            cout << j <<" ";
        }
        cout << endl;
    }
	return 0;
}
