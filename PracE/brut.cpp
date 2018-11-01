#include <cstdio>
#include <stack>
using namespace std;

const long long INF = 1LL << 60;
const int maxl = 10 * 1000 + 5;
const int maxk = 105;

long long A[maxl];
long long B[maxl];
int F[maxl];

long long f[maxl];
long long g[maxl];
int pred[maxl][maxk];

long long S(int a, int b) {
    return B[a] - B[b+1] - 1LL*(b - a + 1)*A[b+1];
}

int main () {
    int k, l;
    scanf("%d%d", &k, &l);
    for (int i = 1; i <= l; i++) {
        scanf("%d", &F[i]);
    }

    for (int i = l; i > 0; i--) {
        A[i] = 1LL*F[i] + A[i+1];
        B[i] = B[i+1] + A[i];

        g[i] = INF;
        pred[i][0] = 0;

    }

    for (int i = 1; i <= l; i++) {
        f[i] = S(1, i);
    }

    for (int key = 1; key < k; key++) {
        for (int i = key + 1; i <= l; i++) {
            for (int j = key; j < i; j++) {
                long long c = f[j] + S(j + 1, i);
                if (c < g[i]) {
                    g[i] = c;
                    pred[i][key] = j;
                }
            }
        }

        for (int i = key + 1; i <= l; i++) {
            f[i] = g[i]; g[i] = INF;
        }
    }

    printf("%lld\n", f[l]);
    stack<int>keys;
    int ind = l;
    for (int key = k - 1; key >= 0; key--) {
        keys.push(ind - pred[ind][key]);
        ind = pred[ind][key];
    }
    while(keys.size()) {
        printf("%d ", keys.top());
        keys.pop();
    }
    puts("");
}
