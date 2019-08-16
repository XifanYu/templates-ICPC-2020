int last[N], dist[N], cur[N], q[N];
int ff[4 * M], pred[4 * M];
long long cap[4 * M];

struct dinic
{
    int n, m;
    dinic(int nv)
    {
        n = nv, m = 0;
        for (int i = 0; i < n; i++) last[i] = -1;
    }
    void add(int x, int y, long long c)
    {
        ff[m] = y, cap[m] = c, pred[m] = last[x], last[x] = m++;
        ff[m] = x, cap[m] = 0, pred[m] = last[y], last[y] = m++;
    }
    long long push(int u, int sink, long long flow)
    {
        if (u == sink) return flow;
        for (int& e = cur[u]; e >= 0; e = pred[e])
        {
            int v = ff[e];
            if (cap[e] > 0 and dist[u] + 1 == dist[v])
                if (long long aug = push(v, sink, min(flow, cap[e])))
                    return cap[e] -= aug, cap[e^1] += aug, aug;
        }
        return 0;
    }
    long long flow(int source, int sink)
    {
        long long ret = 0;
        while (true)
        {
            for (int i = 0; i < n; i++) cur[i] = last[i], dist[i] = -1;

            int qs = 0, qe = 0;
            q[qe++] = source;
            dist[source] = 0;
            while (qs < qe)
            {
                int u = q[qs++];
                for (int e = last[u]; e >= 0; e = pred[e])
                {
                    int v = ff[e];
                    if (cap[e] > 0 and dist[v] < 0)
                        q[qe++] = v, dist[v] = dist[u] + 1;
                }
            }
            if (dist[sink] < 0) break;
            while (long long aug = push(source, sink, inf)) ret += aug;
        }
        return ret;
    }
};