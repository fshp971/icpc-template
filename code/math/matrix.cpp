typedef long long LL;
const int maxn = 10;

struct Matrix {
    int row, col;
    LL mat[maxn+5][maxn+5];
    // 如果懒得写自定义初始化, 那到时记得要手动初始化mat[][]
    Matrix(): row(0), col(0) { memset(mat, 0, sizeof(mat)); }
    void clear(int _row = 0, int _col = 0) {
        row = _row, col = _col;
        memset(mat, 0, sizeof(mat));
    }
    Matrix operator*(const Matrix &a) {
        Matrix res;
        res.row = row, res.col = a.col;
        for(int i=0; i<row; ++i) {
            for(int k=0; k<col; ++k) {
                if(mat[i][k] == 0) continue;
                for(int j=0; j<a.col; ++j)
                    // 可能要取模
                    res.mat[i][j] += mat[i][k]*a.mat[k][j];
            }
        }
        return res;
    }
    void output() {
        printf("row = %d, col = %d\n", row, col);
        for(int i=0; i<row; ++i) {
            for(int k=0; k<col; ++k)
                std::cout << mat[i][k] << " ";
            printf("\n");
        }
        printf("\n-------------------------\n\n");
    }
};
