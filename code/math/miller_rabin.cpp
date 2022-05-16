// Miller Rabin 素性检测
// Pollard-Rho 大数分解
// 使用前请仔细阅读每一部分的说明
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// 一系列工具函数
LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }
// 如果为保险可以使用较慢但没有精度问题的类快速幂方法
// 不到最后时刻绝对不能使用自然溢出法, 误差极大, 极易导致Miller-Rabin判断错误进而引起TLE
// 如果没有__int128, 应使用类似快速幂的方法计算MulMod
LL MulMod(LL a,LL b,LL c) { return ((__int128)a) * b % c; }
LL PowMod(LL a, LL b, LL p) {
    LL r = 1 % p;
    while(b) {
        if(b&1) r = MulMod(r,a,p);
        a = MulMod(a,a,p);
        b >>= 1;
    }
    return r;
}

// Miller Rabin 素性检测(原理基于二次剩余)
// 返回为true表示n(极可能)是素数, 返回为false表示n一定不是素数
// 亦即, Miller Rabin的检测方法只有可能把合数判成素数, 但一定不会把素数判成合数
//
// MaxTry表示尝试次数, 每次尝试随机一个在1~(n-1)的整数a来判断(使用了rand()函数)
// 若n为合数, 可以证明每次尝试判断将n判错(判为素数)的概率不超过1/2
// 因此尝试MaxTry次后将合数判为素数的概率不超过1/(2^MaxTry)
//
// MaxTry是可以调节的参数, 不过一般不太影响速度, 调高可以提高正确性
const int MaxTry = 30;

bool MillerRabin(LL n) {
    if(n==2) return true;
    if(n==0 || n==1 || !(n&1)) return false;
    LL u = n-1, t = 0;
    while((u&1) == 0) u >>= 1, ++t;
    for(int s = 1; s <= MaxTry; ++s) {
        LL a = rand() % (n-1) + 1;
        LL x = PowMod(a, u, n);
        for(int i = 1; i <= t; ++i) {
            LL tx = MulMod(x, x, n);
            if(tx==1 && x!=1 && x!=n-1) return false;
            x = tx;
        }
        if(x!=1) return false;
    }
    return true;
}

// Pollard-Rho 大数分解
//
// 递归将n拆成tot素因子, 并将结果保存在deco[1~tot]中
// 将重复的素因子也一并拆出, 且结果无序, 需自行排序
// 调用前tot记得清零
//
// 本质上就是一个有一定道理的随机乱搞
// 其中(MulMod(x,x,n)+c)%n是一个近似的随机函数
// 此非算法导论原版Pollard-Rho, 但思想是一样的
// 此改良版速度非常快(测板题: hdu-4344)
//
// 由于此算法用的 rand()+while(), 所以有一定机率会一直找不到解最终TLE
// 如果TLE, 在确保代码正确的情况下, 可以尝试多次提交
// 或者可以尝试将MulMod()替换成纯整数运算的版本, 防止精度问题
// 此模板至少能保证2^63以内的正确性
int tot;
LL deco[100];

void PollardRho(LL n) {
    if(n == 1) return;
    if(MillerRabin(n)) { deco[++tot] = n; return; }
    while(1) {
        LL c = rand() % (n-1) + 1;
        LL x = rand() % n;
        LL y = (MulMod(x,x,n)+c) % n;
        while(x != y) { // 关键终止条件, 不然容易陷入死循环
            LL d = Gcd(abs(x-y), n);
            if(d != 1) {
                // 找出的d仅保证d!=1且d!=n, 不一定是素因子, 因此还需要继续递归分解
                PollardRho(d);
                PollardRho(n/d);
                return;
            }
            x = (MulMod(x,x,n)+c) % n;
            // 相当于y每次多走1步, 即Floyd判圈(所以说, 变量名别打错啊)
            y = (MulMod(y,y,n)+c) % n;
            y = (MulMod(y,y,n)+c) % n;
        }
    }
}

int main() {
    srand(time(NULL));
    // 调用例子, 对n进行因数分解
    LL n; scanf("%lld", &n);
    tot = 0; // tot赋值为0
    PollardRho(n);
    sort(deco+1, deco+1+tot); // 自行排序保证有序, 其中包括重因子
    return 0;
}
