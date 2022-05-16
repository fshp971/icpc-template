// copy from http://uoj.ac/submission/255151
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

namespace SA{

const int MAXN = 1e5 + 10; // 字符串长度上限

// sa[]表示后缀数组, 下标0~n, 其中sa[0]表示终止字符(字典序最小)
// rk[i]表示suffix(i)对应的排名
// ht[i]表示suffix(sa[i-1])与suffix(sa[i])的LCP长度
int sa[MAXN],rk[MAXN],ht[MAXN],s[MAXN<<1],t[MAXN<<1];
int p[MAXN],b[MAXN],cur[MAXN];
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
void inducedsort(int n, int n1, int m, int *s, int *t, int *v) {
    fill_n(b,m,0),fill_n(sa,n,-1);
    for(int i=0;i<n;i++) b[s[i]]++;
    for(int i=1;i<m;i++) b[i] += b[i-1];
    for(int i=0;i<m;i++) cur[i] = b[i]-1;
    for(int i=n1-1;i>=0;--i) pushS(v[i]);
    for(int i=1;i<m;i++) cur[i] = b[i-1];

    // 自行修改部分, 为防止越界. 如果出锅了再改回来
    //for(int i=0;i<n;i++) if(sa[i]>0&&t[sa[i]-1]))pushL(sa[i]-1);
    for(int i=0;i<n;i++) if(sa[i]>0&&(sa[i]==0||t[sa[i]-1]))pushL(sa[i]-1);

    for(int i=0;i<m;i++) cur[i] = b[i]-1;

    // 自行修改部分, 为防止越界. 如果出锅了再改回来
    //for(int i=n-1;i>=0;--i) if(sa[i]>0&&!t[sa[i]-1])pushS(sa[i]-1);
    for(int i=n-1;i>=0;--i) if(sa[i]>0&&(sa[i]==0||!t[sa[i]-1]))pushS(sa[i]-1);
}

void sais(int n,int m,int *s,int *t,int *p) {
    int n1 = t[n] = 0,*s1 = s+n,ch = rk[0] = -1;
    for(int i = n-1;~i;--i) t[i] = s[i]==s[i+1]?t[i+1]:s[i]>s[i+1];
    for(int i = 0;i<n;i++) rk[i] = (!t[i]&&t[i-1])?(p[n1]=i,n1++):-1;
    inducedsort(n,n1,m,s,t,p);
    for(int i = 0,x,y;i<n;i++) if(~(x = rk[sa[i]])) {
        if(ch < 1 || p[x+1] - p[x] != p[y+1] - p[y]) ch++;
        else for(int j=p[x],k=p[y];j<=p[x+1];j++,k++)
            if(((s[j]<<1)|t[j])!=((s[k]<<1)|t[k])){ch++;break;}
        s1[y=x] = ch;
    }
    if(ch+1<n1) sais(n1,ch+1,s1,t+n,p+n1);
    else for(int i = 0;i<n1;i++) sa[s1[i]] = i;
    for(int i = 0;i<n1;i++) s1[i] = p[sa[i]];
    inducedsort(n,n1,m,s,t,s1);
}

template<typename T>
int mapCharToInt(int n,const T *str) {
    int m = *max_element(str,str+n);
    fill_n(rk,m+1,0);
    for(int i = 0;i<n;i++) rk[str[i]] = 1;
    for(int i = 1;i<=m;i++) rk[i] += rk[i-1];
    for(int i = 0;i<n;i++) s[i] = rk[str[i]]-1;
    return rk[m];
}


// 这份GetHeight和前面倍增排序中所用的GetHeight是有区别的
// 具体区别在于长度n是否包含终止字符
void getheight(int n) {
    int i, j, k = 0;
    for(i = 0; i < n; ++i) rk[sa[i]] = i;
    for(i = 0; i < n-1; ++i) { //由于rk[n-1] = 0, 故无需考虑
        if(k) --k;
        j = sa[rk[i] - 1];
        while(s[i+k] == s[j+k]) ++k;
        ht[rk[i]] = k;
    }
}

template<typename T>
void BuildSA(int n,const T *str) { //str[n] miniuium
    int m = mapCharToInt(++n,str);
    sais(n,m,s,t,p);
    getheight(n);
}

}

const int maxn = 1e5;

int n;
char str[maxn + 5];

int main(){
    scanf("%s", str);
    n = strlen(str); // 字符串下标从0开始, 第n位放终止字符
    str[n] = '\0'; // 显式的放置终止字符
    SA::BuildSA(n, str); // 调用方式
    for(int i = 1;i<=n;i++)
        printf("%d%c", SA::sa[i]+1, (i==n)?'\n':' ');
    for(int i = 2;i<=n;i++)
        printf("%d%c", SA::ht[i], (i==n)?'\n':' ');
    return 0;
}
