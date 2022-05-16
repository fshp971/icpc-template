typedef double DB; // 方便随时修改
const DB eps = 1e-10;

// -1: a<0;  0: a==0;  1: a>0;
int Cmp(const DB &a) {
    if(fabs(a) < eps) return 0;
    return a<0 ? -1 : 1;
}

struct Point {
    DB x, y;
    Point() {}
    Point(DB _x, DB _y) { x = _x, y = _y; }
    DB operator * (const Point &a) const { return x*a.x + y*a.y; } // 点乘
    DB operator ^ (const Point &a) const { return x*a.y - y*a.x; } // 叉乘
    Point operator + (const Point &a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point &a) const { return Point(x-a.x, y-a.y); }
    Point operator * (const DB &a) const { return Point(x*a, y*a); }
    Point operator / (const DB &a) const { return Point(x/a, y/a); }
    bool operator == (const Point &a) const { return Cmp(x-a.x) == 0 && Cmp(y-a.y) == 0; }
    DB Mod() const { return sqrt(x*x + y*y); }
};
