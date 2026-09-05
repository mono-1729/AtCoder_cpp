#include <vector>
#include <algorithm>
#include <utility>
#define ll long long

// Aが凸の場合
template<class Elem>
std::vector<std::pair<Elem, ll>> MinPlusConvolution_AIsConvex(
    const std::vector<Elem>& A,
    const std::vector<Elem>& B,
    Elem Inf
){
    ll n = A.size();
    ll m = B.size();
    ll z = n + m - 1;
    std::vector<std::pair<Elem, ll>> c(z, {Inf,-1});
    std::vector<ll> idx(z+1);
    c[0] = { A[0] + B[0], 0 };
    idx.back() = m-1;
    ll d = 1; while(d < z) d *= 2;
    for(ll q=d/2; q>0; q/=2){
        for(ll h=q; h<z; h+=q*2){
            ll l = h-q, r = std::min(h+q, z);
            idx[h] = idx[l];
            for(ll t=idx[l]; t<=idx[r]; t++){
                if(t<=h && h-t<n && B[t] + A[h-t] < c[h].first){
                    c[h] = { B[t] + A[h-t], h-t };
                    idx[h] = t;
                }
            }
        }
    }
    return c;
}

// Aが凹の場合

template<class Func, class Eval>
struct LiChaoTreeFlexible{
private:
    int xn;
    int N;
    std::vector<Func> V;
    std::vector<bool> visited;
    Func InfFunc;
    Eval ev;

    bool cmpat(Func fl, Func fr, int p){
        if(p >= xn) p = xn-1;
        return ev(fl, p) < ev(fr, p);
    }
public:
    
    LiChaoTreeFlexible(int n, Func inf, Eval eval)
        : xn(n)
        , InfFunc(std::move(inf))
        , ev(std::move(eval))
    {
        N = 1;
        while(N < n) N *= 2;
        V.assign(N*2, InfFunc);
        visited.assign(N*2, false);
    }
    
    void addSegment(int l, int r, Func f){
        if(l >= r) return;
        auto dfs = [&](int i,Func f,int a,int b,auto& dfs) -> void {
            visited[i] = true;
            if(i >= (int)V.size()) return;
            if(r <= a || b <= l) return;
            int m = (a+b)/2;
            if(!(l <= a && b <= r)){
                dfs(i*2,f,a,m,dfs);
                dfs(i*2+1,f,m,b,dfs);
                return;
            }
            if(cmpat(f, V[i], m)) std::swap(V[i],f);
            if(a + 1 == b) return;
            bool lessf_l = cmpat(f, V[i], a);
            bool lessf_r = cmpat(f, V[i], b-1);
            if(!lessf_l && !lessf_r) return;
            if(lessf_l) dfs(i*2,f,a,m,dfs);
            else dfs(i*2+1,f,m,b,dfs);
        };
        dfs(1,f,0,N,dfs);
    }
    
    void addLine(Func f){
        addSegment(0,N,f);
    }
    
    Func minFunc(int p){
        int i = 1;
        Func res = InfFunc;
        int l = 0, r = N;
        while(i < (int)V.size()){
            if(!visited[i]) break;
            if(cmpat(V[i], res, p)) res = V[i];
            int m = (l+r)/2;
            if(p < m){ i = i*2; r = m; }
            else{ i = i*2+1; l = m; }
        }
        return res;
    }
};

template<class Elem>
std::vector<std::pair<Elem, ll>> MinPlusConvolution_AIsConcave(
    const std::vector<Elem>& A,
    const std::vector<Elem>& B,
    Elem Inf
){
    using namespace std;
    ll N = (ll)A.size();
    ll M = (ll)B.size();
    std::vector<std::pair<Elem, ll>> C(N+M-1, {Inf,-1});
    for(ll s=0; s<M; s+=N+1){
        ll n = (M-s <= N) ? M-s : (N+1);
        auto ds1 = LiChaoTreeFlexible(N, 0,
            [&](ll a, ll b) -> Elem {
                if(b < a) return -Inf - a;
                return A[b-a] + B[s+a];
            });
        for(ll i=0; i<N; i++){
            if(i+s<M) ds1.addLine(i);
            ll k = ds1.minFunc(i);
            Elem fk = A[i-k] + B[s+k];
            if(fk < C[s+i].first) C[s+i] = {fk, i-k};
        }
        auto ds2 = LiChaoTreeFlexible(n-1, n-1,
            [&](ll a, ll b) -> Elem {
                b += 1;
                if(a < b) return -Inf + a;
                return A[N-1-(a-b)] + B[s+a];
            });
        for(ll i=n-1; i>=1; i--){
            ds2.addLine(i);
            ll k = ds2.minFunc(i-1);
            ll p = s + (N-1) + i;
            Elem fk = A[p-s-k] + B[s+k];
            if(fk < C[p].first) C[p] = {fk, p-s-k};
        }
    }
    return C;
}

int main(){

}