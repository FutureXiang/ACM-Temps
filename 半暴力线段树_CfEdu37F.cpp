#include <iostream>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstdio>
using namespace std;
const int maxn=300005;
int n,m;

struct seg
{
    long long w;
    bool keep;
}s[maxn*4];

int Divisor(int x) // 暴力求因子个数，用不着long long
{
    int cnt=0;
    int i;
    for(i=1;i*i<x;++i)
    {
        if(x/i*i==x)
            cnt+=2;//1,16 2,8
    }
    if(i*i==x) cnt++; //4
    return cnt;
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        scanf("%I64d",&s[now].w); // I64d on CF
        if(s[now].w==1ll||s[now].w==2ll) s[now].keep=true; // D(1)=1, D(2)=2. [1,2,1,2]=true.
        return;
    }
    int m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    s[now].w = s[now*2].w + s[now*2+1].w;
    if(s[now*2].keep && s[now*2+1].keep) s[now].keep=true; // sub keep
}
void update(int now,int l,int r,int ql,int qr)
{
    if(r<ql||l>qr) return;
    int m=(l+r)/2;
    if(ql<=l && r<=qr)
    {
        if(s[now].keep) return;
        if(l==r)
        {
            s[now].w = Divisor(s[now].w);
            if(s[now].w==1ll || s[now].w==2ll) s[now].keep=true;
            return;
        }
    }
    if(l==r) return;
    if(ql<=m) update(now*2,l,m,ql,qr);
    if(qr>m)  update(now*2+1,m+1,r,ql,qr);
    s[now].w = s[now*2].w + s[now*2+1].w;
    if(s[now*2].keep && s[now*2+1].keep) s[now].keep=true; // sub keep
}
long long query(int now,int l,int r,int ql,int qr)

{
    if(r<ql||l>qr) return 0ll;
    long long ans=0ll;
    if(ql<=l && r<=qr) return s[now].w;
    int m=(l+r)/2;
    if(l==r) return s[now].w;
    if(ql<=m) ans += query(now*2,l,m,ql,qr);
    if(qr>m)  ans += query(now*2+1,m+1,r,ql,qr);
    return ans;
}

int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    while(m--)
    {
        int q,l,r;
        scanf("%d%d%d",&q,&l,&r);
        if(q==1)
            update(1,1,n,l,r);
        else
            printf("%I64d\n",query(1,1,n,l,r)); //I64d on CF
    }
    return 0;
}
