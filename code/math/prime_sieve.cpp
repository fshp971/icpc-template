const int max_len = 1e9;
bool P[max_len+10];

void prime_maker() {
    memset(P,0,sizeof(P));
    int len = max_len;
    // p[1] = false;
    for(int i=2;i*i<=len;++i) if(!P[i]) {
        for(int j=i;i*j<=len;++j) if(!P[j])
            for(long long k=i*j;k<=len;k*=j) P[k]=true;
    }
}
