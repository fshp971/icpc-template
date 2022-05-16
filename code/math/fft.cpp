#include<bits/stdc++.h>
//#include<complex>
using namespace std;

//若使用自己定义的复数速度貌似会略快
typedef complex<double> Comp;
const double PI = acos(-1.0);

const int Bin = 17, maxn = 1<<Bin;

//手写复数, 比STL复数快很多
struct Comp {
    double re, im;
    Comp(): re(0), im(0) {}
    Comp(const double _re, const double _im) { re = _re; im = _im; }
    Comp operator+(const Comp &a) { return Comp(re+a.re, im+a.im); }
    Comp operator-(const Comp &a) { return Comp(re-a.re, im-a.im); }
    Comp operator*(const Comp &a) { return Comp(re*a.re-im*a.im, re*a.im+im*a.re); }
    Comp operator*(const double &a) { return Comp(re*a, im*a); }
    Comp operator/(const double &a) { return Comp(re/a, im/a); }
    void operator*=(const Comp &a) { (*this) = (*this) * a; }
    void operator+=(const Comp &a) { re += a.re; im += a.im; }
    void operator*=(const double &a) { re*=a; im*=a; }
    void operator/=(const double &a) { re/=a; im/=a; }
    Comp conj() { return Comp(re, -im); }
};

//预处理单位根, 可以提高精度, 但速度可能会变慢
vector<Comp> ww[Bin + 2];
void Init() {
    for(int i = 1, l = 2; l <= maxn; ++i, l <<= 1) {
        for(int k = 0; k < l/2; ++k)
            ww[i].push_back( Comp( cos(PI*2*k/l), sin(PI*2*k/l) ) );
    }
}

// type=1为DFT运算, type=-1为DFT逆运算
void FFT(Comp *a, int len, int type) {
    int i, j, k, l, tt;
    for(i = 1, j = len>>1; i < len-1; ++i) {
        if(i < j) swap(a[i], a[j]);
        k = len>>1;
        while(j >= k) j -= k, k >>= 1;
        j += k;
    }
    Comp var, u, v;
    for(l = 2, tt = 1; l <= len; l <<= 1, ++tt) {
        for(k = 0; k < len; k += l) {
            for(i = k; i < k+l/2; ++i) {
                var = ww[tt][i-k];
                if(type == -1) var.im = -var.im;
                u = a[i], v = var * a[i+l/2];
                a[i] = u+v, a[i+l/2] = u-v;
            }
        }
    }
    // 不预处理单位根时的做法
    // for(l = 2; l <= len; l <<= 1) {
    //     step = Comp( cos(PI*2 / l * type), sin(PI*2 / l * type) );
    //     for(k = 0; k < len; k += l) {
    //         var = Comp(1,0);
    //         for(i = k; i < k+l/2; ++i) {
    //             u = a[i], v = var * a[i+l/2];
    //             a[i] = u+v, a[i+l/2] = u-v;
    //             var *= step;
    //         }
    //     }
    // }
    if(type == -1) for(i = 0; i < len; ++i) a[i] /= len;
}

int main() {
    Init(); // 切记要预处理单位根
    // n必须是2的幂, 若不足则在后面补0
    // n指的是FFT后算出的结果的多项式长度, 故n >= len(aa) + len(bb)
    int n = 1<<10;
    // aa[i]表示x^i项的系数, bb[i]类似
    Comp aa[n+5], bb[n+5];
    FFT(aa, n, 1);
    FFT(bb, n, 1);
    for(int i=0; i<n; ++i)
        aa[i] *= bb[i];
    FFT(aa, n, -1);
    return 0;
}
