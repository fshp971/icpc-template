// 直线相交
// 二元组<a,b>, <c,d>分别表示两条线段, 现在要求这两条线段的交点res
// 原理看代码就明白了
bool Line_Intersection(Point &a, Point &b, Point &c, Point &d, Point &res) {
    DB d1 = (a-c) ^ (d-c), d2 = (d-c) ^ (b-a);
    if(Cmp(d2) == 0) return false; // 平行无交点
    res = a + (b - a) * (d1 / d2);
    // 即令a点向向量ab方向移动 (d1/d2*|ab|) 的距离
    return true;
}

// 线段相交
// 此处的交点可以是线段的端点, 若不能在端点处相交则可以省去很多判断
// 两条线段不能完全重合 (总之就是要根据具体题目具体修改)
bool Segment_Intersection(Point &a, Point &b, Point &c, Point &d, Point &res) {
    Point v0 = b-a, v1 = c-a, v2 = d-a;
    if( Cmp(v0^v1) * Cmp(v0^v2) > 0) return false;
    v0 = d-c, v1 = a-c, v2 = b-c;
    if( Cmp(v0^v1) * Cmp(v0^v2) > 0) return false;
    // 以上的判断得到的两条线段可能会在同一直线上
    // 因此接下来要判断是否在端点处有交点
    if(Cmp((d-c) ^ (b-a)) == 0) {
        if(a == c || a == d) { res = a; return true; }
        if(b == c || b == d) { res = b; return true; }
        return false;
    }

    DB d1 = (a-c) ^ (d-c), d2 = (d-c) ^ (b-a);
    res = a + (b - a) * (d1 / d2);
    // 即令a点向向量ab方向移动 (d1/d2*|ab|) 的距离
    return true;
}
