#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void BFS(vector < int > ke[1000], int n, int m, int d[1000])
{
    queue < int > qu;
    qu.push(1);
    d[1] = 1;
    while (!qu.empty())
    {
        int u = qu.front();
        qu.pop();
        for (int i = 0; i < ke[u].size(); i++)
        {
            int v = ke[u][i];
            if (d[v] == 0)
            {
                d[v] = d[u] + 1;
                qu.push(v);
            }
            if (v == n)
                return;
        }
    }
}
int main(int argc, const char* argv[])
{
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int m, n, d[1000];
        bool F[1000];
        vector < int > ke[1000];
        memset(d, 0, sizeof(d));
        cin >> n >> m;
        for (int j = 0; j < m; j++)
        {
            int x, y;
            cin >> x >> y;
            /*We use vector to store the adjacent edge of vertex i as j and vice versa*/
            ke[x].push_back(y);
            ke[y].push_back(x);
        }
        BFS(ke, n, m, d);
        cout << d[n] - 1 << endl;
    }
    return 0;
}