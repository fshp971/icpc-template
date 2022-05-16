// 计算n^(1/m)像下取整
// 一坨括号仔细核对千万别打错
import java.io.*;
import java.util.*;
import java.math.*;
public class Main {
    public static BigInteger sqrt(BigInteger n, int m) {
        if (n.compareTo(BigInteger.ONE) <= 0 || m <= 1) return n;
        BigInteger now = n.shiftRight((n.bitLength() - 1) * (m - 1) / m), last;
        do {
            last = now;
            // ( last*(m-1) + n/(last^(m-1)) ) / m;
            now = last.multiply(
                    BigInteger.valueOf(m-1)
                ).add(n.divide(last.pow(m-1))).divide(BigInteger.valueOf(m));
        } while (now.compareTo(last) < 0);
        return last;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedInputStream(System.in));
        BigInteger n = in.nextBigInteger();
        int m = in.nextInt();
        System.out.println( sqrt(n,m) );
        in.close();
        return;
    }
}
