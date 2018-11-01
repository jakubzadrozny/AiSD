#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

const int maxn = 1000005;
const int p = 999979;
const long long H = 1000000005LL;

int n, m, cnt = 0;
int edges[maxn];
int routes[maxn];

vector<int>G[maxn];
unordered_map<long long, int>M;

int get_vertex(int x, int y) {
    long long hash = 1LL * x * H + 1LL * y;
    auto it = M.find(hash);
    if(it == M.end()) {
        M[hash] = cnt;
        return cnt++;
    } else {
        return (*it).second;
    }
}

int main () {
    int t;
    scanf("%d %d %d", &m, &n, &t);
    while(t--) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);

        int v = get_vertex(a, b);
        int u = get_vertex(c, d);

        edges[u]++;
        G[v].push_back(u);
    }

    int s = get_vertex(0, 0);
    int f = get_vertex(m, n);
    routes[s] = 1;
    queue<int>Q;
    for(int i = 0; i < cnt; i++) {
        if(edges[i] == 0) {
            Q.push(i);
        }
    }

    while(Q.size()) {
        int v = Q.front();
        if(v == f) break;
        Q.pop();
        for(auto u : G[v]) {
            routes[u] = (routes[u] + routes[v]) % p;
            if(--edges[u] == 0) {
                Q.push(u);
            }
        }
    }

    printf("%d\n", routes[f]);
}
