from collections import defaultdict
n=int(input())
a=list()
d=defaultdict(int)
mod=216063822110665427813261110433*998244353
for i in range(n):
    x=int(input())%mod
    a.append(x)
    d[a[i]]+=1
ans=0
for i in range(n):
    for j in range(n):
        ans+=d[(a[i]*a[j])%mod]
print(ans)
