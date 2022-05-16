// n条方程n个变量, 若有解则唯一, 无法判断无解情况
// 计算完成后A[i][n] (i = 0 ~ n-1) 共n个数即为方程的解
double A[maxn + 5][maxn + 5];
void Gauss(int n) {
    for(int i = 0; i < n; ++i) {
        int r = i;
        for(int j = i + 1; j < n; ++j)
            if(fabs(A[r][i]) < fabs(A[j][i])) r = j;
        if(r != i)
            for(int j = 0; j <= n; ++j) swap(A[i][j], A[r][j]);
        for(int j = i + 1; j < n; ++j) {
            for(int k = n; k >= i; --k)
                A[j][k] -= A[i][k]/A[i][i] * A[j][i];
        }
    }
    for(int i = n - 1; i >= 0; --i) {
        for(int j = i + 1; j < n; ++j)
            A[i][n] -= A[j][n] * A[i][j];
        A[i][n] /= A[i][i];
    }
}

// 高斯消元化阶梯型求解的个数
// 这一般是在剩余系中才会问这样的问题, 所以这里以(mod P)的剩余系来搞
// 化阶梯型的一般做法可以直接照着这个板修改得到
int A[maxn + 5][maxm + 5], Inv[maxP + 5]; // Inv[i]是i的逆元
void Gauss(int n, int m) { // 共有n条方程, m个变元
    int row = 0;
    for(int i = 0; i < m && row < n; ++i) {
        if(A[row][i] == 0) {
            int r = row;
            for(int j = row + 1; j < n; ++j)
                if(A[j][i] != 0) { r = j; break; }
            if(r == row) continue;
            for(int j = i; j <= m; ++j) swap(A[row][j], A[r][j]);
        }
        for(int j = row + 1; j < n; ++j)
            for(int k = m; k >= i; --k)
                A[j][k] = (A[j][k] - A[row][k]*Inv[A[row][i]]*A[j][i] % P + P) % P;
        ++row;
    }
    // 此时若A[row][m]~A[n-1][m]中有非零数, 则表示方程组无解
    // 否则该方程组的秩恰为row
    while(row < n) {
        if(A[row][m]) { puts("No answer"); break; } //无解
        ++row;
    }
}
