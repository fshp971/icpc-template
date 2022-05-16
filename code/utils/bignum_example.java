// hdu 4624
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    static final int maxn = 50;
    public static void main(String[] args) {
        long [][][]f = new long[maxn+5][2][maxn*maxn+5];
        BigDecimal []E = new BigDecimal[maxn+5];
        f[0][0][0] = 1;
        for(int i=0; i<=maxn; ++i)
            for(int k=0; k<=(i+1)*i/2; ++k)
                for(int t=i+1; t<=maxn; ++t) {
                    f[t][0][k+(t-i)*(t-i-1)/2] += f[i][1][k];
                    f[t][1][k+(t-i)*(t-i-1)/2] += f[i][0][k];
                }
        for(int i=1; i<=maxn; ++i) {
            E[i] = new BigDecimal("0");
            for(int k=0; k<=i; ++k) {
                for(int j=0; j<=(i+1)*i/2; ++j) {
                    if( j+(i-k+1)*(i-k)/2 == (i+1)*i/2) continue;
                    BigDecimal p = new BigDecimal("1");
                    BigDecimal a = new BigDecimal(j + (i-k+1)*(i-k)/2);
                    BigDecimal b = new BigDecimal((i+1)*i/2);
                    p = p.subtract( a.divide(b, 30, BigDecimal.ROUND_HALF_UP) );
                    BigDecimal cont = new BigDecimal(f[k][1][j] - f[k][0][j]);
                    E[i] = E[i].add( cont.divide(p, 30, BigDecimal.ROUND_HALF_UP) );
                }
            }
        }
        Scanner in = new Scanner(System.in);
        int T = in.nextInt(), x;
        for(int t=1; t<=T; ++t) {
            x = in.nextInt();
            System.out.printf("%.15f\r\n", E[x]);
        }
    }
}
