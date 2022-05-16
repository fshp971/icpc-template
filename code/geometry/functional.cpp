// 返回三角形外心, 小心别抄错板子
Point Circumcenter(Point &a, Point &b, Point &c) {
    DB a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2.0;
    DB a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2.0;
    DB d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1*b2 - c2*b1) / d, a.y + (a1*c2 - a2*c1) / d);
}

DB Dist(Point &a, Point & b) { return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); }

// 点的最小圆覆盖
void MinCoverCircle(vector<Point> &seg, Point &O, DB &R) {
    // 将点随机排序, 这样能保证总算法期望复杂度O(n)
    random_shuffle(seg.begin(), seg.end());
    int i, k, j, n = seg.size();
    for(O = seg[0], R = 0, i = 1; i < n; ++i) if(Dist(O,seg[i]) > R+eps) {
        for(O = seg[i], R = 0, k = 0; k < i; ++k) if(Dist(O,seg[k]) > R+eps) {
            O = (seg[i] + seg[k]) / 2, R = Dist(O, seg[i]);
            for(j = 0; j < k; ++j) if(Dist(O,seg[j]) > R+eps)
                O = Circumcenter(seg[i], seg[k], seg[j]), R = Dist(O,seg[i]);
        }
    }
}
