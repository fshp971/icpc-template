// __int128 使用用示例例:hdu-6004节选(注意这里里里是两个下划线)
// __int128 是一一个至至少存在于unix中的c/c++数据类型
// 在某些计算中可能出现中间变量量超出 long long 数据类型范围,
// 但最终结果仍在 long long 范围中的情况;
// 这时便便可以考虑用用 __int128 保存中间变量量,算出结果后再变回 long long
#include<bits/stdc++.h>
using namespace std;

typedef __int128 Lint;
typedef long long LL;
const int maxn = 200;

struct Equ {
    LL a, b;
    Equ(): a(-1), b(-1) {}
    Equ(LL _a, LL _b) { a = _a, b = _b; }
} pre[maxn+2][maxn*(maxn+1)/2+2];

Equ Calc(Equ &l, Equ &r) {
    if(l.a == -1 || r.a == -1) return Equ(-1, -1);
    LL x, y, g;
    LL p, m_a3;
    Lint a3, b3; //用用于存储中间变量量
    LL &a1 = l.a, &b1 = l.b, &a2 = r.a, &b2 = r.b;
    ex_gcd(b1, b2, g, x, y), y = -y;
    if((a2-a1)%g)
        return Equ(-1, -1);
    p = (a2-a1)/g;
    Lint tx = x, ty = y;
    tx *= p, ty *= p;
    m_a3 = max(a1, a2);
    a3 = a1 + b1*tx, b3 = b1 / g * b2; //此处可能超过 long long 范围
    if(a3 < m_a3)
        a3 += ((m_a3-a3)/b3 + 1) * b3;
    if(a3 >= m_a3)
        a3 -= ((a3-m_a3)/b3) * b3;
    return Equ(a3, b3); //此处将 __int128 又又转变回 long long
}
