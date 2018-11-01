#include <cstdio>
#include <stack>
using namespace std;

const int maxn = 1000 * 1000 + 1;

int pre[maxn]; 
int post[maxn];
int children[maxn];
int size[maxn];
int start[maxn];

stack<int>S;

int cnt = 0;

int main () {
    int n, q;
    scanf("%d %d", &n, &q);
    for(int i = 1; i < n; i++) {
        int v;
        scanf("%d", &v);
        v--;
        post[i] = v;
        size[v]++;
    }
    for(int i = 1; i < n; i++) {
        start[i] = start[i - 1] + size[i - 1];    
    }
    for(int i = 1; i < n; i++) {
        int v = post[i];
        children[start[v]++] = i;
    }

    S.push(0);
    while(!S.empty()) {
        int v = S.top();
        if(!pre[v]) {
            pre[v] = ++cnt;
        }
        if(size[v] > 0) {
            int next = children[start[v] - size[v]];
            size[v]--;
            S.push(next);
        } else {
            post[v] = cnt;
            S.pop();
        }
    }

    while(q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        if(pre[b] >= pre[a] and pre[b] <= post[a]) {
            puts("TAK");
        } else {
            puts("NIE");
        } 
    }
}
