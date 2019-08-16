bool was[N];
long long cap[N][N];

struct FF
{
    int n;
    FF(int nv) { n = nv; }
    void add(int x, int y, long long c) { cap[x][y] += c; }
    bool push(int u, int sink, long long capacity)
    {
        if (u == sink) return true;
        if (was[u]) return false;
        was[u] = true;
        for (int v = 0; v < n; v++)
            if (cap[u][v] >= capacity and push(v, sink, capacity))
                return cap[u][v] -= capacity, cap[v][u] += capacity, true;
        return false;
    }
    long long flow(int source, int sink)
    {
        long long ret = 0, capacity = inf;
        while (capacity > 0)
        {
            if (push(source, sink, capacity)) ret += capacity;
            else capacity /= 2;
            for (int i = 0; i < n; i++) was[i] = false;
        }
        return ret;
    }
};