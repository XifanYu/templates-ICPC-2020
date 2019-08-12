#include<bits/stdc++.h>
using namespace std;

#define maxn 1111
const int inf = 1000000000;

struct edge
{
    int to, cap, rev;
    edge(int to = 0, int cap = 0, int rev = 0): to(to), cap(cap), rev(rev) {}
};

vector<edge> g[maxn];
int level[maxn], iter[maxn];
int n, m, e, v;
int S, T;

void add_edge(int from, int to, int cap)
{
    g[from].push_back(edge(to, cap, g[to].size()));
    g[to].push_back(edge(from, 0, g[from].size() - 1));
}

bool bfs()
{
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(S);
    level[S] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); i++)
        {
            edge& e = g[v][i];
            if (e.cap && level[e.to] == -1)
            {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
    return level[T] != -1;
}

int dfs(int v, int f)
{
    if (v == T)
    {
        return f;
    }
    for (int& i = iter[v]; i < g[v].size(); i++)
    {
        edge& e = g[v][i];
        if (e.cap && level[e.to] > level[v])
        {
            int d = dfs(e.to, min(f, e.cap));
            if (d > 0)
            {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int maxflow()
{
    int ans = 0;
    while (bfs())
    {
        memset(iter, 0, sizeof(iter));
        int f;
        while (true)
        {
            f = dfs(S, inf);
            if (f == 0)
            {
                break;
            }
            ans += f;
        }
    }
    return ans;
}

