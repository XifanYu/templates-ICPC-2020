int cost[N][N];
int lx[N], ly[N], xy[N], yx[N], q[N], sl[N], slx[N], pre[N];
bool S[N], T[N];

struct KM
{
    int n, mm;
    KM(int nv)
    {
        n = nv;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cost[i][j] = -inf;
    }
    void add(int x, int y, int c) { cost[x][y] = max(cost[x][y], c); }

    void upd()
    {
        int del = inf;
        for (int i = 0; i < n; i++)
            if (!T[i])
                del = min(del, sl[i]);
        for (int i = 0; i < n; i++)
        {
            if (S[i]) lx[i] -= del;
            if (T[i]) ly[i] += del;
            else sl[i] -= del;
        }
    }
    void upd(int x, int prevx)
    {
        S[x] = true, pre[x] = prevx;
        for (int y = 0; y < n; y++)
            if (lx[x] + ly[y] - cost[x][y] < sl[y])
                sl[y] = lx[x] + ly[y] - cost[x][y], slx[y] = x;
    }

    void aug()
    {
        if (mm == n) return;
        int x, y, root, qb = 0, qe = 0;
        for (int i = 0; i < n; i++) S[i] = T[i] = 0, pre[i] = -1;
        for (x = 0; x < n; x++)
            if (xy[x] == -1)
            {
                q[qe++] = root = x, pre[x] = -2, S[x] = true;
                break;
            }
        for (y = 0; y < n; y++)
            sl[y] = lx[root] + ly[y] - cost[root][y], slx[y] = root;
        while (true)
        {
            while (qb < qe)
            {
                x = q[qb++];
                for (y = 0; y < n; y++)
                    if (cost[x][y] == lx[x] + ly[y] && !T[y])
                    {
                        if (yx[y] == -1) break;
                        T[y] = true, q[qe++] = yx[y], upd(yx[y], x);
                    }
                if (y < n) break;
            }
            if (y < n) break;
            upd();
            for (qb = qe = y = 0; y < n; y++)
                if (!T[y] && sl[y] == 0)
                    if (yx[y] == -1)
                    {
                        x = slx[y];
                        break;
                    }
                    else
                    {
                        T[y] = true;
                        if (!S[yx[y]]) q[qe++] = yx[y], upd(yx[y], slx[y]);
                    }
            if (y < n) break;
        }
        if (y < n)
        {
            mm++;
            for (int cx = x, cy = y, ty; cx != -2; cx = pre[cx], cy = ty)
                ty = xy[cx], yx[cy] = cx, xy[cx] = cy;
            aug();
        }
    }

    int go()
    {
        int ret = 0;
        mm = 0;
        for (int i = 0; i < n; i++) xy[i] = yx[i] = -1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                lx[i] = max(lx[i], cost[i][j]);
        aug();
        for (int x = 0; x < n; x++) ret += cost[x][xy[x]];
        return ret;
    }
};