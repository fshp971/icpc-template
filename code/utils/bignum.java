// BigInteger
BigInteger a("123"); // 通过字符串构造
c = BigInteger.valueOf(456); // 通过整数构造
c = BigInteger.ONE; // 或者BigInteger.ZERO
c = a.add(b); // 加法
c = a.subtract(b); // 减法
c = a.multiply(b); // 乘法
c = a.divide(b); // 除法
c = a.gcd(b); // gcd(a,b)
c = a.abs();
c = a.mod(b); // 取模，a, b必须都是非负数
c = a.modPow(b,p); // a^b % p
// c = -1: a < b;
// c = 0: a = b;
// c = 1: a > b;
int c = a.compareTo(b);
String c = a.toString(); // 可以用于打印结果

// BigDecimal
// add(), subtract(), multiply(), abs(), compareTo()及构造函数和BigInteger类似
public BigDecimal divide(BigDecimal divisor, int scale, int roundingMode);
// scale表示计算规模（精度？长度？取大点就好了，比如30）
// roundingMode表示取整规则，有以下几种常用规则：
// ROUND_UP, ROUND_DOWN, ROUND_CEILING, ROUND_FLOOR, ROUND_HALF_UP（四舍五入）, ROUND_HALF_DOWN
