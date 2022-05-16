typedef long long LL;
int gcd(LL a,LL b) { return b ? gcd(b, a%b) : a; }

// 调用时需保证 a >= b >= 0, 且提供的 g, x, y 需为实际存在的变量
// g = gcd(a,b), 计算结果满足 x*a + y*b = g = gcd(a,b)
// 需要注意 (x, y) 并不唯一
void ex_gcd(LL a,LL b,LL &g,LL &x,LL &y) {
    if(b==0){ g = a; x = 1; y = 0; }
    else{ ex_gcd(b,a%b,g,y,x); y -= (a/b)*x; }
}
