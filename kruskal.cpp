/*
tag: 贪心 最小生成树 并查集 MST mst kruskal 最大边最小
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn=1003;
const int maxm=10004;
int n,m,f[maxn],k;
struct edge
{
    int x,y,w;
}s[maxm];
bool cmp_edge(edge x,edge y)
{
    return x.w<y.w;
}
int find(int x)
{
    if(x!=f[x]) return f[x]=find(f[x]);
    else return f[x];
}
void kruskal()
{
    int ans=0;
    for(int i=1;i<=n;i++) f[i]=i; //initialize
    sort(s+1,s+m+1,cmp_edge);

    for(int i=1;i<=m;i++)
    {
        int p=find(s[i].x);
        int q=find(s[i].y);
        if(q!=p)
        {
            ans+=s[i].w;
            f[q]=p;
        }
    }
    bool flag=true; // is connected?
    for(int i=1;i<n;i++)
    {
        if(find(i)!=find(i+1)) 
        {
            flag=false;
            break;
        }
    }
    if(flag)printf("%d\n",ans); // min sum
    else printf("?\n"); // is not connected
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>s[i].x>>s[i].y>>s[i].w;
    kruskal();
    return 0;
}
