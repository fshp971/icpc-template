const int maxn = 1e3;
int SG[maxn+10];

void SG_cal(int x, int len) {
    bool vis[len+10];
    SG[0] = x;  // set the initial status of SG[0]
    for(int i = 1; i <= len; ++i) {
        memset(vis, 0, sizeof(vis));
        // travel every sub-status of i
        for(k = head[i]; k != tail[i]; k=nex[i])
            vis[SG[k]] = true;
        for(int k = 0; ; ++k)
            if(!vis[k]) {
                SG[i] = k;
                break;
            }
    }
    return;
}
