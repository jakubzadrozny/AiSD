#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 1000005;
const int p = 999979;
const long long H = 1000000005LL;

int n, m;
int edges[maxn];
int routes[maxn];

vector<long long>nums;
vector<int>G[maxn];
vector<pair<long long, long long> >E;

long long get_hash(int x, int y) {
    return 1LL * x * H + 1LL * y;
}

int get_vertex(long long v) {
    return lower_bound(nums.begin(), nums.end(), v) - nums.begin();
}

int main () {
    int t;
    scanf("%d %d %d", &m, &n, &t);
    while(t--) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        long long u = get_hash(a, b);
        long long v = get_hash(c, d);

        nums.push_back(u);
        nums.push_back(v);

        E.push_back({u, v});
    }

    nums.push_back(get_hash(0, 0));
    nums.push_back(get_hash(m, n));
    sort(nums.begin(), nums.end());

    while(E.size()) {
        long long u = E.back().first;
        long long v = E.back().second;
        E.pop_back();

        int i = get_vertex(u);
        int j = get_vertex(v);

        edges[j]++;
        G[i].push_back(j);
    }

    int s = get_vertex(get_hash(0, 0));
    int f = get_vertex(get_hash(m, n));
    routes[s] = 1;
    queue<int>Q;
    if(edges[0] == 0)
        Q.push(0);
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i - 1] == nums[i])
            continue;
        if(edges[i] == 0)
            Q.push(i);
    }

    while(Q.size()) {
        int v = Q.front();
        if(v == f) break;
        Q.pop();
        for(auto u : G[v]) {
            routes[u] = (routes[u] + routes[v]) % p;
            if(--edges[u] == 0)
                Q.push(u);
        }
    }

    printf("%d\n", routes[f]);
}
