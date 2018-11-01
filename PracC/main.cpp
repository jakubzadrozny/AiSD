#include <cstdio>
#include <deque>
using namespace std;

int main () {
    int n, l, b;
    scanf("%d %d %d", &n, &l, &b);
    deque<pair<int, long long> >Q;
    Q.push_back({0, 0LL});
    for(int i = 0; i < n; i++) {
        int d, c;
        scanf("%d %d", &d, &c);

        while(Q.size() and d - Q.front().first > b)
            Q.pop_front();

        if(Q.empty()) {
            puts("NIE");
            return 0;
        } else {
            long long cost = c + 1LL * Q.front().second;
            while(Q.size() and Q.back().second >= cost)
                Q.pop_back();
            Q.push_back({d, cost});
        }
    }

    while(Q.size() and l - Q.front().first > b)
        Q.pop_front();

    if(Q.empty()) {
        puts("NIE");
    } else {
        printf("%lld\n", Q.front().second);
    }
}
