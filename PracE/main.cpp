#include <cstdio>
#include <utility>
#include <deque>
#include <vector>
#include <cmath>
using namespace std;

#define id first
#define until second.first
#define inclusive second.second

const int maxl = 10 * 1000 + 5;
const int maxk = 105;

long long A[maxl];
long long B[maxl];
int F[maxl];

long long f[maxl];
long long g[maxl];
int order[maxl];

int pred[maxl][maxk];

deque<pair<int, pair<double, bool> > >Q;
vector<int> sorted[maxl];

// wspolczynniki prostej i
pair<long long, long long> get_coeffs (int i) {
    long long a = A[i];
    long long b = f[i] - B[i] - 1LL*i*A[i];
    return {a, b};
}

// czy proste i, j przecinaja sie w x
bool is_crossing (int i, int j, long long x) {
    pair<long long, long long> a = get_coeffs(i);
    pair<long long, long long> b = get_coeffs(j);
    return a.first*x + a.second == b.first*x + b.second;
}

// iloczyn wektorowy prostej i z prosta j w punkcie x
double cross_prod (int i, int j, double x) {
    pair<long long, long long> a = get_coeffs(i);
    pair<long long, long long> b = get_coeffs(j);

    pair<double, double> v = { 1, a.first };
    pair<double, double> u = { x, (double) x*b.first + b.second - a.second };

    double cross = v.first * u.second - v.second * u.first;

    return cross;
}

// punkt przeciecia prostych i, j
double crossing (int i, int j) {
    pair<long long, long long> a = get_coeffs(i);
    pair<long long, long long> b = get_coeffs(j);
    return (double) (b.second - a.second) / (double) (a.first - b.first);
}

// dorzuc prosta i do otoczki
void add_line (int i) {
    if (Q.size() > 0) {
        int j = Q.front().id;
        double cross = cross_prod(i, j, 0);
        if (cross <= 0) {
            return;
        }
    }

    while (Q.size() > 1) {
        double y = Q[1].until;
        int j = Q.front().id;
        double cross = cross_prod(i, j, y);
        if(cross > 0) {
            Q.pop_front();
        } else if (cross == 0) {
            if (Q[1].inclusive) {
                Q.pop_front();
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if (Q.size() > 0) {
        int j = Q.front().id;
        double x = crossing(i, j);
        if (is_crossing(i, j, (long long) round(x))) {
            x = round(x);
        }
        Q.front().until = x;
        Q.front().inclusive = order[j] < order[i];
    }
    Q.push_front({i, {0, true}});
}

// zwroc najlepsza prosta w punkcie i
int get_min (double i) {
    while (Q.size() > 1) {
        if (i < Q.back().until or (i == Q.back().until and !Q.back().inclusive)) {
            Q.pop_back();
        } else {
            break;
        }
    }
    return Q.back().id;
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

        // pierwszy krok - wszystkie literki na ostatnim klawiszu
        order[i] = i - 1;
        f[i] = B[i];
        pred[i][0] = l + 1;
    }

    for (int key = 1; key < k; key++){

        for (int i = l-key; i > 0; i--) {
            add_line(i+1);
            int j = get_min((double) i);
            g[i] = f[j] + B[i]-B[j] - 1LL*(j-i)*A[j];
            pred[i][key] = j;
            sorted[order[j]].push_back(i);
        }

        int cnt = 0;
        for (int i = 0; i < l - key + 1; i++) {
            for (int j = sorted[i].size() - 1; j >= 0; j--) {
                order[sorted[i][j]] = cnt++;
            }
            sorted[i].clear();
            f[i+1] = g[i+1];
        }
        Q.clear();
    }

    printf("%lld\n", f[1]);
    int ind = 1;
    for (int key = k - 1; key >= 0; key--) {
        printf("%d ", pred[ind][key] - ind);
        ind = pred[ind][key];
    }
    puts("");
}
