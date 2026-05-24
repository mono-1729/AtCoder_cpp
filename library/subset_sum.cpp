//https://codeforces.com/contest/1856/problem/E2
//https://codeforces.com/contest/1856/submission/219130190
const ll _max_len=4e6+10;
template<ll _len=1>
std::vector<bool> fast_subset_sub_solver(std::vector<ll> &p,ll sum=-1){
    if(sum==-1){
        sum=0;
        for(auto x:p){
            assert(x>=0);
            sum+=x;
        }
    }
    assert(sum<=_max_len);
    if(sum>=_len){
        return fast_subset_sub_solver<std::min(_max_len,2*_len)>(p,sum);
    }
    for(auto x:p) assert(x>=0);
    std::bitset<_len> dp;
    std::vector<ll> q(sum+1);
    for(auto x:p) q[x]++;
    dp[0]=1;
    for(ll i=1;i<=sum;i++){
        if(q[i]>=1){
            if(0==(q[i]&1)) q[i]--,dp=(dp|(dp<<i));
            q[i]--,dp=(dp|(dp<<i));
            if(i*2<=sum&&2<=q[i]) q[i*2]+=q[i]/2;
        }
    }
    std::vector<bool> res(sum+1);
    for(ll i=0;i<=sum;i++) res[i]=dp[i];
    return res;
}