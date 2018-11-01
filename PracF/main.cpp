#include <cstdio>
#include <algorithm>
#include <utility>
#include <tuple>
#include <stack>
#include <vector>
using namespace std;

#define x first
#define y second

const int maxn = 1000 + 5;
const int maxt = 100 * 1000 + 5;
const int maxhash = maxn * maxn + maxn;
const int dirs = 4;

pair<int, int> directions[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

vector<pair<int, pair<int, int> > >Q;

stack<int>T;
stack<int>ANS;

int rep[maxhash];
int size[maxhash];
int areas = 0;

bool valid(int i, int j, int n, int m) {
    return i >= 0 and j >= 0 and i < n and j < m;
}

void makeset(int v) {
    rep[v] = v;
    size[v] = 1;
    areas += 1;
}

int find(int v) {
    if (rep[v] == v) {
        return v;
    }
    rep[v] = find(rep[v]);
    return rep[v];
}

void unionn(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (a != b) {
        if (size[a] < size[b]) {
            swap(a, b);
        }
        size[a] += size[b];
        rep[b] = a;
        areas -= 1;
    }
}

int encode(int i, int j) {
    return i * maxn + j;
}

int main () {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int h;
            scanf("%d", &h);
            Q.push_back({h, {i, j}});
            rep[encode(i,j)] = -1;
        }
    }
    sort(Q.begin(), Q.end());

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int h;
        scanf("%d", &h);
        T.push(h);
    }

    int qind = Q.size()-1;
    while (T.size()) {
        int qh, ah;
        pair<int, int>f;
        qh = T.top();
        if (qind < 0) {
            ah = -1;
        } else {
            tie(ah, f) = Q[qind];
        }

        if (ah <= qh) {
            T.pop();
            ANS.push(areas);
        } else {
            qind--;
            int af = encode(f.x, f.y);
            makeset(af);
            for(int i = 0; i < dirs; i++) {
                int dx = directions[i].x;
                int dy = directions[i].y;
                if (valid(f.x+dx, f.y+dy, n, m)) {
                    int h = encode(f.x+dx, f.y+dy);
                    if (rep[h] >= 0) {
                        unionn(af, h);
                    }
                }
            }
        }
    }

    while (ANS.size()) {
        printf("%d ", ANS.top());
        ANS.pop();
    }
}
