// 欧拉函数
// phi[1] = 1.
// 若p为质数, 则phi[p^k] = p^k - p^(k-1).
// 若gcd(m,n)=1, 则phi[m*n] = phi[m] * phi[n].
const int phi_len = 1e6;
int phi[phi_len+10];

void phi_maker() {
    memset(phi,0,sizeof(phi));
    phi[1] = 1;
    for(int i=2;i<=phi_len;++i) if(!phi[i]) {
        for(int k=i;k<=phi_len;k+=i) {
            if(!phi[k]) phi[k] = k;
            phi[k] = phi[k] / i * (i-1);
        }
    }
}

// O(√n)
LL Euler(int n) {
    LL res = n, a = n;
    for(int i=2; i*i<=a; ++i) {
        if(a%i == 0) {
            res = res/i*(i-1);
            while(a%i == 0) a /= i;
        }
    }
    if(a>1) res = res/a*(a-1);
    return res;
}
