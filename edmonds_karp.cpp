#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 2 * 200; /* max number of vertices - adjust */
const int M = 2 * 1200; /* max number of edges - adjust */
const int INF = 1<<30;

int flow;
int bottleneck;
int n, m, e;
int s, t;
int x, y, w;
int p[N], edge[N];
int last[N];
int prev[M];
int to[M];
int c[M], f[M];

/* add directed edge x->y with capacity w */
void add(int x, int y, int w)
{   prev[e] = last[x];
    last[x] = e;
    to[e] = y;
    c[e] = w;
    f[e] = 0;
    e++;
    prev[e] = last[y];
    last[y] = e;
    to[e] = x;
    c[e] = 0;
    f[e] = 0;
    e++;
}

/* find augmenting path in residual graph */
bool path(int u, int v)
{   queue<int> Q;
    int C, F;
    
    for(int i = 0; i < n; i++) p[i] = -1;
    Q.push(u);
    p[u] = u;
    while(!Q.empty())
    {   x = Q.front(), Q.pop();
        if(x == v) return true;
        for(int i=last[x]; i!=-1; i=prev[i])
        {   y = to[i];
            F = f[i];
            C = c[i];
            if(p[y] == -1 && C > F)
            {   p[y] = x;
                edge[y] = i;
                Q.push(y);
            }
        }
    }
    return false;
}

/* send flow through augmenting path */
int send(int u, int v)
{   bottleneck = INF;
    int x, y, index, sym;
    y = v;

    while(p[y] != y)
    {   x = p[y];
        index = edge[y];
        bottleneck = (bottleneck > c[index]-f[index] ? c[index]-f[index] : bottleneck);
        y = x;
    }

    y = v;
    while(p[y] != y)
    {   x = p[y];
        index = edge[y];
        f[index] += bottleneck;
        f[index^1] -= bottleneck;
        y = x;
    }

    return bottleneck;
}

int main(void)
{   scanf("%d %d", &n, &m); /* vertices, edges */

    /* build graph */
    memset(last, 0, sizeof(last));
    for(int i = 0; i < m; i++)
    {   scanf("%d %d %d", &x, &y, &w);
        add(x-1, y-1, w);
    }
    
    flow = 0;
    while(path(s, t))
        flow += send(s, t);
    printf("%d\n", flow);
    
    return 0;
}
