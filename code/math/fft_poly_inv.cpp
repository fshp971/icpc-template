// 给出多项式a(x), 求多项式b(x)使得 a(x)*b(x) = 0 (mod x^(deg))
// 因此调用前应确保已给出a(x)的第0 ~ (deg-1)项系数并填入a[]数组
// 数组空间一定要开够(2倍原长且为2的次幂)
// 若使用FFT一定要调用Init()初始化原根
const int md = 1e9+7; // 自行设置模数
const int maxn = 1 << 18;

LL temp[maxn+5];
void ConvInv(int deg, LL *a, LL *b) {
    if(deg == 1) {
        b[0] = PowMod(a[0], md-2);
        // 由此可以看出, a(x)是否存在逆元只取决于a(x)的常数项是否存在逆元
        return;
    }
    ConvInv((deg+1)>>1, a, b); // 递归求解

    // 因在这一步时相乘涉及的多项式次数均不超过(deg-1)
    // 故应有len >= deg*2-1
    int len = 1;
    while(len < deg*2-1) len <<= 1; 

    // 由于是mod x^(deg), 故当前只需要a(x)的第0 ~ (deg-1)项系数(其他相当于被模掉了)
    for(int i = 0; i < deg; ++i) temp[i] = a[i];
    for(int i = deg; i < len; ++i) temp[i] = 0;

    // 要手动把b(x)的不存在项清成0, 否则怕FFT时出现精度问题(NTT大概没有这样的问题)
    for(int i = (deg+1)>>1; i < len; ++i) b[i] = 0;

    // 计算temp[]和b[]的卷积并将结果保存回temp[]
    // 此处使用FFT模大素数模板, 每次卷积需要4次FFT, 速度较快, 但可能存在潜在的精度问题
    // 也可以使用三模数NTT+CRT, 这样据说每个递归层需要15次NTT, 速度较慢, 但绝对没有精度问题
    Conv(temp, b, temp, len);
    for(int i = deg; i < len; ++i) temp[i] = 0; // 再次手动清0不存在项
    Conv(temp, b, temp, len); // 再次计算temp[]*b[]并将结果保存回temp[]
    for(int i = 0; i < deg; ++i)
        b[i] = (b[i]*2 - temp[i] + md) % md; // 计算最终结果(注意次数为0 ~ deg-1)
}
