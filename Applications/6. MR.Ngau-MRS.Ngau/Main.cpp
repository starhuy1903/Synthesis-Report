#include <iostream>
#include <vector>
using namespace  std;
void DIJKTRA(int N, vector < int > ke[100], int a[][100], int S, int d[])
{
    int MIN = 10000, u;
    bool F[1000];

    for (int i = 1; i <= N; i++)
    {
        d[i] = 10000;
        F[i] = 0;
    }

    d[S] = 1;

    while (true)
    {
        u = 0;
        for (int i = 1; i <= N; i++)
            if (F[i] == 0 && MIN > d[i])
            {
                MIN = d[i];
                u = i;
            }
        if (u == 0) break;
        F[u] = 1;
        for (int j = 0; j < ke[u].size(); j++)
        {
            int v = ke[u][j];
            if (F[v] == 0 && d[v] > d[u] + a[u][v])
                d[v] = d[u] + a[u][v];
        }
    }
}

int main()
{
    int N, M, S, T, a[100][100], man[100], woman[100], MIN = 10000, Luu = 0;
    vector < int > ke[1000];

    cin >> N >> M >> S >> T;
    for (int i = 1; i <= M; i++)
    {
        int x, y, t;
        cin >> x >> y >> t;
        ke[x].push_back(y);
        ke[y].push_back(x);
        a[x][y] = a[y][x] = t;
    }

    DIJKTRA(N, ke, a, S, man);
    DIJKTRA(N, ke, a, T, woman);

    for (int i = 1; i <= N; i++)
    {
        if (man[i] == woman[i] && MIN > man[i])
        {
            MIN = man[i];
            Luu = i;
        }
    }
    if (Luu != 0)  cout << Luu;
    else cout << "CRY";
    return 0;
}