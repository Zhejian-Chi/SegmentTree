#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define MAXN 100010
#define INF 10000009
#define MOD 10000007
#define LL long long
#define in(a) a=read()
#define REP(i,k,n) for(long long i=k;i<=n;i++)
#define DREP(i,k,n) for(long long i=k;i>=n;i--)
#define cl(a) memset(a,0,sizeof(a))
inline long long read(){
    long long x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
inline void out(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) out(x/10);
    putchar(x%10+'0');
}
long long n,m,p;
long long input[MAXN];
struct node{
    long long l,r;
    long long sum,mlz,plz;
}tree[4*MAXN];
inline void build(long long i,long long l,long long r){
    tree[i].l=l;
    tree[i].r=r;
    tree[i].mlz=1;
    if(l==r){
        tree[i].sum=input[l]%p;
        return ;
    }
    long long mid=(l+r)>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    tree[i].sum=(tree[i<<1].sum+tree[i<<1|1].sum)%p;
    return ;
}
inline void pushdown(long long i){
    long long k1=tree[i].mlz,k2=tree[i].plz;
    tree[i<<1].sum=(tree[i<<1].sum*k1+k2*(tree[i<<1].r-tree[i<<1].l+1))%p;
    tree[i<<1|1].sum=(tree[i<<1|1].sum*k1+k2*(tree[i<<1|1].r-tree[i<<1|1].l+1))%p;
    tree[i<<1].mlz=(tree[i<<1].mlz*k1)%p;
    tree[i<<1|1].mlz=(tree[i<<1|1].mlz*k1)%p;
    tree[i<<1].plz=(tree[i<<1].plz*k1+k2)%p;
    tree[i<<1|1].plz=(tree[i<<1|1].plz*k1+k2)%p;
    tree[i].plz=0;
    tree[i].mlz=1;
    return ;
}
inline void mul(long long i,long long l,long long r,long long k){
    if(tree[i].r<l || tree[i].l>r)  return ;
    if(tree[i].l>=l && tree[i].r<=r){
        tree[i].sum=(tree[i].sum*k)%p;
        tree[i].mlz=(tree[i].mlz*k)%p;
        tree[i].plz=(tree[i].plz*k)%p;
        return ;
    }
    pushdown(i);
    if(tree[i<<1].r>=l)  mul(i<<1,l,r,k);
    if(tree[i<<1|1].l<=r)  mul(i<<1|1,l,r,k);
    tree[i].sum=(tree[i<<1].sum+tree[i<<1|1].sum)%p;
    return ;
}
inline void add(long long i,long long l,long long r,long long k){
    if(tree[i].r<l || tree[i].l>r)  return ;
    if(tree[i].l>=l && tree[i].r<=r){
        tree[i].sum+=((tree[i].r-tree[i].l+1)*k)%p;
        tree[i].plz=(tree[i].plz+k)%p;
        return ;
    }
    pushdown(i);
    if(tree[i<<1].r>=l)  add(i<<1,l,r,k);
    if(tree[i<<1|1].l<=r)  add(i<<1|1,l,r,k);
    tree[i].sum=(tree[i<<1].sum+tree[i<<1|1].sum)%p;
    return ;
}
inline long long search(long long i,long long l,long long r){
    if(tree[i].r<l || tree[i].l>r)  return 0;
    if(tree[i].l>=l && tree[i].r<=r)
        return tree[i].sum;
    pushdown(i);
    long long sum=0;
    if(tree[i<<1].r>=l)  sum+=search(i<<1,l,r)%p;
    if(tree[i<<1|1].l<=r)  sum+=search(i<<1|1,l,r)%p;
    return sum%p;
}
int main(){
    in(n);    in(m);in(p);
    REP(i,1,n)  in(input[i]);
    build(1,1,n); 

    REP(i,1,m){
        long long fl,a,b,c;
        in(fl);
        if(fl==1){
            in(a);in(b);in(c);
            c%=p;
            mul(1,a,b,c);
        }
        if(fl==2){
            in(a);in(b);in(c);
            c%=p;
            add(1,a,b,c);
        }
        if(fl==3){
            in(a);in(b);
            printf("%lld\n",search(1,a,b));
        }
    }
    return 0;
}
/*
4 1000
2 3 4 5
1 5
1 5 1
1 5 2
1 5
*/
