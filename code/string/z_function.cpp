// 对于字符串a[1...len]计算其每一位的Z-Function(保存在f[]中)
// 其中f[i]表示a[]从第i位开始和前缀的最长匹配, 即a[1...f[i]] == a[i...(i+f[i]-1)]
// 需特别注意, 这里的字符串a[]下标是从1开始一直到len的
void Z_Function(char *a, int len, int *f) {
    f[1] = len;
    for(int i = 2, l = 0, r = 0; i <= len; ++i) {
        if(i <= r) f[i] = min(r-i+1, f[i-l+1]);
        else f[i] = 0;
        while(i+f[i]<=len && a[i+f[i]]==a[f[i]+1]) ++f[i];
        if(i+f[i]-1 > r) l = i, r = i+f[i]-1;
    }
}
