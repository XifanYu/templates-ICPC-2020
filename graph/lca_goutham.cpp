int tin[N], tout[N], par[N][logN], tim;

void dfs(int u, int p = -1)
{
    tin[u] = ++tim;
    par[u][0] = p;
    for (int i = 1; i < logN; i++)
        par[u][i] = (par[u][i-1] >= 0 ? par[par[u][i-1]][i-1] : -1);

    for (int v : adj[u])
        if (v != p)
            dfs(v, u);

    tout[u] = ++tim;
}

bool anc(int a, int b) { return tin[a] <= tin[b] and tout[a] >= tout[b]; }

int lca(int a, int b)
{
    if (anc(a, b)) return a;
    if (anc(b, a)) return b;
    for (int i = logN - 1; i >= 0; i--)
        if (par[a][i] >= 0 and !anc(par[a][i], b))
            a = par[a][i];
    return par[a][0];
}