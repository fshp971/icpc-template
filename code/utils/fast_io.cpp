#include<cstdio>
//BUAA输入挂，可读__int128
namespace FastIO {
    #define BUF_SIZE 100000 // 缓冲区大小可修改
    bool IOError = 0; // IOError == false 时表示处理到文件结尾
    inline char NextChar() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOError = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool Blank(char c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t';
    }

    template<class T> inline void Read(T &x) {
        char c;
        while(Blank(c = NextChar()));
        if(!IOError) {
            for(x = 0; '0' <= c && c <= '9'; c = NextChar())
                x = (x << 3) + (x << 1) + c - '0';
        }
    }
}
